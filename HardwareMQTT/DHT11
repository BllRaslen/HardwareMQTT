#include "DHTesp.h"

#define DHTpin 14    // D5 of NodeMCU is GPIO14

DHTesp dht;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Initializing DHT Sensor...");

  // use this instead of autodetect: 
  dht.setup(DHTpin, DHTesp::DHT11); // for DHT11, connect DHT sensor to GPIO 14
  //dht.setup(DHTpin, DHTesp::DHT22); // for DHT22, connect DHT sensor to GPIO 14
}

void loop() {
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  float temperatureF = dht.toFahrenheit(temperature);
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
  float heatIndexF = dht.computeHeatIndex(temperatureF, humidity, true);

  Serial.print("Status: ");
  Serial.print(dht.getStatusString());
  Serial.print(" | Humidity: ");
  Serial.print(humidity, 1);
  Serial.print("% | Temperature: ");
  Serial.print(temperature, 1);
  Serial.print("°C (");
  Serial.print(temperatureF, 1);
  Serial.print("°F) | Heat Index: ");
  Serial.print(heatIndex, 1);
  Serial.print("°C (");
  Serial.print(heatIndexF, 1);
  Serial.println("°F)");
}
