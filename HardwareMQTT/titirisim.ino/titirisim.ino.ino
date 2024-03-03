#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "mqtt";
const char* password = "mqttmosquitto";
const char* mqtt_server = "192.168.157.95";
const int mqtt_port = 1883;
const char* mqtt_username = "bllraslen";
const char* mqtt_password = "bllraslen";
const char* topic = "smarthome/vibration";

const int sensorPin = 2; // Connect the signal pin of KY-002 sensor to pin D2 of ESP32

WiFiClient espClient;
PubSubClient client(espClient);

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
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP address: ");
  Serial.println(WiFi.gatewayIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int sensorValue = digitalRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);
  if(sensorValue==0){
  client.publish(topic, "Normal");
  }
  else{
    client.publish(topic,"Deprem!!!");
  }


  // Publish sensor value to MQTT topic

  // Wait before publishing next reading
  delay(1000);
}
