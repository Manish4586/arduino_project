/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Telegram Contact : https://t.me/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/

// Start Pin Layout
int MQPin0 = 1;
int solenoidPin = 10;
int sensorThres = 900;
int LDRSensorPin = 3;
int forcePin = 2;
int LDRDetected;
int forceReading;
// End Pin Layout

void setup() {
// Serial BPS debugging information via the Serial monitor
  Serial.begin(19200);
  pinMode(solenoidPin, OUTPUT);
  pinMode(MQPin0, INPUT);
  pinMode(LDRSensorPin, INPUT);
  pinMode(forcePin, INPUT);
}

void loop() {
  int analogSensor = analogRead(MQPin0);
  LDRDetected = digitalRead(LDRSensorPin);
  Serial.print("Default LDR reading = ");
  Serial.println(analogSensor);
  forceReading = analogRead(forcePin);
  Serial.print("Default Pressure reading = ");
  Serial.println(forceReading);  

// Online Ports
//  Serial.print("Online Ports: comA0, comA1, comA3, comD4, comD10, comD11, ");

  if (analogSensor > sensorThres)
  {  
  digitalWrite(solenoidPin, LOW);
  delay(analogSensor); //Wait 0 MS(debbuging)
  }
  else
  {
  Serial.print("Smoke Detected, ");
  digitalWrite(solenoidPin, HIGH);
  delay(sensorThres); //Wait 1 MS
 }

  if (LDRDetected < 100)
   {
  digitalWrite(solenoidPin, LOW);
 /* 
  delay(0); //Wait 0 MS(debbuging)
 */
  }
  else
  if (LDRDetected > 100)
  { 
  digitalWrite(solenoidPin, HIGH);
  delay(LDRDetected);
  delay(0);//Wait 0 MS
  }

 if (forceReading == 0)
   {
  digitalWrite(solenoidPin, HIGH);
  delay(0); //Wait 0 MS(debbuging)
  }
  else
  if (forceReading == 1023)
  { 
  digitalWrite(solenoidPin, LOW);
  delay(0);
  }
}
