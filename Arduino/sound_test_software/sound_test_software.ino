
const int soundSensorPin = A2; // Analog pin 2 connected to the sound sensor
const int ledPins[] = {2, 3, 4, 5, 6}; // Digital pins connected to the LEDs
const int powerPin = 13; // Power On/Off button connected to pin number 13
const int modeSwitchPin = 12; //  Power On/Off button connected to pin number 12

void setup() {
  pinMode(soundSensorPin, INPUT);
  pinMode(powerPin, INPUT_PULLUP);
  pinMode(modeSwitchPin, INPUT_PULLUP);
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT); 
  }
  Serial.begin(9600);
}

void loop()
{
  int soundValue = 0; //create variable to store many different readings
  for (int i = 0; i < 32; i++) //create a for loop to read
  { soundValue += analogRead(soundSensorPin);  } //read the sound sensor
 
  soundValue >>= 5; //bitshift operation
  

  if (soundValue > 300) { 
    Serial.println(soundValue); //print the value of sound sensor
    Serial.println("THE SOUND IS LOUD!");
  }
  delay(50); //a shorter delay between readings
}


