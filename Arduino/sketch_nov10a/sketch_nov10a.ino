const int soundSensorPin = A2; // Analog pin connected to the sound sensor
const int ledPins[] = {2, 3, 4, 5, 6}; // Digital pins connected to the LEDs
const int powerPin = 13; 
const int modeSwitchPin = 12;

bool powerOn = false;

int mode = 0;

unsigned long lastPowerPressed = 0;

unsigned long lastModePressed = 0;


int lastSound = 0;
unsigned long lastBeat = 0;


int ledIndex = 0;
bool direction = true;
unsigned long lastFlow = 0;

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
  int soundValue = analogRead(soundSensorPin); // Read the analog input value
  
  if (digitalRead(powerPin) == LOW && (millis() - lastPowerPressed) > 50){
    powerOn = !powerOn;
    lastPowerPressed = millis();
    if (powerOn == false){
      for (int i = 0; i < 5; i++){
        digitalWrite(ledPins[i], LOW);
      }
    } else {
      Serial.println("Power is ON.");
    }
  }

  if (powerOn == false) {
    Serial.println("Power OFF");
    return;
  }

  if (digitalRead(modeSwitchPin) == LOW && (millis() - lastModePressed) > 50){
    mode = (mode + 1) % 2; // 0 is Rhythmic, 1 is Flow
    lastModePressed = millis();
    for (int i = 0; i < 5; i++){
        digitalWrite(ledPins[i], LOW);
    }
  }

  soundValue = analogRead(soundSensorPin);

  if (mode == 0){

    if (soundValue > lastSound + 100 && (millis() - lastBeat) > 120){
      lastBeat = millis();

      for (int i = 0; i < 5; i++){
      digitalWrite(ledPins[i], HIGH);
      }
    
      delay(50);

      for (int i = 0; i < 5; i++){
        digitalWrite(ledPins[i], LOW);
      }  
    }
    

    lastSound = soundValue;

  }

  if (mode == 1){

    if ((millis() - lastFlow) > 120){
      lastFlow = millis();

      for (int i = 0; i < 5; i++){
        digitalWrite(ledPins[i], LOW);
      } 
    
      digitalWrite(ledPins[ledIndex], HIGH);

      if (direction == true){
        ledIndex++;
         if (ledIndex >= 4) {
          ledIndex = 4;
          direction = false;
      }
      } else {
        ledIndex--;
        if (ledIndex == 0) {
          ledIndex = 0;
          direction = true;
        }
      }

     

      

    }

  }

  


  
  
}
