/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Telegram Contact : https://t.me/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/

// Start Pin Layout
#define BLYNK_PRINT Serial
#define EspSerial Serial1
#include <SoftwareSerial.h>
#include<SPI.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#define ESP8266_BAUD 19200
ESP8266 wifi(&EspSerial);
// End Pin Layout

// Start Wifi Properties
char auth[] = "";
char ssid[] = "";
char pass[] = "";
// End Wifi Properties

// ESP8266 Properties
SoftwareSerial EspSerial(2, 3);
String s;

BLYNK_WRITE(V0)
{
  s=param.asStr();
  Serial.print(s);
  if(s=="on")
 {
  digitalWrite(7, LOW);
 }
  else if(s=="off")
 {
  digitalWrite(7, HIGH);
 }
}

void setup(void)
{
// Serial BPS debugging information via the Serial monitor
  Serial.begin(19200);
  pinMode(7,OUTPUT);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
 
  Blynk.begin(auth, wifi, ssid, pass);
}

void loop(void)
{
  Blynk.run();
}
