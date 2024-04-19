// constants won't change. They're used here to set pin numbers:
const int buttonPin = 12;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin

// Morse code dictionary
const char* morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
                            ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
                            "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", " "};

// Alphabet
const char* alphabet = "abcdefghijklmnopqrstuvwxyz ";

// variables will change:
int buttonState = 0;       // variable for reading the pushbutton status
int lastButtonState = LOW; // previous state of the button
unsigned long pressStartTime = 0; // the time the button was pressed
unsigned long pressEndTime = 0;   // the time the button was released
int pressDuration = 0;            // duration of button press in milliseconds

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the button state has changed
  if (buttonState != lastButtonState) {
    // button is pressed down
    if (buttonState == HIGH) {
      pressStartTime = millis(); // record the time the button is pressed
    } else { // button is released
      pressEndTime = millis(); // record the time the button is released
      pressDuration = pressEndTime - pressStartTime; // calculate the duration of the press
      
      // translate the duration into Morse code
      if (pressDuration < 200) { // if the press duration is short (a dot)
        Serial.print(".");
      } else if (pressDuration >= 200 && pressDuration < 600) { // if the press duration is medium (a dash)
        Serial.print("-");
      } else { // if the press duration is long (end of a character)
        decodeMorse(); // decode the Morse code
      }
    }
  }
  
  // save the current state as the last state
  lastButtonState = buttonState;
}

void decodeMorse() {
  int dotDuration = 200; // duration of a dot in milliseconds
  int dashDuration = 600; // duration of a dash in milliseconds
  int morseIndex = 0; // index for Morse code array
  
  // iterate through the Morse code array
  for (int i = 0; i < 27; i++) {
    // compare the current Morse code with the recorded button press duration
    if (morseCode[i][morseIndex] == '.') { // if it's a dot
      if (pressDuration < dotDuration + 50) { // check if the press duration is close to the duration of a dot
        Serial.print(alphabet[i]); // print the corresponding letter
        break; // exit the loop
      }
    } else if (morseCode[i][morseIndex] == '-') { // if it's a dash
      if (pressDuration >= dashDuration - 50 && pressDuration < dashDuration + 50) { // check if the press duration is close to the duration of a dash
        Serial.print(alphabet[i]); // print the corresponding letter
        break; // exit the loop
      }
    } else { // if it's the end of a character
      Serial.print(" "); // print a space
      break; // exit the loop
    }
  }
}
