//Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6od203C3N"
#define BLYNK_TEMPLATE_NAME "404"
#define BLYNK_AUTH_TOKEN "Oil9XH-DPxk9XO31oVHUX6CDOskxtW0J"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
#define DHT22_Pin 15
const int btnPin = 18; //
const int btnPin2 = 19; //
#include <HTTPClient.h>
#define WebHooksKey "cMzh_G_IU01wts9_GJdxE8"
#define WebHooksEventNane "meowtestt"
#define WebHooksEventNane "ggsheet"
#define WebHooksEventNane_LINE "meowtestt"
#define My_NAME "B6310646"
#define testSwitch0 22 // 
#define testSwitch1 23 //
boolean btnState = false;
bool high_freq = true;
WidgetLED blynk_LED(V5);
BlynkTimer timer; // Announcing the timer
boolean btnState2 = false;
WidgetLED blynk_LED2(V6);
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "meow";
char pass[] = "meowmeow";
DHTesp dht;
//boolean btnState = false;
void setup()
{
  // Debug console
  Serial.begin(9600);
  dht.setup(DHT22_Pin, DHTesp::DHT22); // Connect DHT sensor to GPIO 15
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  pinMode(btnPin, INPUT_PULLDOWN);
  pinMode(btnPin2, INPUT_PULLDOWN);
  pinMode(testSwitch0, INPUT_PULLUP);
  pinMode(testSwitch1, INPUT_PULLUP);
  randomSeed(analogRead(33));
}
void myTimerEvent() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  boolean isPressed = (digitalRead(btnPin) == LOW);
  if (isPressed != btnState)
  { if (isPressed)
      blynk_LED.on();
    else
      blynk_LED.off();
    btnState = isPressed;
    Serial.print(" LED Status = ");
    Serial.println(btnState);
    if (isPressed)
      blynk_LED2.on();
    else
      blynk_LED2.off();
    btnState2 = isPressed;
    Serial.print(" LED Status = ");
    Serial.println(btnState2);
  }
  Serial.print(" Temp('C) >> "); Serial.print(temperature, 1);
  Serial.print(", Humidity(%) >> "); Serial.println(humidity, 1);
}
void loop() {
  Blynk.run();
  timer.run();
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Serial.println();
  Serial.print("\nTemperature('C) = ");
  Serial.print(temperature, 1);
  Serial.print("\tHumidity(%) = ");
  Serial.print(humidity, 1);
  String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventNane) + "/with/key/" +
                      String(WebHooksKey);
  String httpRequestData = "value1=" + String(My_NAME) + "&value2=" + String(temperature) + "&value3=" +
                           String(humidity);
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(httpRequestData);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
    if (httpResponseCode == 1000)
      Serial.println(" --> Successfully sent");
    else
      Serial.println(" --> Failed!");
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  if (temperature > 20) {

    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventNane_LINE) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" + String(temperature);
    Serial.println();
    Serial.println("Server Name >> " + serverName);
    Serial.println("json httpRequestData >> " + httpRequestData);
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      if (httpResponseCode == 1000)
        Serial.println("[Line] --> Successfully sent");
      else
        Serial.println("[Line] --> Failed!");
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
  if (digitalRead(testSwitch0) == LOW) {
    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventNane_LINE) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" + String("Door Open Alarm");
    Serial.println("Server Name :" + serverName);
    Serial.println("json httpRequestData :" + httpRequestData);
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      if (httpResponseCode == 200)
        Serial.println("Successfully sent");
      else
        Serial.println("Failed!");
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    Serial.print(" >> Wait for 10 Sec --> ");
    for (int i = 9; i >= 0; i--) {
      Serial.print(i);
      delay(1000);
    }
    Serial.println(" >> Ready");
  }
  if (digitalRead(testSwitch1) == LOW) {
    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventNane_LINE) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" + String("Intruders Alarm");
    Serial.println("Server Name :" + serverName);
    Serial.println("json httpRequestData :" + httpRequestData);
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      if (httpResponseCode == 200)
        Serial.println("Successfully sent");
      else
        Serial.println("Failed!");
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    Serial.print(" >> Wait for 10 Sec --> ");
    for (int i = 9; i >= 0; i--) {
      Serial.print(i);
      delay(1000);
    }
    Serial.println(" >> Ready");
  }
  delay(10000);
}
