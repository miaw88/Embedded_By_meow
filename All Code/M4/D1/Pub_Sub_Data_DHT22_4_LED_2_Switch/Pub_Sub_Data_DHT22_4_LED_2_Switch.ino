#include <WiFi.h>
#include <PubSubClient.h>
#include "SHTC3.h"
#define TestLED1 19
#define TestLED2 21
#define TestLED3 22
#define TestLED4 23
#define pushButton1 5
#define pushButton2 18
SHTC3 s(Wire);
const char* ssid = "meow";
const char* password = "meowmeow";
const char* mqtt_server = "test.mosquitto.org";
const char* topic1 = "M401";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
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
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
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
  if ((String)myPayLoad == "ON1") digitalWrite(TestLED1, HIGH);
  if ((String)myPayLoad == "OFF1") digitalWrite(TestLED1, LOW);
  if ((String)myPayLoad == "ON2") digitalWrite(TestLED2, HIGH);
  if ((String)myPayLoad == "OFF2") digitalWrite(TestLED2, LOW);
  if ((String)myPayLoad == "ON3") digitalWrite(TestLED3, HIGH);
  if ((String)myPayLoad == "OFF3") digitalWrite(TestLED3, LOW);
  if ((String)myPayLoad == "ON4") digitalWrite(TestLED4, HIGH);
  if ((String)myPayLoad == "OFF4") digitalWrite(TestLED4, LOW);
}

void reconnect()
{ while (!client.connected()) // Loop until we're reconnected
  { Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32 Client-";
    clientId += String(random(0xffff), HEX); // Create a random client ID
    if (client.connect(clientId.c_str())) // Attempt to connect
    { Serial.println("connected"); // Once connected, publish an announcement...
      client.publish(topic1, "Hello World Pk007"); // ... and resubscribe
      client.subscribe(topic1);
    } else
    { Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{ Serial.begin(115200);
  Wire.begin(15, 4); // SHTC3_Pin D15,D4
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
  pinMode(TestLED1, OUTPUT);
  pinMode(TestLED2, OUTPUT);
  pinMode(TestLED3, OUTPUT);
  pinMode(TestLED4, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{ s.begin(true);
  float t = s.readTempC();
  if (!client.connected()) reconnect();
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000)
  { lastMsg = now;
    snprintf (msg, 75, "Temp = %.2f", t);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic1, msg);
  }
  if (digitalRead(pushButton1) == 0)
  { client.loop();
    sprintf (msg, "Overheat Alarm");
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic1, msg);
    while (digitalRead(pushButton1) == 0);
    delay(100);
  }
  if (digitalRead(pushButton2) == 0)
  { client.loop();
    sprintf (msg, "Intruders Alarm");
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic1, msg);
    while (digitalRead(pushButton2) == 0);
    delay(100);
  }
}
