const int sensorPin = D2; // Update with the actual pin used for the sensor

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int sensorValue = digitalRead(sensorPin);
  
  // Invert the logic if the sensor gives LOW on vibration
  // Remove '!' if your sensor gives HIGH on vibration
  if (sensorValue) {
    Serial.println("Vibration Detected");
  } else {
    Serial.println("Normal");
  }
  
  // Debounce delay to prevent reading too much noise
 delay(100);
}