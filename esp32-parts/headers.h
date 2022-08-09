#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <Servo.h>
#include "credentials.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
WiFiClient client;
WiFiClientSecure client;

#define DHTPIN    23
#define DHTTYPE DHT11
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701 
#define SENSOR_PIN 34

//all objects

//dht
DHT dht(DHTPIN, DHTTYPE);

//drawer servo
Servo servo1;
Servo servo2;

//all variables

//sensor data
int value1, value2, value3;

//fan
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
const int freq = 3000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;


unsigned long lastTime = 0;
unsigned long timerDelay = 10000;


//drawer
int pos = 0;
int lastState = LOW; 
int currentState;
int echo = 2;
int trigger = 4;
long duration;
float distanceCm;
float distanceInch;
