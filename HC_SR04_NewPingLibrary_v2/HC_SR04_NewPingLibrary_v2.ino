/*
 HC-SR04 Ultrasonic Sensor
 Range: 2 cm - 400 cm
 Resolution: 0,3 cm
 Echo (receives the signal) to Arduino pin 13
 Trig (sends the signal) to Arduino pin 12
 If connecting using a single pin, specify the same pin for both trigger_pin and echo_pin as the same pin is doing both functions
 VCC to arduino 5v, GND to arduino GND
 
 METHODS
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

#include <NewPing.h>
 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 4000 //maximum of ping distance in cm
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  //Serial.begin(115200);
  Serial.begin(9600);
}
 
void loop() {
  delay(50);

  //get distance to object in cm
  float range = sonar.ping_cm();
  if ((range >= 1) && (range <= 10) && (range != 0)){
    Serial.println("Trash detected!");
    }
    else {
      Serial.print("Ping: ");
      Serial.print(sonar.ping_cm());
      Serial.println("cm");
      }
}
