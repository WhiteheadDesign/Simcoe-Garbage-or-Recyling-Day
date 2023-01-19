#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
const int Garbage = 12;//SD3
const int Recycling = 11;//SD2

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);
  WiFi.begin("SSID", "Password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  timeClient.begin();
}

void loop() {
timeClient.update();

if(timeClient.getDay()==2){ // Day Counter starts at 0 for Sunday
  
  int week = (timeClient.getDay() + 6) / 7;

  if (week % 2 == 0) {
    Serial.println("Current week of the month is even. Recycling goes out");
    digitalWrite(Recycling, LOW);
  } else {
    Serial.println("Current week of the month is odd. Garbage goes out");
    digitalWrite(Garbage,LOW);
  }

  delay(1000);
 }
}
