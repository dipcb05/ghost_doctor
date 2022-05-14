String data_read(void) {
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
    }
   }
  else Serial.println("Error on HTTP request");
  http.end();
  return payload;
}

void data_send(void){
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2);  
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if(httpCode > 0){
   if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      //Serial.println(payload);
      Serial.println("data send successfully");
    }
  }
  else Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  http.end();
}


void fan_run(String com){
  
  int fan_com = com.toInt();
  int Comma = com.indexOf(",");
  int fan_speed = com.substring(Comma+1).toInt();
 
  if(fan_com == 1){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel, fan_speed*2.5);
    delay(1000);   
  }
  if(fan_com == 0){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);  
  }
}
