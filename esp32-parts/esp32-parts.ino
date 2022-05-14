#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include "credentials.h"
#include <Wire.h>

#define DHTPIN    23
#define DHTTYPE DHT11

//dht
DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure client;
const int sendInterval = 5000; 
int value1, value2, value3;

//fan
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
const int freq = 100000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 50;

void setup() {

  Serial.begin(921600);
  //fan
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);
  //dht
  dht.begin();
  //wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Wifi Connecting...........");
  Serial.println("Wifi Connected !!!");  
}

void loop() {
  
  value1 = dht.readHumidity();
  value2 = dht.readTemperature();
  data_send();
  fan_run(data_read());
  delay(sendInterval);
}
