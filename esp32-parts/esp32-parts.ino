#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include "credentials.h"
#include <Wire.h>
#define LDR_PIN   22
#define DHTPIN    23
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure client;

const int LEDPIN = 2; 
const int PushButton = 4; 
const int sendInterval = 5000; 
int value1, value2, value3;

void setup() {

  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Wifi Connecting...........");
  Serial.println("Wifi Connected !!!");
  pinMode(LEDPIN, OUTPUT);
  pinMode(PushButton, INPUT);
}

void loop() {
  value1 = dht.readHumidity();
  value2 = dht.readTemperature();
  value3 = getLightPercentage(); 
  data_send();
  delay(sendInterval);
  data_read();
  delay(sendInterval);
}
