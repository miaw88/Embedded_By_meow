// ESP-32
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <BlynkSimpleEsp32.h>
#include "SHTC3.h"
#include <TridentTD_LineNotify.h>
const int btn1 = 5; // D5
const int btn2 = 18; // D18
BlynkTimer timer; // Announcing the timer
SHTC3 s(Wire);
char auth[] = "cKFubINNWZz1CHN8JWMdFrRZlS_9-rMJ";
char ssid[] = "jjjj";
char pass[] = "0846894722";
#define LINE_TOKEN "fWrGx9puXSjcNp8zCeBtWQuSoWGivkU5OWBAJN0UfAn"
float temperature = 12.34, humidity = 56.78;
String t;
const char* host = "script.google.com";
const int httpsPort = 443;
String GAS_ID = "AKfycbxSgB94HkFJmP0-1Iviyy6XLQWVMt7zC60bzjKjPmHTY6Omzcq_8SlzsLj5chFRlVyr";
String GAS_Sheet = "Sensor_Data";
WiFiClientSecure client;

void sendData(float SValue1, float SValue2) {
  Serial.println("==========");
  Serial.print("connecting to "); Serial.println(host);
  //---- Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //---- Post Data
  String url;
  url += "/macros/s/" + GAS_ID + "/exec?";
  url += "id=" + String(GAS_Sheet);
  url += "&Sensor1=" + String(SValue1, 2);
  url += "&Sensor2=" + String(SValue2, 2);
  Serial.print("requesting URL: "); Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println("request sent");
  //---- Wait Echo
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("ESP-32/Arduino CI successfull!");
  } else {
    Serial.println("ESP-32/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
}

void myTimerEvent()
{ s.begin(true);
  temperature = s.readTempC();
  humidity = s.readHumidity();
  Blynk.virtualWrite(V10, temperature);
  Blynk.virtualWrite(V11, humidity);
  Serial.print(" Temp('C) >> "); Serial.print(temperature, 1);
  Serial.print(", Humidity(%) >> "); Serial.println(humidity, 1);
  sendData(temperature, humidity);
  if (temperature > 28) {
    LINE.notify("อุณหภูมิ เกินกําหนด");
    LINE.notify(temperature, 5); // จํานวนจริง แสดง 5 หลัก
  }
  if (digitalRead(btn1) == LOW)
  { LINE.notify("Overheat Alarm");
    delay(100);
  }
  if (digitalRead(btn2) == LOW)
  { LINE.notify("Intruders Alarm");
    delay(100);
  }
}

void setup()
{ Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Wire.begin(15, 4);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  Blynk.begin(auth, ssid, pass);
  LINE.setToken(LINE_TOKEN);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{ Blynk.run();
  timer.run(); // running timer every 250ms
}
