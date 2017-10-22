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
bool trashDetected = false;

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
  
  if (distance < 2) {
    playTone(NOTE_C4, 10);
    Serial.print("< 2");
  } else  if (distance < 4) {
    playTone(NOTE_C4, 8);
    Serial.print("< 4");
  } else if (distance < 5) {
    playTone(NOTE_C4, 7);
    Serial.print("< 5");
  } else if (distance < 6) {
    playTone(NOTE_C4, 5);
    Serial.print("< 6");
  } else if (distance < 10) {
    playTone(NOTE_C4, 4);
    Serial.print("< 10");
  } else if (distance < 20) {
    playTone(NOTE_C4, 3);
    Serial.print("< 20");
  } else if (distance < 25) {
    playTone(NOTE_C4, 2);
    Serial.print("<25");
  } else if (distance < 30) {
    playTone(NOTE_C4, 1);
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
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return (microseconds/2) / 29.1;
}

