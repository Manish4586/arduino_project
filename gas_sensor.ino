/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging (Not For Production)
*/

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
int MQPin = A0;
int sensorThres = 200;
int speaker = 6;
int panel = 13; //Panel Properties By Manish4586

void setup()
{
 pinMode(MQPin, INPUT);
 pinMode(speaker,OUTPUT);
 pinMode(panel, OUTPUT); //Panel Properties By Manish4586
 analogWrite(panel, 190); //No Longer Using Potentiometer To Determine Panel Backlight Intensity By Manish4586
 int analogSensor = analogRead(MQPin);
 mySerial.begin(9600);
 Serial.begin(9600);
 lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print("Initializing...");
 lcd.setCursor(0,1);
 lcd.print("GSM Module...");
 delay(3000);
 mySerial.println("AT");
 updateSerial();
 mySerial.println("ATI");
 updateSerial();
 mySerial.println("AT+CSQ");
 updateSerial();
 mySerial.println("AT+CCID");
 updateSerial();
 mySerial.println("AT+CREG?");
 updateSerial();
 lcd.clear();
}
 
void loop()
{
int analogSensor = analogRead(MQPin);
digitalWrite(speaker, LOW);
tone(speaker, 2000);
noTone(speaker);
/* Serial.print("Gas Level: ");
Serial.println(analogSensor); */
lcd.setCursor(0,0);
lcd.print ("Gas Detection ON");
/*lcd.print("Gas Level: ");
lcd.print(analogSensor); */
delay(1000);
 
if ( analogSensor<sensorThres)
{
//lcd.clear();
lcd.setCursor(0,1);
lcd.print("Gas Level Normal");
delay(1000);
}
else
{
digitalWrite(speaker, HIGH);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Exceed");
lcd.setCursor(0,1);
lcd.print("Warning...!");
Call();
Call1();
Sms();
delay(9000);
}
 
lcd.clear();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
}

void Call()
{
  mySerial.println("ATD+ +916000838157;");
  updateSerial();
  delay(10000);
  mySerial.println("ATH");
  updateSerial();
}

void Call1()
{
  mySerial.println("ATD+ +918794034586;");
  updateSerial();
}

void Sms()
{
  mySerial.println("ATD+ +918794034586;");
  updateSerial();
  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CMGS=\"+918638294781\"");
  updateSerial();
  mySerial.print("Gas Leaking! Please Turn Off Regulator");
  updateSerial();
  mySerial.write(26);
}
