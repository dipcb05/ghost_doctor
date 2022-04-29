#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <Wire.h>

#define LDR_PIN   22
#define DHTPIN    23
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure client;

const int LEDPIN = 2; 
const int PushButton = 4; 
const char * ssid = "Dip-Home";
const char * password = "abcd1234";
String GOOGLE_SCRIPT_ID = "AKfycbwmRJJ6peenhED0VEbfC5q3-m_0EserVZzlGAjv5To4_YDJdkU_WLIt-M9vBpPyO25JVg";
const int sendInterval = 5000; 

String server = "http://maker.ifttt.com";
String eventName = "new_data";
String IFTTT_Key = "oLPl3VTknlSUN7TkYGosXWbJR10xMF3Onmf9_ws9-Cy";
String IFTTTUrl="https://maker.ifttt.com/trigger/new_data/with/key/oLPl3VTknlSUN7TkYGosXWbJR10xMF3Onmf9_ws9-Cy";

int value1, value2, value3;

void setup() {

  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Wifi Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("Connected !!!");
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
