#include "headers.h"

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
  pinMode(SENSOR_PIN, INPUT);
  
  //temp sensor
  dht.begin();
  
  //drawer
  servo1.attach(13);  // servo1
  servo2.attach(15); //servo2

  connect_wifi();
}

void loop() {
  value1 = dht.readHumidity();
  value2 = dht.readTemperature();
  value3 = decibel_Value();
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
