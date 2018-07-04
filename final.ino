
#include <ESP8266WiFi.h>
#include "FirebaseArduino.h"
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#include "UbidotsMicroESP8266.h"

#define dht_dpin D1


DHT dht(dht_dpin, DHTTYPE); 

#define TOKEN "BBFF-YrySyZe4jSdbpg0xwpM4PrVPvheCYJ" //This is for Ubidots Integration
#define FIREBASE_HOST "weathermonitor-ab898.firebaseio.com"  //This is the FidrebaseDB URL
#define FIREBASE_AUTH "9hpDXqVtvowYQKa5ouq4i9hX9i9ll81bARDDA2ML"
#define WIFI_SSID "Lel"
#define WIFI_PASSWORD "0zxcvbnm"

Ubidots client(TOKEN);

void setup(void)
{ 
  pinMode(D5,OUTPUT);
  pinMode(D4,INPUT);
  dht.begin();
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
  
  Serial.println("Humidity and temperature\n\n");
  delay(700);

}
void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();        
    float duration_f,distance_f; 

    Firebase.setFloat("Humidity", h);
    /* if (Firebase.failed()) {
      Serial.print("pushing /Humidity failed:");
      Serial.println(Firebase.error());  
     
    }*/
    Firebase.setFloat("Temperature", t);
  // handle error
    if (Firebase.failed()) {
      Serial.print("pushing /Temperature failed:");
      Serial.println(Firebase.error());  
     
    }

    

    
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("Temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    digitalWrite(D5,0);
    delayMicroseconds(2);
    digitalWrite(D5,1);
    delayMicroseconds(10);
    digitalWrite(D5,0);
    duration_f=pulseIn(D4,1);
    distance_f=duration_f*(0.034/2);

    //I've Considered the lenght of the rain gauge is 25 cm 
    float amtRain=25-distance_f;
    Serial.println(amtRain);

     Firebase.setFloat("AmountOfRF", amtRain);
  
  // handle error
    /*if (Firebase.failed()) {
      Serial.print("pushing /AmountOfRF failed:");
      Serial.println(Firebase.error());  
     
    }
    */
    delay(200);
    double sensorValue;
    sensorValue = analogRead(A0);
    double sensor_volt = sensorValue/1024*5.0;
    double RS_gas = (5.0-sensor_volt)/sensor_volt;
    double R0 = RS_gas/(26+(1/3));
    
    Firebase.setFloat("AmountOfCO", R0);
  
  // handle error
    /*if (Firebase.failed()) {
      Serial.print("pushing /AmountOfCO failed:");
      Serial.println(Firebase.error());  
      
    }
    */
    Serial.print("CO :");
    Serial.print(R0);
    Serial.println("*10^(-4) moles ");
    delay(1000);

    //Uploading to UBIDOTS :
    client.add("Temperature", t);
    client.add("Humidity", h);
    client.add("CO", R0);
    client.add("amtRainfall", amtRain);
    client.sendAll(true);
    
}
