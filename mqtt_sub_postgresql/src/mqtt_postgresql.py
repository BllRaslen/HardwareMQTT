import paho.mqtt.client as mqtt
import psycopg2
from psycopg2 import Error
import time

current_time = time.strftime('%Y-%m-%d %H:%M:%S')

# MQTT configuration
MQTT_BROKER_HOST = "192.168.206.95"
MQTT_BROKER_PORT = 1883
MQTT_USERNAME = "bllraslen"
MQTT_PASSWORD = "bllraslen"
MQTT_TOPICS = '#'

# PostgreSQL configuration
DB_HOST = "localhost"
DB_PORT = 5432
DB_NAME = "doc"
DB_USER = "postgres"
DB_PASSWORD = "bll.raslen"

# MQTT on_connect callback
def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker with result code "+str(rc))
    # Subscribe to all topics
    client.subscribe(MQTT_TOPICS)

# MQTT on_message callback
def on_message(client, userdata, msg):
    print("Received message on topic: "+msg.topic)
    print("Message: "+str(msg.payload))
    # Store the received data into PostgreSQL database
    try:
        connection = psycopg2.connect(
            host=DB_HOST,
            port=DB_PORT,
            database=DB_NAME,
            user=DB_USER,
            password=DB_PASSWORD
        )
        cursor = connection.cursor()
        cursor.execute("INSERT INTO mqtt_data (topic, payload, detection_time) VALUES (%s, %s, %s)",
                       (msg.topic, msg.payload.decode('utf-8'), current_time))

        connection.commit()
        print("Data stored successfully in PostgreSQL database")
    except Error as e:
        print("Error while connecting to PostgreSQL", e)
    finally:
        if connection:
            cursor.close()
            connection.close()

# Set up MQTT client
client = mqtt.Client(client_id="Heloo", protocol=mqtt.MQTTv311)
client.username_pw_set(username=MQTT_USERNAME, password=MQTT_PASSWORD)
client.on_connect = on_connect
client.on_message = on_message

# Connect to MQTT broker
client.connect(MQTT_BROKER_HOST, MQTT_BROKER_PORT, 60)

# Start the MQTT loop
client.loop_forever()
