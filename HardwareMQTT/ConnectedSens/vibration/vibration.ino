// const int sensorPin = D2; // Update with the actual pin used for the sensor

// void setup() {
//   Serial.begin(9600);
//   pinMode(sensorPin, INPUT);
// }

// void loop() {
//   int sensorValue = digitalRead(sensorPin);
  
//   // Invert the logic if the sensor gives LOW on vibration
//   // Remove '!' if your sensor gives HIGH on vibration
//   if (sensorValue) {
//     Serial.println("Vibration Detected");
//   } else {
//     Serial.println("Normal");
//   }
  
//   // Debounce delay to prevent reading too much noise
//  delay(100);
// }


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "mqtt";
const char* password = "mqttmosquitto";
const char* mqtt_server = "192.168.206.95";
const int mqtt_port = 1883;
const char* mqtt_topic_pub = "publish/signal/ir";
const char* mqtt_username = "bllraslen";
const char* mqtt_password = "bllraslen";
const char* mqtt_client_id = "esp8266Client";

const int sensorPin = D2; // Update with the actual pin used for the sensor

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.begin(9600);
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

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int sensorValue = digitalRead(sensorPin);

  // Invert the logic if the sensor gives LOW on vibration
  // Remove '!' if your sensor gives HIGH on vibration
  if (sensorValue) {
    Serial.println("Vibration Detected");
    client.publish(mqtt_topic_pub, "0"); // Publish to topic if vibration detected
  } else {
    Serial.println("Normal");
    client.publish(mqtt_topic_pub, "1"); // Publish to topic if no vibration detected
  }

  // Debounce delay to prevent reading too much noise
  delay(100);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
