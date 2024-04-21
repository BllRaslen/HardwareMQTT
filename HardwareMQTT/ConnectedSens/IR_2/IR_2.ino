
// int ledPin = 13; // D7 choose pin for the LED
// int buzzerPin = 14; // Example: D5 as buzzer pin
// int speakerPin = 15; // Example: D8 as piezo speaker pin
// int inputPin = 12; // D6 choose input pin (for Infrared sensor) 
// int val = 0; // variable for reading the pin status

// void setup() {  
//   Serial.begin(9600);
//   pinMode(ledPin, OUTPUT); // declare LED as output
//   pinMode(buzzerPin, OUTPUT); // declare buzzer as output
//   pinMode(speakerPin, OUTPUT); // declare speaker as output
//   pinMode(inputPin, INPUT); // declare Infrared sensor as input
// }

// void loop() {
//   val = digitalRead(inputPin); // read input value 
//   if (val == HIGH) { // check if the input is HIGH
//     digitalWrite(ledPin, LOW); // turn LED OFF
//     digitalWrite(buzzerPin, LOW); // turn Buzzer OFF (if active low)
//     digitalWrite(speakerPin, LOW); // turn Speaker OFF (if generating tone)
//     Serial.println("IR Sensor Value without Object in front of the Sensor");
//   } else { 
//     digitalWrite(ledPin, HIGH); // turn LED ON 
//     digitalWrite(buzzerPin, HIGH); // turn Buzzer ON (if active low, use tone() for speaker)
//     // To generate a tone on the speakerPin:
//     tone(speakerPin, 1000); // Generate a 1kHz tone (change frequency as needed)
//     Serial.println("IR Sensor Value with an Object in front of the Sensor");
//     delay(100);
//     noTone(speakerPin); // Stop the tone
//   } 
// }

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "mqtt";
const char* password = "mqttmosquitto";
const char* mqtt_server = "192.168.206.95";
const int mqtt_port = 1883;
const char* mqtt_topic_pub = "publish/signal/temp";
const char* mqtt_topic_sub = "publish/signal/ir";
const char* mqtt_username = "bllraslen";
const char* mqtt_password = "bllraslen";

WiFiClient espClient;
PubSubClient client(espClient);

int ledPin = D7; // choose pin for the LED
int buzzerPin = D5; // choose pin for the buzzer
int speakerPin = D8; // choose pin for the piezo speaker
int inputPin = D6; // choose input pin (for Infrared sensor)
int val = 0; // variable for reading the pin status
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
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
  if (strcmp(topic, mqtt_topic_sub) == 0) {
    if ((char)payload[0] == '1') {
      sensorEnabled = true;
    } else {
      sensorEnabled = false;
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
  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(buzzerPin, OUTPUT); // declare buzzer as output
  pinMode(speakerPin, OUTPUT); // declare speaker as output
  pinMode(inputPin, INPUT); // declare Infrared sensor as input
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
    val = digitalRead(inputPin); // read input value 
    if (val == HIGH) { // check if the input is HIGH
      digitalWrite(ledPin, LOW); // turn LED OFF
      digitalWrite(buzzerPin, LOW); // turn Buzzer OFF
      digitalWrite(speakerPin, LOW); // turn Speaker OFF
      Serial.println("IR Sensor Value without Object in front of the Sensor");
      client.publish(mqtt_topic_pub, "0");
    } else { 
      digitalWrite(ledPin, HIGH); // turn LED ON 
      digitalWrite(buzzerPin, HIGH); // turn Buzzer ON
      // To generate a tone on the speakerPin:
      tone(speakerPin, 1000); // Generate a 1kHz tone (change frequency as needed)
      Serial.println("IR Sensor Value with an Object in front of the Sensor");
      client.publish(mqtt_topic_pub, "1");
      delay(100);
      noTone(speakerPin); // Stop the tone
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    digitalWrite(buzzerPin, LOW); // turn Buzzer OFF
    digitalWrite(speakerPin, LOW); // turn Speaker OFF
    Serial.println("Sensor is disabled");
  }

  delay(1000); // Adjust delay as needed
}
