#include <MIDI.h>


const int ledPin =  13;
const int buttonsCount = 2;
const int inPins[buttonsCount] = {2, 3};

int buttonStates[buttonsCount];
int lastButtonStates[buttonsCount];
unsigned long lastDebounceTimes[buttonsCount];

unsigned long debounceDelay = 2;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  for (int buttonIndex = 0; buttonIndex < buttonsCount; buttonIndex++) {
    buttonStates[buttonIndex] = 0;
    lastButtonStates[buttonIndex] = 0;
    lastDebounceTimes[buttonIndex] = 0;
    pinMode(inPins[buttonIndex], INPUT);
  }

  MIDI.begin();
}

void loop() {

  for (int buttonIndex = 0; buttonIndex < buttonsCount; buttonIndex++) {
    processButton(buttonIndex);
  }

  MIDI.read();
}

void processButton(int buttonIndex) {
  
  if (buttonStateChanged(buttonIndex)) {
    if (getButtonState(buttonIndex) == HIGH) {
      digitalWrite(ledPin, HIGH);

      //blinkNumberOfTimes(inPins[buttonIndex]);
    
      MIDI.sendNoteOn(42 + buttonIndex, 127, 1);
          
    }
    else {
      digitalWrite(ledPin, LOW);
    }
  } 
}

bool buttonStateChanged(int buttonIndex) {
  int reading = digitalRead(inPins[buttonIndex]);
  
  if (reading != lastButtonStates[buttonIndex]) {
    resetDebounceTimer(buttonIndex);
  }
  
  if (debounceTimerExpired(buttonIndex)) {
  
    if (reading != getButtonState(buttonIndex)) {
      setButtonState(buttonIndex, reading);

      return true;
    }
  }

  lastButtonStates[buttonIndex] = reading;

  return false;
}

int getButtonState(int buttonIndex) {
  return buttonStates[buttonIndex];
}

void setButtonState(int buttonIndex, int newState) {
  buttonStates[buttonIndex] = newState;
}

void resetDebounceTimer(int buttonIndex) {
  lastDebounceTimes[buttonIndex] = millis();
}

bool debounceTimerExpired(int buttonIndex) {
  return timeInCurrentState(buttonIndex) > debounceDelay;
}

int timeInCurrentState(int buttonIndex) {
  return millis() - lastDebounceTimes[buttonIndex];
}

// For debugging only. Uses delay so break real time.
//void blinkNumberOfTimes(int numberOfTimes) {
//  for (int i = 0; i < numberOfTimes; i++) {
//    digitalWrite(ledPin, HIGH);
//    delay(200);
//    digitalWrite(ledPin, LOW);
//    delay(200);
//  }
//}

