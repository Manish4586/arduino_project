/* 
* Copyright (c) 2019, 2020 Open Source Arduino Projects
*  Arduino Projects By Manish4586 & Karan
*  Source Code : https://GitHub.com/Manish4586
*  Author : Manish4586 <manish.n.manish45@gmail.com>
*  Status : Debug
*/

// Start Pin Layout
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <Wire.h> 
#include <Keypad.h>
int MQPin = 0;
int solenoidpin = 7;
int panel = 10; //Panel Properties By Manish4586 <manish.n.manish45@gmail.com>
int ldrsensor;
int orcepin;
int out;
int thresh = 700;
int force = 2;
int password;
//int irSensor;
//int flameSensor;
int ldrdetected;
int forceresding;
int solenoidthresh;
//LiquidCrystal_I2C lcd(0x21, 16, 2); 
LiquidCrystal lcd(12,11,5,4,9,6);
// End Pin Layout

#define Password_Length 4

char Data[Password_Length]; 
char Master[Password_Length] = "1234"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {A2, A3, A4, A5};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(19200);
 // pinMode(irSensor,INPUT);
 // pinMode(flameSensor,INPUT);
  pinMode(relay,OUTPUT);
  pinMode(force,INPUT);
  pinMode(gasSensor,INPUT);
  pinMode(panel,OUTPUT); //Panel Properties By Manish4586 <manish.n.manish45@gmail.com>
  analogWrite(panel,115); //No Longer Using Potentiometer To Determine Panel Backlight Intensity Instead Using Digital Value To Set Electrical Changes Are Done To Support It So Check Circuit Diagram Before Changing Default Value By Manish4586 <manish.n.manish45@gmail.com>
 // Begin LCD Properties
  lcd.begin(16,2);
 // End LCD Properties
}

void loop() {
 /* if (pass() == false ){
    Serial.println("password in incorrect");
    lcd.setCursor(0,0);
      lcd.print("                     "); 
    lcd.print("password is incorrect");
  }else{*/
  if(pass() == true){
    digitalWrite(relay,HIGH);
    while(digitalRead(relay)==HIGH){  //we check if the the solenoid is on (LOOP 1)
        lcd.setCursor(0,1);
        lcd.print("        ");
        int MQPin = analogRead(MQPin);
        lcd.setCursor(0,1);
        lcd.print(MQPin);
      if (digitalRead(force)==HIGH){  //we check if force sensor is on i.e something is kept intop
        //we want the relay to be high if the force sensor is on
         if(MQPin > thresh){   //check whether for gas sensor high means gas or vice versa
         digitalWrite(relay,LOW);//if we find gase sensor on break LOOP 1
          Serial.println("gas is on,selenoid is switch off ");
          lcd.setCursor(0,0);
          lcd.print("gas is high solenoid is offed");
          lcd.setCursor(0,1);
          lcd.print(MQPin);
        }
      }
      
      else{
        int counter = 1;
        while(digitalRead(force)==LOW && counter<= 5){    //check for 5sec i.e. each loop is 1sec if the sensor is high then break the loop
          Serial.println("lift off");
            delay(10000);
            Serial.println(counter);
            if(counter==5){   //if it becomes 5sec then off the sensor
              digitalWrite(relay,LOW);// breaks the LOOP 1
              Serial.println("solenoid is off");
              break;
            }
            //digitalWrite(relay,HIGH);
            counter = counter + 1;
        }
        if(MQPin>thresh){    //check whether for gas sensor high means gas or vice versa
          digitalWrite(relay,LOW);    //if we find gas sensor on make relay off , breaks the LOOP 1
          Serial.println("gas is on,selenoid off "); 
          lcd.setCursor(0,0);
          lcd.print("gas is high solenoid is offed");
        lcd.setCursor(0,1);
        lcd.print("        ");
          lcd.setCursor(0,1);
          lcd.print(MQPin);         
        }
      }
    }
  }
}
bool pass(){
  lcd.setCursor(0,0);
  //lcd.print("                  ");
  lcd.print("Enter Password:");
 Serial.println("enter the password");
 bool looppass=true;
while(looppass){

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]);
    Serial.println(Data[data_count]);
    data_count++; 
    }

  if(data_count == Password_Length-1){
    //lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.print("Correct");
      Serial.println("correct");
      //digitalWrite(signalPin, HIGH); 
      //delay(10000);
      clearData();  
      return true;
      }
    else{
      lcd.print("Incorrect");
      Serial.println("incorecct");
     // digitalWrite(signalPin, LOW);
     // delay(10000);
     // clearData();  
      }
    
    lcd.clear();
    clearData();  
  }
}
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
}
