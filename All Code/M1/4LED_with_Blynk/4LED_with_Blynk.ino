//Blynk
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6Mi8FFufQ"
#define BLYNK_TEMPLATE_NAME "4LED"
#define BLYNK_AUTH_TOKEN "Yhbd5nxPXx9oBdoZNabz7dvZtP8WN-wd"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "meow";
char pass[] = "meowmeow";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}
