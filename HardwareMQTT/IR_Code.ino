// int ledPin = 13; // D7 choose pin for the LED
// int inputPin =12; // D6 choose input pin (for Infrared sensor) 
// int val = 0; // variable for reading the pin status

// void setup() 
// {  Serial.begin(9600);
//    pinMode(ledPin, OUTPUT); // declare LED as output 
//    pinMode(inputPin, INPUT); // declare Infrared sensor as input
// }


// void loop() {
//   // put your main code here, to run repeatedly:
//    val = digitalRead(inputPin); // read input value 
//    if (val == HIGH)
//    { // check if the input is HIGH
//       digitalWrite(ledPin, LOW); // turn LED OFF 
//       Serial.print(val);
//       Serial.println("IR Sensor Value with out Object in front of the Sensor");
 
//    } 
//    else 
//    { 
//       digitalWrite(ledPin, HIGH); // turn LED ON 
//       Serial.print(val);
//       Serial.println("IR Sensor Value with an Object in front of the Sensor");
//       delay(100);
//    } 
// }

// ----------------
int ledPin = 13; // D7 choose pin for the LED
int buzzerPin = 14; // Example: D5 as buzzer pin
int speakerPin = 15; // Example: D8 as piezo speaker pin
int inputPin = 12; // D6 choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status

void setup() {  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(buzzerPin, OUTPUT); // declare buzzer as output
  pinMode(speakerPin, OUTPUT); // declare speaker as output
  pinMode(inputPin, INPUT); // declare Infrared sensor as input
}

void loop() {
  val = digitalRead(inputPin); // read input value 
  if (val == HIGH) { // check if the input is HIGH
    digitalWrite(ledPin, LOW); // turn LED OFF
    digitalWrite(buzzerPin, LOW); // turn Buzzer OFF (if active low)
    digitalWrite(speakerPin, LOW); // turn Speaker OFF (if generating tone)
    Serial.println("IR Sensor Value without Object in front of the Sensor");
  } else { 
    digitalWrite(ledPin, HIGH); // turn LED ON 
    digitalWrite(buzzerPin, HIGH); // turn Buzzer ON (if active low, use tone() for speaker)
    // To generate a tone on the speakerPin:
    tone(speakerPin, 1000); // Generate a 1kHz tone (change frequency as needed)
    Serial.println("IR Sensor Value with an Object in front of the Sensor");
    delay(100);
    noTone(speakerPin); // Stop the tone
  } 
}
