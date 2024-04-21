// #define SENSOR_PIN 4   // The ESP32 pin connected to the OUT pin of the sound sensor (GPIO 4)
// #define LED_PIN 2      // The ESP32 pin connected to the LED (GPIO 2)

// int prev_state = HIGH;  // The previous state from the input pin
// int sound_state;        // The current reading from the input pin
// unsigned long previousMillis = 0; // Stores the last time sound was checked
// const long interval = 2000; // Interval between sound checks (in milliseconds)

// void setup() {
//   // Initialize the Serial to communicate with the Serial Monitor.
//   Serial.begin(9600);
//   // Initialize the LED pin as an output
//   pinMode(LED_PIN, OUTPUT);
//   // Initialize the sound sensor pin as an input
//   pinMode(SENSOR_PIN, INPUT);
// }

// void loop() {
//   delay(2000);
//     // Read the state of the ESP32's input pin
//     sound_state = digitalRead(SENSOR_PIN);
   
//     if (sound_state == 1) {
//          Serial.println("sound_state : ");
//                   Serial.println(sound_state);
//       // If sound is detected, print a message
//       Serial.println("Sound detected!");
//       // Turn off the LED
//       digitalWrite(LED_PIN, HIGH);
//           Serial.println("-----------------------------------------");

//     } else {
//        Serial.println("sound_state : ");
//                   Serial.println(sound_state);
//       // If no sound is detected, print a message
//       Serial.println("No sound detected!");
//       // Turn on the LED
//       digitalWrite(LED_PIN, LOW);
//           Serial.println("-----------------------------------------");

//     }

// }



#include <WiFi.h>
#include <PubSubClient.h>

#define SENSOR_PIN 4   // The ESP32 pin connected to the OUT pin of the sound sensor (GPIO 4)
#define LED_PIN 2      // The ESP32 pin connected to the LED (GPIO 2)

const char* ssid = "mqtt";
const char* password = "mqttmosquitto";
const char* mqtt_server = "192.168.206.95";
const int mqtt_port = 1883;
const char* mqtt_topic = "publish/signal/ir";
const char* mqtt_username = "bllraslen";
const char* mqtt_password = "bllraslen";

WiFiClient espClient;
PubSubClient client(espClient);

int prev_state = HIGH;  // The previous state from the input pin
int sound_state;        // The current reading from the input pin
unsigned long previousMillis = 0; // Stores the last time sound was checked
const long interval = 2000; // Interval between sound checks (in milliseconds)

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
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
  // Handle incoming messages on subscribed topics.
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
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sound_state = digitalRead(SENSOR_PIN);

    if (sound_state == 1) {
      Serial.println("sound_state : ");
      Serial.println(sound_state);
      Serial.println("Sound detected!");
      digitalWrite(LED_PIN, HIGH);
      client.publish(mqtt_topic, "1");
      Serial.println("-----------------------------------------");

    } else {
      Serial.println("sound_state : ");
      Serial.println(sound_state);
      Serial.println("No sound detected!");
      digitalWrite(LED_PIN, LOW);
      client.publish(mqtt_topic, "0");
      Serial.println("-----------------------------------------");

    }
  }
}
