#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"
#define Pin_DHT22 15
const char* ssid = "meow"; //Your Wifi
const char* password = "meowmeow"; //Your Wifi password
const char* mqtt_server = "test.mosquitto.org";
const char* topic1 = "Flow1";
DHTesp dht;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int Counter = 0;
int SW1 = 4;
int SW2 = 5;
int LED1 = 19;
int LED2 = 21;
int LED3 = 22;
int LED4 = 23;
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to "); Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  randomSeed(micros());
  Serial.println(""); Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}
void reconnect()
{ while (!client.connected()) // Loop until we're reconnected
  { Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32 Client-";
    clientId += String(random(0xffff), HEX); // Create a random client ID
    if (client.connect(clientId.c_str())) // Attempt to connect
    { Serial.println("connected"); // Once connected, publish an announcement...
      client.publish(topic1, "Hello World Akki"); // ... and resubscribe
      client.subscribe(topic1);
    }
    else
    { Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length)
{ char myPayLoad[50];
  Serial.print("Message arrived [");
  Serial.print(topic1);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  { Serial.print((char)payload[i]);
    myPayLoad[i] = payload[i];
    myPayLoad[i + 1] = '\0'; // End of String
  }
  Serial.print("\n ---> "); Serial.println(myPayLoad);
  myPayLoad[4] = '\0'; // String lessthan 4 Charector
  if ((String)myPayLoad == "ON")
  { digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }
  if ((String)myPayLoad == "ON1") {
    digitalWrite(LED1, HIGH);
  }
  if ((String)myPayLoad == "ON2") {
    digitalWrite(LED2, HIGH);
  }
  if ((String)myPayLoad == "ON3") {
    digitalWrite(LED3, HIGH);
  }
  if ((String)myPayLoad == "ON4") {
    digitalWrite(LED4, HIGH);
  }
  if ((String)myPayLoad == "OFF")
  { digitalWrite(LED1, LOW); digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW); digitalWrite(LED4, LOW);
  }
  if ((String)myPayLoad == "OFF1") {
    digitalWrite(LED1, LOW);
  }
  if ((String)myPayLoad == "OFF2") {
    digitalWrite(LED2, LOW);
  }
  if ((String)myPayLoad == "OFF3") {
    digitalWrite(LED3, LOW);
  }
  if ((String)myPayLoad == "OFF4") {
    digitalWrite(LED4, LOW);
  }
}
void setup()
{ Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  dht.setup(Pin_DHT22, DHTesp::DHT22);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void loop()
{ if (!client.connected()) reconnect();
  { client.loop();
    if (digitalRead(SW1) == 0)
    { client.loop();
      snprintf (msg, 75, "Alert!!! The temperature is too high.");
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish(topic1, msg);
      while (digitalRead(SW1) == 0);
      delay(100);
    }
    if (digitalRead(SW2) == 0)
    { client.loop();
      snprintf (msg, 75, "Alert !!! There are suspicious people in the area.");
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish(topic1, msg);
      while (digitalRead(SW2) == 0);
      delay(100);
    }
  }
  long now = millis();
  if (now - lastMsg > 5000)
  { lastMsg = now;
    float humid = dht.getHumidity();
    float tempp = dht.getTemperature();
    snprintf (msg, 75, "Tempp: %.2f'C Humid: %.2f%%", tempp, humid);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic1, msg);
  }
}
