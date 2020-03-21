/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/
/* LCD RS pin to digital pin 12
LCD Enable pin to digital pin 11
LCD Backlight pin to digital 10
LCD D4 pin to digital pin 5
LCD D5 pin to digital pin 4
LCD D6 pin to digital pin 9
LCD D7 pin to digital pin 6 */
#include <LiquidCrystal.h>
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
int panel = 10; //Panel Properties By Manish4586 <manish.n.manish45@gmail.com>
//int out = 8;
LiquidCrystal lcd(12, 11, 5, 4, 9, 6);
int LDRDetected;
int forceReading;
int solenoidThres;
// End Pin Layout

void setup(void) {
// Serial BPS debugging information via the Serial monitor
  Serial.begin(19200);
  pinMode(solenoidPin, OUTPUT);
  pinMode(MQPin, INPUT);
//  pinMode(out, OUTPUT);
  pinMode(LDRSensorPin, INPUT);
  pinMode(forcePin, INPUT);
  pinMode(panel, OUTPUT); //Panel Properties By Manish4586 <manish.n.manish45@gmail.com>
  analogWrite(panel, 190); //No Longer Using Potentiometer To Determine Panel Backlight Intensity Instead Using Digital Value To Set Electrical Changes Are Done To Support It So Check Circuit Diagram Before Changing Default Value By Manish4586 <manish.n.manish45@gmail.com>
 // Begin LCD Properties
  lcd.createChar(1, heart);
  lcd.begin(16,2);
  lcd.print("Initialising....");
  delay(1000);
  lcd.clear();
  lcd.print("Gas Project");
  lcd.setCursor(0,1);
  lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);lcd.write(1);
  delay(2000);
  lcd.clear();
 // End LCD Properties
}

void loop(void) {
/*  lcd.setCursor(0, 1);
  lcd.print(millis() / 9000); */
  int analogSensor = analogRead(MQPin);
  Serial.print("Default LDR reading = ");
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
}
