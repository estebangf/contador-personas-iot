// LIBRERIAS UTILIZADAS
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "Webpage.h"
#include <MQTT.h>
#include <HTTPClient.h> 

WiFiClient client;
MQTTClient clientmqtt;

//--- Prototipo de Funciones --------
void iniciarTrigger();
float calcularDistancia();

//--- Pines utilizados ---------------
#define LEDAZUL 2 // LED azul de la placa

#define TRIGGER 5 // Sensor ultrasonico
#define ECHO 4    // Sensor ultrasonico
//-----------------------------------------------

//--- Constantes ---------------
const float VEL_SONIDO = 34300.0; // Velocidad del sonido en cm/s
const float UMBRAL = 10.0;        // Umbral maximo cuando no hay persona
const portTickType delayOneSeccond = 1000 / portTICK_RATE_MS;

unsigned long lastMillis = 0;
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
void tareaSensor(void *pvParameters);
//-----------------------------------------------

//--- CONFIGURACION WIFI ------------------------
WebServer Server(80);
const char *SSID = "leosui";
const char *PASSWORD = "01345678";

const char *DEVICE_NAME = "ESP32_THING";
//-----------------------------------------------

//-------- Conectando el MQTT ------------------


void connect() {
  Serial.printf("\nconnecting....");
  while(!clientmqtt.connect("Broker IOT")) //Se conecta al broker de NodeRED con/sin usuario y pass
  {
    Serial.printf(".");
    delay(1000);
  }
  Serial.print("\nconnected");
  clientmqtt.subscribe("Leo"); //Poner su nombre
}

void messageReceived(String &topic, String &payload) //Recibe mensajes del topico
{
  Serial.println("incoming: " + topic + " - " + payload);
}
//--------------------------------------------------

void setup()
{
  Serial.begin(115200);
  //--- Modo entrada/salida de los pines ----------
  pinMode(ECHO, INPUT);     // Entrada del Sensor ultrasonico
  pinMode(TRIGGER, OUTPUT); // Salida del Sensor ultrasonico
  pinMode(LEDAZUL, OUTPUT);
  //-----------------------------------------------

  //--- CONFIGURACION WIFI ------------------------
  WiFi.hostname(DEVICE_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    digitalWrite(LEDAZUL, HIGH);
    delay(100);
    Serial.print(".");
    digitalWrite(LEDAZUL, LOW);
    delay(100);
  }
  digitalWrite(LEDAZUL, LOW);
  IPAddress ip(192, 168, 43, 18);
  IPAddress gateway(192, 168, 43, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4); //optional
  WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


 //----------------CONECTANDO AL BROKER-------------------------------
  
  clientmqtt.begin("138.219.235.16", 6321, client); //cliente mqtt
  //clientmqtt.onMessage(messageReceived);

  connect();

  //-----------------------------------------------

  //--- CREACION DE TAREAS FREERTOS ---------------
  xTaskCreatePinnedToCore(tareaSensor, "tareaSensor", 2048, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  //-----------------------------------------------

  //--- INICIALIZACION DEL SERVIDOR ---------------
  //Server.on("/", handleRoot);
  //Server.on("/readState", readState);
  Server.begin();
  //-----------------------------------------------
}

void loop() {
  clientmqtt.loop(); //Actualiza el estado del cliente MQTT, si o si tiene que estar en el loop

  if (!clientmqtt.connected()) //Verifica que el client está conectado
  {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    //clientmqtt.publish("Leo", "world"); //Poner su nombre
  }
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
      clientmqtt.publish("Leo", "world", "musica" "river" "3");
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

