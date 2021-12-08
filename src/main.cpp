// LIBRERIAS UTILIZADAS
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "Webpage.h"
#include "SensorUS.h"

WiFiClient client;
SensorUS sensor;

//--- Pines utilizados ---------------
#define LEDAZUL 2 // LED azul de la placa

#define TRIGGER 5 // Sensor ultrasonico
#define ECHO 6    // Sensor ultrasonico
//-----------------------------------------------

//--- Constantes ---------------
const float VEL_SONIDO = 34300.0; // Velocidad del sonido en cm/s
const float DEFUMBRAL = 150.0;       // Umbral maximo cuando no hay persona
const portTickType delayOneSeccond = 1000 / portTICK_RATE_MS;
//-----------------------------------------------

//--- CORE ------------------------------------
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
//-----------------------------------------------

//--- Prototipos funciones SERVIDOR ------------

//-----------------------------------------------

//--- Prototipo funciones FREERTOS -------------
//void tareaSensor(void *pvParameters);
//-----------------------------------------------

//--- CONFIGURACION WIFI ------------------------
WebServer Server(80);
const char *SSID = "Fibertel WiFi308 2.4GHz";
const char *PASSWORD = "0041251608";

const char *DEVICE_NAME = "ESP32_THING";
//-----------------------------------------------

void setup()
{
  /*
  //--- Modo entrada/salida de los pines ----------
  pinMode(ECHO, INPUT);     // Entrada del Sensor ultrasonico
  pinMode(TRIGGER, OUTPUT); // Salida del Sensor ultrasonico
  pinMode(LEDAZUL, OUTPUT);
  //-----------------------------------------------
  */
  sensor.begin(TRIGGER, ECHO);

  //--- CONFIGURACION WIFI ------------------------
  WiFi.hostname(DEVICE_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    digitalWrite(LED, HIGH);
    delay(100);
    Serial.print(".");
    digitalWrite(LED, LOW);
    delay(100);
  }
  digitalWrite(LED, LOW);
  IPAddress ip(192, 168, 0, 125);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4); //optional
  WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //-----------------------------------------------

  //--- CREACION DE TAREAS FREERTOS ---------------
  xTaskCreatePinnedToCore(tareaSensor, "tareaSensor", 2048, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  //-----------------------------------------------

  //--- INICIALIZACION DEL SERVIDOR ---------------
  Server.on("/", handleRoot);
  Server.on("/readState", readState);
  Server.begin();
  //-----------------------------------------------
}

void loop()
{
  sensor.checkDist(DEFUMBRAL);

  Server.handleClient();
  vTaskDelay(10 / portTICK_RATE_MS);
}

//--- FUNCIONES FREERTOS -------------------------
/*
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
    vTaskDelay(delayOneSeccond)
  }
}
*/
//-----------------------------------------------

//--- FUNCIONES AUXILIARES ------------------------
/*
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

bool evaluarDistancia() 
{
  if(calcularDistancia>UMBRAL)
    return true
  else
    return false
}
*/

//--- FUNCIONES SERVIDOR ------------------------
void handleRoot()
{
  server.send(200, "text/html", WebpageCode);
}
void readState()
{
  String act_state = server.arg("state");

  // CODIGO PERTINENTE...

  server.send(200, "text/plane", state);
}
//-----------------------------------------------