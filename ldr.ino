#include <ESP8266WiFi.h>
#include "FirebaseArduino.h"

#define FIREBASE_HOST "weathermonitor-ab898.firebaseio.com"
#define FIREBASE_AUTH "9hpDXqVtvowYQKa5ouq4i9hX9i9ll81bARDDA2ML"
#define WIFI_SSID "alexstark"
#define WIFI_PASSWORD "Kingfisher"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
    
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value=analogRead(A0);
  float vlt = value*(5.0/1023.0);
  Firebase.setFloat("LDRvoltage", vlt);
  Serial.println(vlt);
}
