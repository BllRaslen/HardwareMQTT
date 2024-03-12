#define SENSOR_PIN D7 // The ESP8266 pin D7 connected to the OUT pin of the sound sensor

int prev_state = HIGH; // The previous state from the input pin
int sound_state;     // The current reading from the input pin

void setup() {
  // Initialize the Serial to communicate with the Serial Monitor.
  Serial.begin(9600);
  // initialize the ESP8266's pin as an input
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // read the state of the the ESP8266's input pin
  sound_state = digitalRead(SENSOR_PIN);

  if (prev_state == HIGH && sound_state == LOW)
    Serial.println("The sound has been detected");
  else if (prev_state == LOW && sound_state == HIGH)
    Serial.println("The sound has disappeared");

  // save the the last state
  prev_state = sound_state;
}
