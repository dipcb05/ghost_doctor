void data_read(void) {
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read";
  Serial.println("Making a request");
  http.begin(url.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  String payload;
    if (httpCode > 0) {
        payload = http.getString();        
        Serial.println(httpCode);
        Serial.println(payload);
      }
    else {
      Serial.println("Error on HTTP request");
    }
  http.end();
}

void data_send(void){
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2) +"&value3=" + String((int)value3);  
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if(httpCode > 0){
   if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
    }
  }
  else Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  http.end();
}

float getLightPercentage(void){
  int ldrRawVal;
  float percentage;
  ldrRawVal = analogRead(LDR_PIN);    
  percentage = ((float)((ldrRawVal*100)/4096));
  return percentage;
}
