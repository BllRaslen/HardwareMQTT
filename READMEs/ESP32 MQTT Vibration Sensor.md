# ESP32 MQTT Vibration Sensor

This project demonstrates how to connect an ESP32 microcontroller to a MQTT broker and publish vibration sensor readings to a specified topic.

## Requirements

- Hardware:
  - ESP32 microcontroller
  - Vibration sensor (KY-002)
- Software:
  - Arduino IDE
  - WiFi library for ESP32
  - PubSubClient library for MQTT communication

## Circuit Diagram

Connect the signal pin of the KY-002 vibration sensor to pin D2 of the ESP32.

## Installation

1. Install the Arduino IDE if you haven't already.
2. Install the ESP32 board support package in the Arduino IDE.
3. Install the required libraries:
   - WiFi.h
   - PubSubClient.h

## Configuration

Before uploading the code to your ESP32, make sure to modify the following variables in the code according to your setup:

- `ssid`: Your WiFi network name.
- `password`: Your WiFi password.
- `mqtt_server`: IP address of your MQTT broker.
- `mqtt_port`: Port number of the MQTT broker.
- `mqtt_username`: Username for MQTT authentication (if required).
- `mqtt_password`: Password for MQTT authentication (if required).
- `topic`: MQTT topic to which sensor readings will be published.
- `sensorPin`: Pin number to which the signal pin of the vibration sensor is connected.

## Usage

1. Upload the code to your ESP32 using the Arduino IDE.
2. Open the serial monitor to view the ESP32's output.
3. The ESP32 will attempt to connect to the specified WiFi network and MQTT broker upon startup.
4. Once connected, the ESP32 will continuously read the vibration sensor and publish the readings to the specified MQTT topic.

## Troubleshooting

- If you encounter any connection issues, double-check your WiFi credentials and MQTT broker settings.
- Ensure that the hardware connections are correct according to the provided circuit diagram.

## License

This project is licensed under the MIT License.
