#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "karthikIPS";
const char* password = "123456789";

// MQTT broker
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

int sensorValue = 25;   // Dummy sensor value

// Function to connect WiFi
void setup_wifi()
{
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Function to connect MQTT
void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266_Client"))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop()
{M
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  // Publish sensor value every 3 seconds
  String msg = "Temperature: " + String(sensorValue);

  Serial.print("Publishing: ");
  Serial.println(msg);

  client.publish("iot/classroom/temp", msg.c_str());

  sensorValue++;   // Simulate changing sensor
  delay(3000);
}