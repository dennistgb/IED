#include <HttpClient.h>
#include <b64.h>

#include <ArduinoHttpClient.h>



#include <ArduinoJson.h>
#include <ArduinoJson.hpp>






#include <ESP8266WiFi.h>
#define SSID "Hello World"
#define PW "owe$pay$"
#define BASEURL "https://ap-southeast-1.aws.data.mongodb-api.com/app/application-0-zpzys/endpoint/"
#define SECRECT ""
#define LED 1
#define SW 0
StaticJsonDocument<200> jsonBuffer;
int get_state(){
  HttpClient http;

  String serverPath = BASEURL + "getstate/?secret=" + SECRECT;

  // Your Domain name with URL path or IP address with path
  http.begin(serverPath.c_str());

  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

  // Send HTTP GET request
  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    JsonObject& output =jsonBuffer.parseObject(payload);
    Serial.println(payload);
    return (int)output["pc_button_hold_time"]
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}

int set_led(){
  HTTClient http;
  
  String serverPath = BASEURL + "getstate/?secret=" + SECRECT+"led="+to_string(digitalRead(LED));

  // Your Domain name with URL path or IP address with path
  http.begin(serverPath.c_str());

  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

  // Send HTTP GET request
  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    JsonObject& output =jsonBuffer.parseObject(payload);
    Serial.println(payload);
    return (int)output["pc_button_hold_time"]
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}






void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(SSID, PW);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sleep(1000);
  if(WiFi.status()== WL_CONNECTED){
    int time=get_state()
    set_led()
    if (time>0){
      digitalWrite(SW,HIGH);
      sleep(1000*time);
      digitalWrite(SW,LOW);
      get_state();
    }
  }

}
