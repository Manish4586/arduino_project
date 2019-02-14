/* 
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Telegram Contact : https://t.me/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/

// Start Pin Layout
int smokeA0 = A1;
int solenoidPin = 10;
int LEDpin = 11;
int sensorThres = 100;
int flame_sensor = 4;
int fsrAnalogPin = 3;
int flame_detected;
int LEDbrightness;
int fsrReading;
// End Pin Layout

void setup() {
// Serial BPS debugging information via the Serial monitor
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(flame_sensor, INPUT) ;
    pinMode(LEDpin, OUTPUT);
}

void loop() {
  int analogSensor = analogRead(smokeA0);
  int flame_detected = digitalRead(flame_sensor);
/*
 Connect one end of FSR to 5V, the other end to Analog 3.
 Then connect one end of a 10K resistor from Analog 3 to ground
 Connect LED from pin 11 through a resistor to ground 
 * FRS Reading = (0-1023)
 * analogWrite = (0-255) 
*/
  int fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Default FRS reading = ");
  Serial.println(fsrReading);
  int LEDbrightness = map(fsrReading, 0, 1015, 0, 240);
  analogWrite(LEDpin, LEDbrightness);  

// Online Ports
  Serial.print("Online Ports: comA0, comA1, comA3, comD4, comD10, comD11, ");
  Serial.println(analogSensor);

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
 /* delay(100); //Wait 1 MS
 */ }

 if (flame_detected == 1)
   {
  digitalWrite(solenoidPin, HIGH);
 /* delay(0); //Wait 0 MS(debbuging)
 */
  }
  else
  { 
  digitalWrite(solenoidPin, LOW);
  delay(0); //Wait 0 MS
  }
  delay(100);
}
