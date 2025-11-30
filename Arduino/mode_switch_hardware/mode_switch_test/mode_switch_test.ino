const int soundSensorPin = A2; // Analog pin connected to the sound sensor
const int ledPins[] = {2, 3, 4, 5, 6}; // Digital pins connected to the LEDs
const int powerPin = 13; 
const int modeSwitchPin = 12;

void setup() {
  pinMode(soundSensorPin, INPUT);
  pinMode(powerPin, INPUT_PULLUP);
  pinMode(modeSwitchPin, INPUT_PULLUP);
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT); // Set the LED pins as outputs
  }
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  int modeSwitch = digitalRead(modeSwitchPin);
  if (modeSwitch == LOW){ 
    Serial.println("modeSwitch button is pressed.");
    digitalWrite(ledPins[3], HIGH);
  } else {
    digitalWrite(ledPins[3], LOW);
  }

  delay(200);
}