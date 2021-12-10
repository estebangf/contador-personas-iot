// LIBRERIAS UTILIZADAS
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "Webpage.h"

WiFiClient client;

//--- Pines utilizados ---------------
#define LED_AZUL 2 // LED azul de la placa

#define TRIGGER 5 // Sensor ultrasonico
#define ECHO 6    // Sensor ultrasonico
//-----------------------------------------------

//--- Constantes ---------------
const float VEL_SONIDO = 34300.0; // Velocidad del sonido en cm/s
const float UMBRAL = 30.0;        // Umbral maximo cuando no hay persona
const portTickType delayOneSeccond = 1000 / portTICK_RATE_MS;

const char *USERNAME = "admin";
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
void handleSetEstacionamiento();
void handleGetConfigs();
//-----------------------------------------------

//--- Prototipo funciones FREERTOS -------------
void tareaSensor(void *pvParameters);
//-----------------------------------------------

//--- CONFIGURACION WIFI ------------------------
WebServer server(80);
const char *SSID = "Fernandez";
const char *PASSWORD = "lulu2017";

const char *DEVICE_NAME = "ESP32_IOT";
//-----------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP ENCENDIDO...");

  //--- Modo entrada/salida de los pines ----------
  pinMode(LED_AZUL, OUTPUT);
  //-----------------------------------------------
  Serial.println("PINS CONFIGURADOS...");

  //--- CONFIGURACION WIFI ------------------------
  WiFi.hostname(DEVICE_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.println("WIFI CONFIGURADO...");
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    digitalWrite(LED_AZUL, HIGH);
    delay(100);
    Serial.print(".");
    digitalWrite(LED_AZUL, LOW);
    delay(100);
  }
  digitalWrite(LED_AZUL, LOW);
  // IPAddress ip(192, 168, 0, 125);
  // IPAddress gateway(192, 168, 0, 1);
  // IPAddress subnet(255, 255, 255, 0);
  // IPAddress primaryDNS(8, 8, 8, 8);   //optional
  // IPAddress secondaryDNS(8, 8, 4, 4); //optional
  // WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //-----------------------------------------------

  //--- CREACION DE TAREAS FREERTOS ---------------
  xTaskCreatePinnedToCore(tareaSensor, "tareaSensor", 2048, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  //-----------------------------------------------

  //--- INICIALIZACION DEL SERVIDOR ---------------
  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/setwifi", handleSetWifi);
  server.on("/setbroker", handleSetBroker);
  server.on("/setestacionamiento", handleSetEstacionamiento);
  server.on("/getconfigs", handleGetConfigs);
  server.begin();
  Serial.println("HTTP server started");
  //-----------------------------------------------
}

void loop()
{
  server.handleClient();
  // vTaskDelay(10 / portTICK_RATE_MS);
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
  server.send(200, "text/html", WebpageCode);
}
void handleLogin()
{
  String username = server.arg("username");
  String password = server.arg("password");

  if (username == USERNAME && password == PASSWORD)
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

  server.send(200, "text/plane", "{\"message\": \"succcess\"}");
}
void handleSetBroker()
{
  String domain = server.arg("domain");
  String port = server.arg("port");
  String username = server.arg("username");
  String password = server.arg("password");

    server.send(200, "text/plane", "{\"message\": \"succcess\"}");
}
void handleSetEstacionamiento()
{
  String sucursal = server.arg("sucursal");
  String cupo = server.arg("cupo");
  String puerta = server.arg("puerta");

    server.send(200, "text/plane", "{\"message\": \"succcess\"}");
}
void handleGetConfigs()
{
  String section = server.arg("section");
  String configs = "{\"message\": \"success\", \"configs\": ";
  if (section == "broker")
  {
    configs += "{\"username\":\"";
    configs += USERNAME;
    configs += "\",\"password\":\"";
    configs += PASSWORD;
    configs += "\"}";
  }
  else if (section == "wifi")
  {
    configs += "{\"ssid\":\"";
    configs += USERNAME;
    configs += "\",\"password\":\"";
    configs += PASSWORD;
    configs += "\"}";
  }
  configs += "}";

  server.send(200, "text/plane", configs);
}
//-----------------------------------------------