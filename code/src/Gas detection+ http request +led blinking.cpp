#include "ESP8266WiFi.h"
#include <Ethernet.h>
#include <SPI.h>
byte ip[] = { 192, 168, 10, 113 };
int buzzer = D5;
int LED = D1;
int smokeA0 = A0;

const char* SSID="WifiM2M";
const char* password ="0wifim2m";
// Your threshold value. You might need to change it.
int sensorThres = 350;

void setup() {
 pinMode(buzzer, OUTPUT);
 pinMode(smokeA0, INPUT);
 pinMode(LED, OUTPUT);
 Serial.begin(9600);

Serial.println();
WiFi.disconnect();
WiFi.mode(WIFI_STA);
Serial.print("Connecting to");
Serial.println(SSID);
WiFi.begin(SSID,password);

while (WiFi.status()!= WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
Serial.println("");
Serial.println("Connected to WiFi");
}

void loop() {
 int analogSensor = analogRead(smokeA0);

 Serial.print("Pin A0: ");
 Serial.println(analogSensor);
 WiFiClient client;

 // Checks if it has reached the threshold value
 if (analogSensor > sensorThres)
 {
   tone(buzzer, 1000, 200);
   digitalWrite(LED, HIGH);// turn the LED off.(Note that LOW is the voltage level but actually
                      //the LED is on; this is because it is acive low on the ESP8266.
   delay(1000);          // wait for 1 second.
   digitalWrite(LED, LOW); // turn the LED on.
   delay(1000);         // wait for 1 second.

   // Use WiFiClient class to create TCP connections
   if (!client.connect(ip, 8000))
   {  //host : Ip server
    Serial.println("connection failed");
    delay(5000);
    return;
  }
  else
  // This will send a string to the server
  client.println("Gaz detecte");
 }
 else
 {
   noTone(buzzer);
 }
 delay(100);
}
