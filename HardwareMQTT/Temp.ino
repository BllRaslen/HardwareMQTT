// #include "DHT.h"

// #define DPIN 4        //Pin to connect DHT sensor (GPIO number) D2
// #define DTYPE DHT11   // Define DHT 11 or DHT22 sensor type

// DHT dht(DPIN,DTYPE);

// void setup() {
//   Serial.begin(9600);
//   dht.begin();
// }

// void loop() {
//   delay(2000);
  
//   float tc = dht.readTemperature(false);  //Read temperature in C
//   float tf = dht.readTemperature(true);   //Read Temperature in F
//   float hu = dht.readHumidity();          //Read Humidity

//   Serial.print("Temp: ");
//   Serial.print(tc);
//   Serial.print(" C, ");
//   Serial.print(tf);
//   Serial.print(" F, Hum: ");
//   Serial.print(hu);
//   Serial.println("%");
// }

// ----------------------------------
// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   int analogValue = analogRead(A0); // Read the analog input
//   float millivolts = (analogValue / 1023.0) * 3300; // Convert to millivolts
//   float celsius = millivolts / 10; // Convert millivolts to Celsius
//   Serial.print("Temperature: ");
//   Serial.print(celsius);
//   Serial.println(" C");
//   delay(1000); // Wait a second between readings
// }


void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(A0); // Read the analog input
  float millivolts = (analogValue / 1023.0) * 3300; // Convert to millivolts
  float celsius = millivolts / 10; // Convert millivolts to Celsius
  float fahrenheit = (celsius * 9.0 / 5.0) + 32; // Convert Celsius to Fahrenheit

  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  delay(1000); // Wait a second between readings
}
