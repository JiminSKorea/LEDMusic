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
  for (int i=0;i<5;i++){ digitalWrite(ledPins[i], HIGH); delay(200); digitalWrite(ledPins[i], LOW); }

}

// referenced LAB 4 code https://ublearns.buffalo.edu/d2l/lms/dropbox/user/folder_user_view_feedback.d2l?db=239431&grpid=0&isprv=0&bp=0&ou=307491