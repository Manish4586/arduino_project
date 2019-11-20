/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Telegram Contact : https://t.me/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/

// Start Pin Layout
int MQPin = 1;
int solenoidPin = 7;
int sensorThres = 900;
int LDRSensorPin = 3;
int forcePin = 2;
#define out 8
int LDRDetected;
int forceReading;
int solenoidThres;
// End Pin Layout

void setup(void) {
// Serial BPS debugging information via the Serial monitor
  Serial.begin(19200);
  pinMode(solenoidPin, OUTPUT);
  pinMode(MQPin, INPUT);
  pinMode(out, OUTPUT);
  pinMode(LDRSensorPin, INPUT);
  pinMode(forcePin, INPUT);
}

void loop(void) {
  int analogSensor = analogRead(MQPin);
  LDRDetected = digitalRead(LDRSensorPin);
// digitalWrite(out, HIGH);
// digitalWrite(out1, LOW);
  Serial.print("Default LDR reading = ");
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

  if (analogSensor > sensorThres)
  {  
  digitalWrite(solenoidPin, LOW);
  delay(analogSensor);
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
