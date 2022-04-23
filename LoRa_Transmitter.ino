#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <BH1750.h>
#include "DHT.h"               

#define ss 18
#define rst 14
#define dio0 26
#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("LoRa Sender");
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(ss, rst, dio0);
  
  if (!LoRa.begin(868E6)) {
    Serial.println("Start of LoRa failed!");
    while (1);
  }
  Wire.begin(21, 22);
  lightMeter.begin();
  dht.begin();

}

void loop() {
  float lux = lightMeter.readLightLevel();
  int wet = analogRead(36);
  int rain = analogRead(12);
  float h = dht.readHumidity();   
  float t = dht.readTemperature();
  Serial.print(h);
  Serial.print(t);
  // send packet
  LoRa.beginPacket();
  LoRa.print("Lux: ");
  LoRa.println(lux);
  LoRa.print("Wet: ");
  LoRa.println(wet);
  LoRa.print("Humid: ");
  LoRa.println(h);
  LoRa.print("Rain: ");
  LoRa.println(rain);
  LoRa.print("Temp: ");
  LoRa.println(t);
  LoRa.endPacket();
  counter++;
  delay(5000);
}
