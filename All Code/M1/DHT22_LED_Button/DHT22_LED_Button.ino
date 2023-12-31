meowz
meowz#7197

meowz — 04/04/2023 15:43
#include <TM1638plus.h>
#include "DHTesp.h"
#define Pin_DHT22 15 // D15 
#define Brd_STB 18 // strobe = GPIO connected to strobe line of module 
#define Brd_CLK 19 // clock = GPIO connected to clock line of module 
#define Brd_DIO 21 // data = GPIO connected to data line of module 
bool high_freq = true; //default false,, If using a high freq CPU > ~100 MHZ set to true.
DHTesp dht;
TM1638plus tm(Brd_STB, Brd_CLK , Brd_DIO, high_freq);
void setup() {
  Serial.begin(115200);
  dht.setup(Pin_DHT22, DHTesp::DHT22);
  tm.displayBegin();
}
void loop() {
  int h = dht.getHumidity()10;
  int t = dht.getTemperature()10;
  Serial.print("Temperature: ");
  Serial.print(t); Serial.print(" *C\t");
  Serial.print("Humidity: ");
  Serial.print(h); Serial.print(" %\n");
  int Tempp2 = t / 100; int Tempp1 = (t / 10) % 10; int Tempp0 = t % 10;
  int Humi2 = h / 100; int Humi1 = (h / 10) % 10; int Humi0 = h % 10;
  tm.displayHex(0, Tempp2);
  tm.displayASCIIwDot(1, Tempp1 + '0'); // turn on dot
  tm.displayHex(2, Tempp0);
  tm.display7Seg(3, B01011000); // Code=tgfedcba
  tm.displayHex(4, Humi2);
  tm.displayASCIIwDot(5, Humi1 + '0'); // turn on dot
  tm.displayHex(6, Humi0);
  tm.display7Seg(7, B01110100); // Code=tgfedcba
  delay(2000);
}
#include <TM1638plus.h>
#include "DHTesp.h"
#define Pin_DHT22 15 // D15 
#define Brd_STB 18 // strobe = GPIO connected to strobe line of module 
#define Brd_CLK 19 // clock = GPIO connected to clock line of module 
#define Brd_DIO 21 // data = GPIO connected to data line of module 
ขยาย
DHT22_with_TM1638.ino
2 KB
! J — 04/04/2023 16:30
ภาพ
ภาพ
ภาพ
#define Button1 22
#define LED1 19
#define Button2 23
#define LED2 18

int buttonState1 = 0;
ขยาย
Quiz101.ino
1 KB
#define DHT22_Pin 15 
#include "DHTesp.h" 
DHTesp dht;

void setup() { 
 Serial.begin(115200); 
ขยาย
Quiz102.ino
1 KB
#include <TM1638plus.h>
#include "DHTesp.h"
#define Pin_DHT22 15 // D15 
#define Brd_STB 18 // strobe = GPIO connected to strobe line of module 
#define Brd_CLK 19 // clock = GPIO connected to clock line of module 
#define Brd_DIO 21 // data = GPIO connected to data line of module 
ขยาย
Quiz103.ino
2 KB
meowz
 เริ่มการโทรเป็นเวลา 1 ชั่วโมง
 — 26/04/2023 18:02
meowz — 26/04/2023 18:03
ได้ไยินไๆหม
meowz — 26/04/2023 18:47
แท บัค
บวา
บา
meowz — 27/04/2023 14:53
[
    {
        "id": "8d8ede65.bc90c",
        "type": "tab",
        "label": "Flow 1",
        "disabled": false,
ขยาย
message.txt
11 KB
! J — 02/05/2023 15:15
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "DHTesp.h"
DHTesp dht;
#define PinLED1 18
ขยาย
Quiz203.ino
5 KB
! J — 02/05/2023 15:53
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "DHTesp.h"
DHTesp dht;
#define LED1 19
ขยาย
Quiz204.ino
4 KB
meowz
 เริ่มการโทรเป็นเวลา 2 นาที
 — 15/05/2023 20:57
meowz — 15/05/2023 20:57
ว่างยัง
meowz
 เริ่มการโทรเป็นเวลา 1 นาที
 — 15/05/2023 21:02
meowz
 เริ่มการโทรเป็นเวลา 13 นาที
 — 18/05/2023 23:57
! J — วันนี้ เวลา 15:14
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "DHTesp.h"
DHTesp dht;
#define LED1 2
ขยาย
Quiz204.ino
4 KB
﻿
! J
! J#3918
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "DHTesp.h"
DHTesp dht;
#define LED1 2
#define LED2 4
#define LED3 19
#define LED4 21
#define DHT22_Pin 15
int pushButton1 = 22;
int pushButton2 = 23;
const char* ssid = "jjjj";
const char* password = "0846894722";
const char* mqtt_server = "test.mosquitto.org";
const char* topic1 = "M1_QUIZ204";
String ledState1 = "NA";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
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
  Serial.print("\n"); Serial.println(myPayLoad);
  myPayLoad[4] = '\0'; // String lessthan 4 Charector
  if ((String)myPayLoad == "ON1") digitalWrite(LED1, HIGH);
  if ((String)myPayLoad == "OFF1") digitalWrite(LED1, LOW);
  if ((String)myPayLoad == "ON2") digitalWrite(LED2, HIGH);
  if ((String)myPayLoad == "OFF2") digitalWrite(LED2, LOW);
  if ((String)myPayLoad == "ON3") digitalWrite(LED3, HIGH);
  if ((String)myPayLoad == "OFF3") digitalWrite(LED3, LOW);
  if ((String)myPayLoad == "ON4") digitalWrite(LED4, HIGH);
  if ((String)myPayLoad == "OFF4") digitalWrite(LED4, LOW);
}
void reconnect()
{ while (!client.connected()) // Loop until we're reconnected
  { Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX); // Create a random client ID
    if (client.connect(clientId.c_str())) // Attempt to connect
    { Serial.println("connected"); // Once connected, publish an announcement...
      client.publish(topic1, "Hello World "); // ... and resubscribe
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
  setup_wifi();
  dht.setup(DHT22_Pin, DHTesp::DHT22);
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}
void loop()
{
  if (!client.connected()) reconnect();
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000)
  { lastMsg = now;
    ++value;
    float h = dht.getHumidity();
    float t = dht.getTemperature();
    sprintf (msg, "TempC: %.2f C, Humidity: %.2f %%", t, h);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic1, msg);
  }
  if (digitalRead(pushButton1) == 1) {
    sprintf (msg, "Overheat Alarm");
    Serial.println(msg);
    client.publish(topic1, msg);
    delay(500);
  }
  if (digitalRead(pushButton2) == 1) {
    sprintf (msg, "Intruders Alarm");
    Serial.println(msg);
    client.publish(topic1, msg);
    delay(500);
  }
}
