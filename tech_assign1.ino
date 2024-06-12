#include <HTTPClient.h>
#include <WiFi.h>


const int LDRPin = 34; 

const char* ssid = "2602";         
const char* password = "fillah26"; 
const char* serverName = "http://192.168.123.1:5000/sensorldr"; 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    int ldr = analogRead(LDRPin);
    float ldrvalue = ((ldr / 4095.00) * 100); // 
    Serial.print ("ldrvalue = ");
    Serial.print (ldrvalue);

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"ldrvalue\":" + String(ldrvalue) + "}";
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
  } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(10000); 
}
