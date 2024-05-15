const int triggerPin = 6;  // Trigger pin of the ultrasonic sensor
const int echoPin = 7;     // Echo pin of the ultrasonic sensor
const int buzzerPin = 9;   // Buzzer pin

long duration;
int distance;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);  // Initialize serial communication at 9600 bps
}

void loop() {
  // Clear the trigger pin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Set the trigger pin HIGH for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read the echo pin, and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)

  Serial.print("Distance: ");
  Serial.println(distance);

  // Set buzzer beeping rate based on distance
  if (distance < 10) {
    tone(buzzerPin, 1000);  // Continuous beep
    delay(100);  // Small delay to avoid overload
    noTone(buzzerPin);
    Serial.println("TRIPLE CAUTION, high frequency!!!");
  } else if (distance < 20) {
    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
    delay(200);
    Serial.println("DOUBLE CAUTION, mid frequency!!!");
  } else if (distance < 30) {
    tone(buzzerPin, 1000);
    delay(400);
    noTone(buzzerPin);
    delay(400);
    Serial.println("CAUTION, low frequency!!!");
  } else if (distance < 50) {
    tone(buzzerPin, 1000);
    delay(800);
    noTone(buzzerPin);
    delay(800);
    Serial.println("Appropriate distace, v low frequency!!!");
  } else {
    noTone(buzzerPin);  // No beep
  }

  delay(1000);  // Delay between readings
}