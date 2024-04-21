
// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   int analogValue = analogRead(A0); // Read the analog input
//   float millivolts = (analogValue / 1023.0) * 3300; // Convert to millivolts
//   float celsius = millivolts / 10; // Convert millivolts to Celsius
//   float fahrenheit = (celsius * 9.0 / 5.0) + 32; // Convert Celsius to Fahrenheit

//   Serial.print("Temperature: ");
//   Serial.print(celsius);
//   Serial.print(" C, ");
//   Serial.print(fahrenheit);
//   Serial.println(" F");

//   delay(1000); // Wait a second between readings
// }


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "mqtt";
const char* password = "mqttmosquitto";
const char* mqtt_server = "192.168.206.95";
const int mqtt_port = 1883;
const char* mqtt_topic_sub = "publish/signal/ir";
const char* mqtt_topic_pub = "publish/signal/air";
const char* mqtt_username = "bllraslen";
const char* mqtt_password = "bllraslen";

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
      Serial.println("Sensor enabled");
    } else {
      sensorEnabled = false;
      Serial.println("Sensor disabled");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("esp8266Client", mqtt_username, mqtt_password)) {
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
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
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

  delay(1000); // Adjust delay as needed
}
