/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Telegram Contact : https://t.me/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/

const int ledPin = 4;
const int ldrPin = A0;

void setup() {
// Serial BPS debugging information via the Serial monitor
  Serial.begin(19200);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus <= 500) {
  digitalWrite(ledPin, LOW);
  Serial.println(ldrStatus);
}
else
{
digitalWrite(ledPin, HIGH);
Serial.println(ldrStatus);
    }

}
