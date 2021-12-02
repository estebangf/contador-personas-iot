#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}


/*
Esta es la forma en la que yo calculaba la distancia en otro proyecto
byte pinTrig = 8;
byte pinEcho = 9;

int medirDistancia(){
  digitalWrite(pinTrig, HIGH);
  delay(1);
  digitalWrite(pinTrig, LOW);
  int t = pulseIn(pinEcho, HIGH);

  velocidad = espacio / tiempo.
  espacio = velocidad * tiempo

  // No recuerdo la fundamentación exacta para esta
  // parte de la función, solo recuerdo que 58.3 era
  // una constante.
  // Sin embargo, recomiendo que utilicemos el material
  // en la siguiente pagina para calcular la distancia
  // ya que es mucho mas prolijo, eficaz y preciso:
  // https://programarfacil.com/blog/arduino-blog/sensor-ultrasonico-arduino-medir-distancia/
  return  t / 58.3;
}
*/
