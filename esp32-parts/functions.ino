String get_data(void) {
   Serial.println("command receiving from cloud");
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read";
   Serial.println("Making a request");
   http.begin(url.c_str());
   http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
   int httpCode = http.GET();
   String payload;
   if (httpCode > 0) {
       if(httpCode == HTTP_CODE_OK) {
        payload = http.getString();
        Serial.println(payload);
    }
   }
   else Serial.printf("HTTP Request failed, error: %s\n", http.errorToString(httpCode).c_str());
   http.end();
   return payload;
}

void sensor_data_send(void){
  Serial.println("sensor data sending..........");
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2);  
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if(httpCode > 0){
   if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
      Serial.println("data send successfully");
    }
  }
  else Serial.printf("HTTP Request failed, exception: %s\n", http.errorToString(httpCode).c_str());
  http.end();

}
void fan_run(int fan_switch, int fan_speed){
   Serial.println(fan_switch);
  if(fan_switch == 1){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel, fan_speed*2.5);
    delay(1000);   
    Serial.printf("the fan is running, speed: %f\n", fan_speed); 
  }
  if(fan_switch == 0 || fan_speed == 0){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);  
    Serial.println("fan is off");
  }
}


int drawer_move(int drawer_switch1, int drawer_switch2)
{
  if(drawer_switch1 == 1){
     for (pos = 0; pos <= 180; pos += 1) { 
      servo1.write(pos);
      delay(20);
     }
    return 1;
  }
   
  if(drawer_switch2 == 1){
     for (pos = 0; pos <= 180; pos += 1) { 
      servo2.write(pos);
      delay(15);
     }
  }
  else return 0;
}
