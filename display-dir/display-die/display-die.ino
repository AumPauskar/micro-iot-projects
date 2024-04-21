// C++ code
//
#include <LiquidCrystal_I2C.h>

// defining constants
const int buttonPin = 12;
const int ledPin = 13;

// global variables
int buttonState = 0;
int die;

// defining lcd object
LiquidCrystal_I2C lcd_1(32, 16, 2);

void setup()
{
  // lcd setup
  lcd_1.init();
  lcd_1.setCursor(0, 0);
  lcd_1.backlight();
  lcd_1.display();
  
  // button setup
  pinMode(buttonPin, INPUT);
  
  // random seed 
  randomSeed(analogRead(0));
  
  // button setup
  pinMode(ledPin, OUTPUT);
}

void refreshDisplay(int arg) {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print(arg);
}

int rollDice() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == HIGH) {
    // Generate a random number between 1 and 6 (inclusive)
    int randomNumber = random(1, 7);
    refreshDisplay(randomNumber);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    return randomNumber;
  } else {
    // If button is not pressed, return -1 as an indication
    digitalWrite(ledPin, LOW);
    return -1;
  }
}

void loop()
{
  // only for debugging
  die = rollDice();
  Serial.println(die);
}