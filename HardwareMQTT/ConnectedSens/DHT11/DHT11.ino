// #include "DHTesp.h"

// #define DHTpin 14    // D5 of NodeMCU is GPIO14

// DHTesp dht;

// void setup() {
//   Serial.begin(115200);
//   Serial.println();
//   Serial.println("Initializing DHT Sensor...");

//   // use this instead of autodetect: 
//   dht.setup(DHTpin, DHTesp::DHT11); // for DHT11, connect DHT sensor to GPIO 14
//   //dht.setup(DHTpin, DHTesp::DHT22); // for DHT22, connect DHT sensor to GPIO 14
// }

// void loop() {
//   delay(dht.getMinimumSamplingPeriod());

//   float humidity = dht.getHumidity();
//   float temperature = dht.getTemperature();
//   float temperatureF = dht.toFahrenheit(temperature);
//   float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
//   float heatIndexF = dht.computeHeatIndex(temperatureF, humidity, true);

//   Serial.print("Status: ");
//   Serial.print(dht.getStatusString());
//   Serial.print(" | Humidity: ");
//   Serial.print(humidity, 1);
//   Serial.print("% | Temperature: ");
//   Serial.print(temperature, 1);
//   Serial.print("°C (");
//   Serial.print(temperatureF, 1);
//   Serial.print("°F) | Heat Index: ");
//   Serial.print(heatIndex, 1);
//   Serial.print("°C (");
//   Serial.print(heatIndexF, 1);
//   Serial.println("°F)");
// }


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>

const char* ssid = "mqtt";
const char* password = "mqttmosquitto";
const char* mqtt_server = "192.168.206.95";
const int mqtt_port = 1883;
const char* mqtt_topic_sub = "publish/signal/ir";
const char* mqtt_topic_pub = "publish/signal/air";
const char* mqtt_username = "bllraslen";
const char* mqtt_password = "bllraslen";
const char* mqtt_client_id = "esp8266Client";

#define DHTpin 14    // D5 of NodeMCU is GPIO14

DHTesp dht;

WiFiClient espClient;
PubSubClient client(espClient);

bool sensorEnabled = false;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if (strcmp(topic, mqtt_topic_sub) == 0) {
    if ((char)payload[0] == '1') {
      sensorEnabled = true;
      Serial.println("Sensor started");
    } else {
      sensorEnabled = false;
      Serial.println("Sensor stopped");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  Serial.println();
  Serial.println("Initializing DHT Sensor...");
  dht.setup(DHTpin, DHTesp::DHT11); // for DHT11, connect DHT sensor to GPIO 14
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (sensorEnabled) {
    // Your sensor-related code here
    // Example: digitalWrite(sensorPin, HIGH); // Turn sensor on
    Serial.println("Sensor is working");
    client.publish(mqtt_topic_pub, "1"); // Publish "1" if sensor is working
  } else {
    // Your code to disable the sensor
    // Example: digitalWrite(sensorPin, LOW); // Turn sensor off
        client.publish(mqtt_topic_pub, "0"); // Publish "1" if sensor is working

    Serial.println("Sensor is not working");
  }
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
