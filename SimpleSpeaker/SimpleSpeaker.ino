/*
Attach the + of the speaker with a 220 Ohm resistor to pin 8 on Arduino
Attach the - of the speaker to GND
*/

#define NOTE_C4  262
int speakerPin = 8;
bool play = true;

void setup(){
  // initialize serial communication:
  Serial.begin(9600);
}

void loop(){

  if (play== true){
      playTone(NOTE_C4, 10);
      Serial.println("First Tone");
      playTone(NOTE_C4, 8);
      Serial.println("Second Tone");
      playTone(NOTE_C4, 4);
      Serial.println("Third Tone");
  }
}

void playTone(int note, int noteDuration){
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    
    int duration = 1000/noteDuration;
    tone(speakerPin, note,duration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speakerPin); 
}



