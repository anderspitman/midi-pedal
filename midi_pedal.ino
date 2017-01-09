#include <MIDI.h>



// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int lastButtonState = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 2;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  MIDI.begin();
}

void loop() {
  // read the state of the pushbutton value:
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;
      
      // check if the pushbutton is pressed.
      // if it is, the buttonState is HIGH:
      if (buttonState == HIGH) {
        // turn LED on:
        digitalWrite(ledPin, HIGH);
  
        MIDI.sendNoteOn(42, 127, 1);
        
      } else {
        // turn LED off:
        digitalWrite(ledPin, LOW);
      }
    }
  }

  lastButtonState = reading;

  MIDI.read();
}
