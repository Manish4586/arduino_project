/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Telegram Contact : https://t.me/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/

// Start Pin Layout
int MQAnalogPin0 = 1;
int solenoidPin = 10;
int LEDpin = 11;
int sensorThres = 100;
int IRSensor = 4;
int fsrA = 3;
int IRDetected;
int LEDbrightness;
int fsrReading;
// End Pin Layout

void setup() {
// Serial BPS debugging information via the Serial monitor
  Serial.begin(19200);
  pinMode(solenoidPin, OUTPUT);
  pinMode(MQAnalogPin0, INPUT);
  pinMode(IRSensor, INPUT) ;
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  int analogSensor = analogRead(MQAnalogPin0);
  int IRDetected = digitalRead(IRSensor);
  Serial.println(analogSensor);
/*
 Connect one end of FSR to 5V, the other end to Analog 3.
 Then connect one end of a 10K resistor from Analog 3 to ground
 Connect LED from pin 11 through a resistor to ground 
 * FSR Reading = (0-1023)
 * analogWrite = (0-255) 
*/
  int fsrReading = analogRead(fsrA);
  Serial.print("Default FSR reading = ");
  Serial.println(fsrReading);
  int LEDbrightness = map(fsrReading, 0, 1023, 0, 250);
  analogWrite(LEDpin, LEDbrightness);  

// Online Ports
  Serial.print("Online Ports: comA0, comA1, comA3, comD4, comD10, comD11, ");

  if (analogSensor > sensorThres)
  {
  Serial.print("No Smoke Detected, ");    
  digitalWrite(solenoidPin, LOW);
  delay(0); //Wait 0 MS(debbuging)
  }
  else
  {
  Serial.print("Smoke Detected, ");
  digitalWrite(solenoidPin, HIGH);
 /*
  delay(100); //Wait 1 MS
 */ }

 if (IRDetected == 1)
   {
  digitalWrite(solenoidPin, HIGH);
 /* 
  delay(0); //Wait 0 MS(debbuging)
 */
  }
  else
  { 
  digitalWrite(solenoidPin, LOW);
  delay(0); //Wait 0 MS
  }
  delay(100);
}
