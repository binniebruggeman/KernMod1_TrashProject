/*
 HC-SR04 Ultrasonic Sensor
 Range: 2 cm - 400 cm
 Resolution: 0,3 cm
 Echo (receives the signal) to Arduino pin 13
 Trig (sends the signal) to Arduino pin 12
 If connecting using a single pin, specify the same pin for both trigger_pin and echo_pin as the same pin is doing both functions
 VCC to arduino 5v, GND to arduino GND
 */

#define NOTE_C4  262

//Ultrasonic sensor
int trigPin = 12;
int echoPin = 11;

bool trashDetection = false;

//Speaker
int speakerPin = 8;

void setup() {
  //Ultrasonic sensor
  pinMode (2, OUTPUT); //attach vcc to pin 2 on Arduino
  pinMode (5, OUTPUT); //attach GND to pin 5 on Arduino

  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  digitalWrite(2, HIGH);
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters.
  long duration, distance;

  // The ping is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse.
  pinMode(trigPin, OUTPUT);// attach pin 3 to Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  // The same pin is used to read the signal from the ping. The ping is a
  // HIGH pulse, whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode (echoPin, INPUT);//attach pin 4 to Echo
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance in cm
  distance = microsecondsToCm(duration);

  if (distance > 1 && distance < 15) {
    trashDetection = true;
    playTone(NOTE_C4, 3);
    Serial.print("Trash detected at: ");
    Serial.print(distance);
    Serial.println(" cm");
    trashDetection = false;
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
//    delay(100);
  }
}


void playTone(int note, int noteDuration) {
  // to calculate the note duration, take one second divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

  int duration = 1000 / noteDuration;
  tone(8, note, duration);

  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = duration * 1.30;
  delay(pauseBetweenNotes);
  // stop the tone playing:
  noTone(8);
}

long microsecondsToCm(long microseconds) {
  //The soundwave is travelling from the sensor to the object and back again from
  //the object to the sensor. Therefor to get the distance to the object (in microsenconds)
  //we need to devide it by 2. Next we devide by 29.1 to get a distance in cm.
  return (microseconds / 2) / 29.1;
}

