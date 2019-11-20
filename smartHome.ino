/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Telegram Contact : https://t.me/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/

// Start Pin Layout
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);
String command;
// End Pin Layout

void setup(void)

{
// Serial BPS debugging information via the Serial monitor
  BT.begin(19200);
  Serial.begin(19200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  while (BT.available())
  {
  delay(10);
  char c = BT.read();
  command += c;
  } 
  if (command.length() > 0)
  {
    Serial.println(command);
  if(command == "light on")
  {
    digitalWrite(2, HIGH);
  }
  else if(command == "light off")
  {
    digitalWrite(2, LOW);
  }
  else if (command == "lamp on")
  {
    digitalWrite (3, HIGH);
  }
  else if ( command == "lamp off")
 {
   digitalWrite (3, LOW);
 }
  else if (command == "fan on")
 {
   digitalWrite (4, HIGH);
 }
  else if (command == "fan off")
 {
   digitalWrite (4, LOW);
 }
  else if (command == "all on")
 {
   digitalWrite (2, HIGH);
   digitalWrite (3, HIGH);
   digitalWrite (4, HIGH);
 }
  else if (command == "off")
 {
   digitalWrite (2, LOW);
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
 }
command="";
 }
}
