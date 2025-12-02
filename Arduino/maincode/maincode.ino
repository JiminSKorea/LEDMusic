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
  
  if (digitalRead(powerPin) == LOW && (millis() - lastPowerPressed) > 200){
    powerOn = !powerOn;
    lastPowerPressed = millis();
    if (powerOn == false){
      for (int i = 0; i < 5; i++){
        digitalWrite(ledPins[i], LOW);
      }
      Serial.println("Power is OFF");
    } else {
      Serial.println("Power is ON.");
    }
  }

  if (powerOn == false) {
    return;
  }

  if (digitalRead(modeSwitchPin) == LOW && (millis() - lastModePressed) > 200){
    mode = (mode + 1) % 2; // 0 is Rhythmic, 1 is Flow
    Serial.println("Mode Switch");
    lastModePressed = millis();
    for (int i = 0; i < 5; i++){
        digitalWrite(ledPins[i], LOW);
    }
  }

  soundValue = analogRead(soundSensorPin);

  if (mode == 0){


    if (soundValue > lastSound + 50 && (millis() - lastBeat) > 400){
      lastBeat = millis();

      for (int i = 0; i < 5; i++){
      digitalWrite(ledPins[i], HIGH);
      }

      delay(50);

      for (int i = 0; i < 5; i++){
        digitalWrite(ledPins[i], LOW);
      }  
    }
    

    

  }

  if (mode == 1){


    if (soundValue > 100 &&(millis() - lastFlow) > 120){
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

  lastSound = soundValue;
}

// references
//https://sensorkit.arduino.cc/sensorkit/module/lessons/lesson/06-the-sound-sensor 
//https://projecthub.arduino.cc/krishna_agarwal/how-to-make-diy-music-reactive-led-using-arduino-illuminate-your-sound-4839be 
//https://seeeddoc.github.io/Grove-Sound_Sensor/ 
//https://ublearns.buffalo.edu/d2l/lms/dropbox/user/folder_user_view_feedback.d2l?db=239431&grpid=0&isprv=0&bp=0&ou=307491  
