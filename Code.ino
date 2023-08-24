#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#define ssid  "MAH-SHWAMP"
#define password  "nintendo"
const int Garbage = D5; //Green 1st and 3rd week of the month Odd
const int Recycling = D6; //Blue 2nd and 4th week of the month even

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  pinMode(Garbage, OUTPUT);
  pinMode(Recycling, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  timeClient.begin();
}

void loop() {
  timeClient.update();
  time_t currentTime = timeClient.getEpochTime();
  struct tm *timeInfo = gmtime(&currentTime);
  int currentWeek = (timeInfo->tm_yday - 1) / 7 + 1;
  if (currentWeek % 2 == 0) {
    Serial.println("Current week is even.");
    digitalWrite(Recycling , HIGH);
  }
  else {
    Serial.println("Current week is odd.");
    digitalWrite(Garbage, HIGH);
  }
  delay(1000);

}
