// Define the size of the dictionary
const int DICTIONARY_SIZE = 26;

// Structure to represent a key-value pair
struct MorsePair {
  char key;          // English alphabet character
  const char* value; // Morse code counterpart
};

// Array of key-value pairs representing the Morse code dictionary
const MorsePair morseDictionary[DICTIONARY_SIZE] = {
  {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."},
  {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
  {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},
  {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
  {'Y', "-.--"}, {'Z', "--.."}
};

// Define the pin for the LED
const int LED_PIN = 13;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Set LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Prompt the user to enter a string
  Serial.println("Enter a string (A-Z):");

  // Read the user input
  while (!Serial.available()); // Wait for input
  String input = Serial.readStringUntil('\n'); // Read input until newline character

  // Translate input to Morse code and blink LED accordingly
  translateAndBlink(input);
}

// Function to translate a string to Morse code and blink LED
void translateAndBlink(String input) {
  // Iterate through each character in the input string
  for (int i = 0; i < input.length(); i++) {
    // Convert character to uppercase
    char c = toupper(input.charAt(i));

    // Find Morse code counterpart in the dictionary
    const char* morseCode = findMorseCode(c);

    // Blink LED according to Morse code
    blinkMorseCode(morseCode);
  }
}

// Function to find Morse code for a given character
const char* findMorseCode(char c) {
  for (int i = 0; i < DICTIONARY_SIZE; i++) {
    if (morseDictionary[i].key == c) {
      return morseDictionary[i].value;
    }
  }
  return ""; // Return empty string if character not found
}

// Function to blink LED according to Morse code
void blinkMorseCode(const char* morseCode) {
  for (int i = 0; morseCode[i] != '\0'; i++) {
    if (morseCode[i] == '.') {
      digitalWrite(LED_PIN, HIGH);
      delay(250); // Dot duration
      digitalWrite(LED_PIN, LOW);
      delay(250); // Inter-element gap
    } else if (morseCode[i] == '-') {
      digitalWrite(LED_PIN, HIGH);
      delay(750); // Dash duration
      digitalWrite(LED_PIN, LOW);
      delay(250); // Inter-element gap
    } else if (morseCode[i] == ' ') {
      delay(750); // Inter-character gap
    }
  }
  delay(1250); // Inter-word gap
}
