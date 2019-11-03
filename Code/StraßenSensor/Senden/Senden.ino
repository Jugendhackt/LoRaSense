#include "TheThingsNetwork.h"
#include "SimpleDHT.h"

#define loraSerial Serial1
#define debugSerial Serial
#define freqPlan TTN_FP_EU868

const char *devAddr = "26011165";
const char *nwkSKey = "";
const char *appSKey = "";

int pinDHT11 = 2;
SimpleDHT11 dht11;
int  sensorPin  =  A0; 
int  sensorValue =  0;
int wait = 10000;

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);
  
  while (!debugSerial && millis() < 10000);
  
  debugSerial.println("-- PERSONALIZE");
  ttn.personalize(devAddr, nwkSKey, appSKey);
  debugSerial.println("-- STATUS");
  ttn.showStatus();
}

void loop()
{
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
  
  debugSerial.println("-- LOOP");

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

  byte jh[3] = {0};
  
  jh[0] = temperature;
  jh[1] = humidity;
  jh[2] = sensorValue;

  /*

  byte temp[1];
  temp[0] = temperature;

  byte hum[1];
  hum[0] = humidity;

  byte dzb[1];
  dzb[0] = sensorValue;

  ttn.sendBytes(temp, sizeof(temp)); //Temperatur
  delay(100);
  ttn.sendBytes(hum, sizeof(hum));   //Luftfeuchtigkeit
  delay(100);
  ttn.sendBytes(dzb, sizeof(dzb));   //Lautstärke
  
  */
  
  ttn.sendBytes(jh, sizeof(jh));
  
  delay(wait);                       //Warte wait Millisekunden
}
