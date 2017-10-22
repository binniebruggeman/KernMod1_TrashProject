/*
 HC-SR04 ULTRASONIC SENSOR
 Range: 2 cm - 400 cm
 Resolution: 0,3 cm
 Echo (receives the signal) to Arduino pin 13
 Trig (sends the signal) to Arduino pin 12
 If connecting using a single pin, specify the same pin for both trigger_pin and echo_pin as the same pin is doing both functions
 VCC to arduino 5v, GND to arduino GND

 NEWPING LIBRARY METHODS
 sonar.ping(); - Send a ping, returns the echo time in microseconds or 0 (zero) if no ping echo within set distance limit
 sonar.ping_in(); - Send a ping, returns the distance in inches or 0 (zero) if no ping echo within set distance limit
 sonar.ping_cm(); - Send a ping, returns the distance in centimeters or 0 (zero) if no ping echo within set distance limit
 sonar.ping_median(iterations); - Do multiple pings (default=5), discard out of range pings and return median in microseconds
 sonar.convert_in(echoTime); - Converts microseconds to distance in inches
 sonar.convert_cm(echoTime); - Converts microseconds to distance in centimeters
 sonar.ping_timer(function); - Send a ping and call function to test if ping is complete.
 sonar.check_timer(); - Check if ping has returned within the set distance limit.
 timer_us(frequency, function); - Call function every frequency microseconds.
 timer_ms(frequency, function); - Call function every frequency milliseconds.
 timer_stop(); - Stop the timer.
 */


//Ultrasonic sensor
#include <NewPing.h>
#define NOTE_C4  262
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200 //maximum of ping distance in cm

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
bool trashDetected = false;

//Speaker
int speakerPin = 8;

void setup() {
  //Serial.begin(115200);
  Serial.begin(9600);
}

void loop() {
  //Ultrasonic sensor
  delay(50);
  int range = sonar.ping_cm();    //gets distance of object to sensor in cm and puts this in 'range'

  if ((range >= 1) && (range <= 15) && (range != 0)) { //if an object is detected within this range
    Serial.println("Trash detected!");  //print "Trash Detected" to the serial monitor
    trashDetected = true;   // set the boolean "trashDetected" to "true"
  }
  else {
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
  }

  //Sketch won't compile because of this part. Tried all sorts of things, also tried to put the tone function in the if range statement, but nothing works.
  if (trashDetected == true) {
    //Speaker
    Serial.println("TRUE!");  //print "Trash Detected" to the serial monitor
    playTone(NOTE_C4, 10);
    Serial.print("< 2");
    trashDetected = false; //set trashDetected to false again, otherwise the piezo will continu to beep
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






