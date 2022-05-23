#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <Servo.h>
#include "credentials.h"
#include <Wire.h>
#define DHTPIN    23
#define DHTTYPE DHT11
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

//all objects

//dht
DHT dht(DHTPIN, DHTTYPE);
//drawer servo
Servo servo1;
Servo servo2;
//wifi
WiFiClientSecure client;

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
//drawer
int pos = 0;
int lastState = LOW; 
int currentState;
int echo = 2;
int trigger = 4;
long duration;
float distanceCm;
float distanceInch;

void setup() {

  Serial.begin(115200);
  //fan
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  //dht
  dht.begin();
  //drawer servo
  servo1.attach(13);  // servo1
  servo2.attach(15); //servo2

  
  //wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Wifi Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.println("Wifi Connected !!!");  
}

void loop() {
  value1 = dht.readHumidity();
  value2 = dht.readTemperature();
  sensor_data_send();
  String input, input2, val[10];
  input = get_data();
  input2 = input;
  int in2,i, in = 0, fan_switch, fan_speed, drawer_switch1, drawer_switch2; 
  while(input2.indexOf(',') != -1)
  {
      in2 = input2.indexOf(',');
      val[in++] = input2.substring(0, in2);
      input2 = input2.substring(in2 + 1, input2.length());
  }
  val[in++] = input2.substring(0,input2.length());
  for(i = 0; i < in ; i++)
  {
    if(val[i] == "fan") fan_switch = val[i+1].toInt();
    if(val[i] == "fan speed") fan_speed = val[i+1].toInt();
    if(val[i] == "drawer1") drawer_switch1 = val[i+1].toInt();
    if(val[i] == "drawer2") drawer_switch2 = val[i+1].toInt();
  }
  Serial.printf("fan switch: %d, fan speed: %d, drawer1: %d, drawer2: %d\n", fan_switch, fan_speed, drawer_switch1, drawer_switch2);
  fan_run(fan_switch, fan_speed);
  int a = drawer_move(drawer_switch1, drawer_switch2);
  
  if(a == 1){
      delay(10000);
      digitalWrite(trigger, LOW);
      delayMicroseconds(2);
      digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);
      duration = pulseIn(echo, HIGH);
      distanceCm = duration * SOUND_SPEED/2;
      if(distanceCm => 3){
       for (pos = 180; pos >= 0; pos -= 1) { 
        servo1.write(pos);             
        delay(15);                     
       }
      }
  }
}
