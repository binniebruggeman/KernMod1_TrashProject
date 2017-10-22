/*
 HC-SR04 Ultrasonic Sensor
 Range: 2 cm - 400 cm
 Resolution: 0,3 cm
 Echo (receives the signal) to Arduino pin 13
 Trig (sends the signal) to Arduino pin 12
 VCC to arduino 5v, GND to arduino GND
 */
 
#define trigPin 12
#define echoPin 13
 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
