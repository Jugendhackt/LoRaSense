#include "SimpleDHT.h"

int pinDHT11 = 2;
SimpleDHT11 dht11;
int  sensorPin  =  A0; 
int  sensorValue =  0;

int wait = 60000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }
  
  for (int i = 0; i < 40; i++) {
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  
  Serial.print("Temperatur :");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print("Luftfeuchtigkeit: ");
  Serial.print((int)humidity); Serial.println(" %");

  sensorValue =  analogRead(sensorPin);
  delay(sensorValue); 
  delay(sensorValue);
  Serial.print("Lautstärke: ");
  Serial.println(sensorValue,  DEC);
  
  delay(wait);
}
