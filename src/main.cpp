// LIBRERIAS UTILIZADAS
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Preferences.h>
#include "Webpage.h"
#include "APWebpage.h"

// WiFiClient client;
WiFiServer serverWifi(80);
Preferences PrefWifi;
Preferences PrefUser;
Preferences PrefBroker;
Preferences PrefEstacion;

//--- Pines utilizados ---------------
#define LED_AZUL 2 // LED azul de la placa

#define TRIGGER 5 // Sensor ultrasonico
#define ECHO 6    // Sensor ultrasonico
//-----------------------------------------------

//--- Constantes ---------------
const float VEL_SONIDO = 34300.0; // Velocidad del sonido en cm/s
const float UMBRAL = 30.0;        // Umbral maximo cuando no hay persona
const portTickType delayOneSeccond = 1000 / portTICK_RATE_MS;
//-----------------------------------------------

//--- CORE ------------------------------------
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
//-----------------------------------------------

//--- Prototipos funciones ------------
void iniciarTrigger();
float calcularDistancia();
//-----------------------------------------------

//--- Prototipos funciones SERVIDOR ------------
void handleRoot();
void handleLogin();
void handleSetWifi();
void handleSetBroker();
void handleSetEstacion();
void handleGetConfigs();
//-----------------------------------------------

//--- Prototipo funciones FREERTOS -------------
void tareaSensor(void *pvParameters);
//-----------------------------------------------

//--- CONFIGURACION WIFI ------------------------
WebServer server(80);
const uint8_t MAX_TEST = 5;
uint8_t testWifi = 1;

const char *DEVICE_NAME = "ESP32_IOT";
//-----------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP ENCENDIDO...");
  PrefUser.begin("user", false);
  PrefWifi.begin("wifi", false);
  PrefBroker.begin("broker", false);
  PrefEstacion.begin("estacion", false);

  //--- Modo entrada/salida de los pines ----------
  pinMode(LED_AZUL, OUTPUT);
  //-----------------------------------------------
  Serial.println("PINS CONFIGURADOS...");

  //--- CONFIGURACION WIFI ------------------------
  WiFi.hostname(DEVICE_NAME);
  WiFi.mode(WIFI_STA);
  String ssidWifiPref = PrefWifi.getString("ssid", " ");
  String passwordWifiPref = PrefWifi.getString("password", " ");
  const char *ssidWifi = ssidWifiPref.c_str();
  const char *passwordWifi = passwordWifiPref.c_str();

  Serial.print("WIFI SSID: ");
  Serial.println(ssidWifi);
  Serial.print("WIFI PASSWORD: ");
  Serial.println(passwordWifi);
  WiFi.begin(ssidWifi, passwordWifi);

  while (WiFi.waitForConnectResult() != WL_CONNECTED && testWifi < MAX_TEST)
  {
    digitalWrite(LED_AZUL, HIGH);
    delay(100);
    Serial.print(".");
    digitalWrite(LED_AZUL, LOW);
    delay(100);
    testWifi++;
  }
  digitalWrite(LED_AZUL, LOW);
  if (testWifi >= MAX_TEST)
  {
    digitalWrite(LED_AZUL, HIGH);
    Serial.println("WIFI MAL CONFIGURADO...");
    Serial.println("CREANDO AP...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("AP-IOT", "iotserver");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    Serial.println(WiFi.localIP());
  }
  //-----------------------------------------------

  //--- CREACION DE TAREAS FREERTOS ---------------
  xTaskCreatePinnedToCore(tareaSensor, "tareaSensor", 2048, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  //-----------------------------------------------

  //--- INICIALIZACION DEL SERVIDOR ---------------
  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/setwifi", handleSetWifi);
  server.on("/setbroker", handleSetBroker);
  server.on("/setestacion", handleSetEstacion);
  server.on("/getconfigs", handleGetConfigs);
  server.begin();
  Serial.println("HTTP server started");
  //-----------------------------------------------

  //----- BROKER ----------------------------------
  String domainBrokerST = PrefBroker.getString("domain");
  String usernameBrokerST = PrefBroker.getString("username");
  String passwordBrokerST = PrefBroker.getString("password");

  const char *domainBroker = domainBrokerST.c_str();
  uint16_t portBroker = PrefBroker.getUShort("port");
  const char *usernameBroker = usernameBrokerST.c_str();
  const char *passwordBroker = passwordBrokerST.c_str();
  //-----------------------------------------------

  
  //----- Estacion ----------------------------------
  String puertaEstacionST = PrefEstacion.getString("puerta");

  uint16_t sucursalEstacion = PrefEstacion.getUShort("sucursal");
  uint16_t cupoEstacion = PrefEstacion.getUShort("cupo");
  const char *puertaEstacion = PrefEstacion.getString("puerta").c_str();
  //-----------------------------------------------
}

void loop()
{
  server.handleClient();
  // vTaskDelay(10 / portTICK_RATE_MS);.
}

//--- FUNCIONES FREERTOS -------------------------
void tareaSensor(void *pvParameters)
{
  while (true)
  {

    iniciarTrigger();                      // Preparamos el sensor de ultrasonidos
    float distancia = calcularDistancia(); // Obtenemos la distancia
    if (distancia < UMBRAL)                // Verificamos el umbral
    {
      // Lanzamos alertas
    }
    vTaskDelay(delayOneSeccond);
  }
}
//-----------------------------------------------

//--- FUNCIONES AUXILIARES ------------------------
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(TRIGGER, LOW);
}
float calcularDistancia()
{
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH);

  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * VEL_SONIDO / 2.0;
  vTaskDelay(delayOneSeccond / 2);

  return distancia;
}
//-----------------------------------------------

//--- FUNCIONES SERVIDOR ------------------------
void handleRoot()
{
  if (testWifi >= MAX_TEST)
    server.send(200, "text/html", APWebpageCode);
  else
    server.send(200, "text/html", WebpageCode);
}
void handleLogin()
{
  String username = server.arg("username");
  String password = server.arg("password");

  if (username == PrefUser.getString("username", "admin") &&
      password == PrefUser.getString("password", "1234"))
  {
    server.send(200, "text/plane", "{\"message\": \"succcess\"}");
  }
  else
  {
    server.send(200, "text/plane", "{\"error\": \"error\",\"message\": \"Credenciales incorrectas\"}");
  }
}
void handleSetWifi()
{
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  PrefWifi.putString("ssid", ssid);
  PrefWifi.putString("password", password);

  server.send(200, "text/plane", "{\"message\": \"succcess\"}");
  ESP.restart();
}
void handleSetBroker()
{
  String domain = server.arg("domain");
  uint16_t port = server.arg("port").toInt();
  String username = server.arg("username");
  String password = server.arg("password");

  PrefBroker.putString("domain", domain);
  PrefBroker.putUShort("port", port);
  PrefBroker.putString("username", username);
  PrefBroker.putString("password", password);

  server.send(200, "text/plane", "{\"message\": \"succcess\"}");
}
void handleSetEstacion()
{
  uint16_t sucursal = server.arg("sucursal").toInt();
  uint16_t cupo = server.arg("cupo").toInt();
  String puerta = server.arg("puerta");

  PrefEstacion.putUShort("sucursal", sucursal);
  PrefEstacion.putUShort("cupo", cupo);
  PrefEstacion.putString("puerta", puerta);

  server.send(200, "text/plane", "{\"message\": \"succcess\"}");
}
void handleGetConfigs()
{
  String section = server.arg("section");
  String configs = "{\"message\": \"success\", \"configs\": ";
  if (section == "broker")
  {
    configs += "{\"domain\":\"";
    configs += PrefBroker.getString("domain");
    configs += "\",\"port\":\"";
    configs += PrefBroker.getUShort("port");
    configs += "\",\"username\":\"";
    configs += PrefBroker.getString("username");
    configs += "\",\"password\":\"";
    configs += PrefBroker.getString("password");
    configs += "\"}";
  }
  else if (section == "estacion")
  {
    configs += "{\"sucursal\":\"";
    configs += PrefBroker.getUShort("sucursal");
    configs += "\",\"cupo\":\"";
    configs += PrefBroker.getUShort("cupo");
    configs += "\",\"puerta\":\"";
    configs += PrefBroker.getString("puerta");
    configs += "\"}";
  }
  else if (section == "wifi")
  {
    configs += "{\"ssid\":\"";
    configs += PrefWifi.getString("ssid");
    configs += "\",\"password\":\"";
    configs += PrefWifi.getString("password");
    configs += "\"}";
  }
  configs += "}";

  server.send(200, "text/plane", configs);
}
//-----------------------------------------------