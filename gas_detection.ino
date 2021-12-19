/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging (Not For Production)
*/

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
 
byte heart[8] = 

              {

                0b00000,

                0b01010,

                0b11111,

                0b11111,

                0b11111,

                0b01110,

                0b00100,

                0b00000

              };
// Start Pin Layout
int MQPin = 0;
int solenoidPin = 7;
int sensorThres = 900;
int LDRSensorPin = 3;
int forcePin = 2;
int spk = 6;
int panel = 10; //Panel Properties By Manish4586
//int out = 8;
SoftwareSerial mySerial(3, 2);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
int LDRDetected;
int forceReading;
int solenoidThres;
// End Pin Layout

void setup(void) {
// Serial BPS debugging information via the Serial monitor
  Serial.begin(19200);
  mySerial.begin(19200);
  pinMode(solenoidPin, OUTPUT);
  pinMode(MQPin, INPUT);
  pinMode(spk,OUTPUT);
//  pinMode(out, OUTPUT);
  pinMode(LDRSensorPin, INPUT);
  pinMode(forcePin, INPUT);
  pinMode(panel, OUTPUT); //Panel Properties By Manish4586
  analogWrite(panel, 190); //No Longer Using Potentiometer To Determine Panel Backlight Intensity By Manish4586
 // Begin LCD Properties
  lcd.createChar(1, heart);
  lcd.begin(16,2);
  lcd.print("Initialising....");
  delay(1000);
  lcd.clear();
  lcd.print("Gas ");
  lcd.setCursor(0,1);
  lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);
  delay(2000);
  lcd.clear();
 // End LCD Properties
}

void loop(void) {
/*  lcd.setCursor(0, 1);
  lcd.print(millis() / 9000); */
  tone(spk, 1000);
  noTone(spk);
  int analogSensor = analogRead(MQPin);
  Serial.print("Default LDR reading = ");
  digitalWrite(spk, LOW);
  LDRDetected = digitalRead(LDRSensorPin);
  Serial.println(LDRDetected);
  lcd.print("        ");
  lcd.setCursor(0,0);
  lcd.print("LDR:");
  lcd.print(LDRDetected);
  lcd.setCursor(0,1);
  //lcd.print("        ");
  lcd.print("Gas Int:");
  lcd.print(analogSensor);
  lcd.print("        ");
  Serial.print("Default Gas reading = ");
  Serial.println(analogSensor);
{
  forceReading = analogRead(forcePin);
  Serial.print("Default Load reading = ");
  Serial.println(forceReading);
  solenoidThres = map(forceReading, 0, 1023, 0, 255);
  analogWrite(solenoidPin, solenoidThres);
  delay(0);  
}
// Online Ports
//  Serial.print("Online Ports: comA0, comA1, comA2, comA3, comD4, comD10, comD11, ");

  if (analogSensor<sensorThres)
  {  
  digitalWrite(solenoidPin, LOW);
  delay(sensorThres);
  }
  else
  {
  SendMessage();
  digitalWrite(spk, HIGH);
  Serial.print("Gas Detected, ");
  digitalWrite(solenoidPin, HIGH);
  delay(sensorThres);
 }
 
  if (LDRDetected < 100)
   {
  digitalWrite(solenoidPin, LOW);
  
// delay(0); //Wait 0 MS(debbuging)
  }
  else
  if (LDRDetected > 100)
  { 
  digitalWrite(solenoidPin, HIGH);
  delay(LDRDetected);
  delay(0); //Wait 0 MS
  }

lcd.clear();
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");
  delay(100);
  mySerial.println("AT+CMGS=\"+918794034586\"\r");
  delay(100);
  mySerial.println("Gas Leaking! Please Turn Off Regulator");
  delay(100);
  mySerial.println((char)26);
}
