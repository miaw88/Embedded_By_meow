//Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6Mi8FFufQ"
#define BLYNK_TEMPLATE_NAME "4LED"
#define BLYNK_AUTH_TOKEN "Yhbd5nxPXx9oBdoZNabz7dvZtP8WN-wd"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
#define DHT22_Pin 15
const int btnPin1 = 18; //
const int btnPin2 = 19; //
boolean btnState = false;
WidgetLED blynk_LED(V0);
BlynkTimer timer; // Announcing the timer
boolean btnState2 = false;
WidgetLED blynk_LED2(V1);
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
  pinMode(btnPin1, INPUT_PULLDOWN);
  pinMode(btnPin2, INPUT_PULLDOWN);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}
void myTimerEvent() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Blynk.virtualWrite(V5, temperature);
  Blynk.virtualWrite(V6, humidity);
  boolean isPressed = (digitalRead(btnPin1) == LOW);
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
void loop()
{
  Blynk.run();
  timer.run();
}
