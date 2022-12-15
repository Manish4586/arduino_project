/*
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging (Not For Production)
*/
 
/* LCD RS pin to digital pin 12
LCD Enable pin to digital pin 11
LCD Backlight pin to digital 10
LCD D4 pin to digital pin 5
LCD D5 pin to digital pin 4
LCD D6 pin to digital pin 9
LCD D7 pin to digital pin 7 */
 
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h>
Servo servo;
SoftwareSerial mySerial(0, 1);
LiquidCrystal lcd(12,11,5,4,9,7);
int MQPin = A0;
int sensorThres = 200;
int speaker = 6;
int ledRED = A1;
int ledGREEN = A2;
int panel = 3; //Panel Properties By Manish4586
int servoPin = 10;
//int servPos = 0;
int servShift = 8;
long distance;
void setup()
{
 pinMode(MQPin, INPUT);
 pinMode(speaker,OUTPUT);
 servo.attach(servoPin);
 //servo.write(servPos);
 pinMode(panel, OUTPUT); //Panel Properties By Manish4586
 analogWrite(panel, 250); //No Longer Using Potentiometer To Determine Panel Backlight Intensity By Manish4586
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
//digitalWrite(speaker, LOW);
analogWrite(ledGREEN, 200);
analogWrite(ledRED, 0);
noTone(speaker);
servo.write(0);
if(distance <= 10){
servo.write(90);}
delay(1000);
}
else
{
servo.write(0);
if(sensorThres <= 10){
servo.write(90);
delay(15);
}
analogWrite(ledRED, 150);
analogWrite(ledGREEN, 0);
digitalWrite(speaker, HIGH);         
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Exceed");
lcd.setCursor(0,1);
lcd.print("Warning...!");
Call();
Call1();
Sms();
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
  Serial.println();
  updateSerial();
}
 
void Call1()
{
  mySerial.println("ATD+ +918794034586;");
  updateSerial();
}
 
void Sms()
{
  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CMGS=\"+918638294781\"");
  updateSerial();
  mySerial.println("Gas Leaking! Please Turn Off Regulator");
  updateSerial();
  mySerial.println((char)26);
}
