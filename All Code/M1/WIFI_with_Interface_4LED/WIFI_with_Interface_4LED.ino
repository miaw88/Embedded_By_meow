#include <WiFi.h>
const char* ssid = "meow";
const char* password = "meowmeow";
int pin5 = 5;
int pin18 = 18;
int pin19 = 19;
int pin21 = 21;
WiFiServer server(80);
#define DHT22_Pin 15
#include "DHTesp.h"
DHTesp dht;
void setup() {
  Serial.begin(115200);
  dht.setup(DHT22_Pin, DHTesp::DHT22); // Connect DHT sensor to GPIO 15
  pinMode(pin5, OUTPUT); // set the LED pin mode
  pinMode(pin18, OUTPUT); // set the LED pin mode
  pinMode(pin19, OUTPUT); // set the LED pin mode
  pinMode(pin21, OUTPUT); // set the LED pin mode
  delay(10);
  Serial.print("\n\nConnecting to "); Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected."); Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); server.begin();
}
int value = 0;
bool LED_Status_5 = LOW;
bool LED_Status_18 = LOW;
bool LED_Status_19 = LOW;
bool LED_Status_21 = LOW;
void loop() {
  digitalWrite(pin5, LED_Status_5);
  digitalWrite(pin18, LED_Status_18);
  digitalWrite(pin19, LED_Status_19);
  digitalWrite(pin21, LED_Status_21);
  WiFiClient client = server.available(); // listen for incoming clients
  if (client) { // if you get a client,
    Serial.println("New Client."); // print a message out the serial port
    String currentLine = ""; // make a String to hold incoming data from the client
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c); // print it out the serial monitor
        if (c == '\n') { // if the byte is a newline character
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html>");
            client.println("<body>");
            client.println("<h1>The ESP-32 Update web page without refresh</h1>");
            client.println("<p>");
            client.println("<a href=\"/ledon_5\"><button style = \"background-color: #BF40BF;\">LED1 ON</button></a>");
            client.println("<a href=\"/ledon_18\"><button style = \"background-color: #BF40BF;\">LED2 ON</button></a>");
            client.println("<a href=\"/ledon_19\"><button style = \"background-color: #BF40BF;\">LED3 ON</button></a>");
            client.println("<a href=\"/ledon_21\"><button style = \"background-color: #BF40BF;\">LED4 ON</button></a>");
            client.println("</p>");

            client.println("<a href=\"/ledoff_5\"><button style = \"background-color: #76D7C4;\">LED1 OFF</button></a>");
            client.println("<a href=\"/ledoff_18\"><button style = \"background-color: #76D7C4;\">LED2 OFF</button></a>");
            client.println("<a href=\"/ledoff_19\"><button style = \"background-color: #76D7C4;\">LED2 OFF</button></a>");
            client.println("<a href=\"/ledoff_21\"><button style = \"background-color: #76D7C4;\">LED2 OFF</button></a>");
            client.println("</p>");

            client.println("State of[LED1,LED2,LED3,LED4] is >> ");
            if (LED_Status_5 == HIGH)
              client.println("ON");
            else if (LED_Status_5 == LOW)
              client.println("OFF");
            client.println(",");
            if (LED_Status_18 == HIGH)
              client.println("ON");
            else if (LED_Status_18 == LOW)
              client.println("OFF");
            client.println(",");
            if (LED_Status_19 == HIGH)
              client.println("ON");
            else if (LED_Status_19 == LOW)
              client.println("OFF");
            client.println(",");
            if (LED_Status_21 == HIGH)
              client.println("ON");
            else if (LED_Status_21 == LOW)
              client.println("OFF");
            client.println("<p>");

            delay(dht.getMinimumSamplingPeriod());
            float humidity = dht.getHumidity();
            float temperature = dht.getTemperature();
            client.print("Temperature: ");
            client.print(temperature, 1);
            client.print("C/");
            client.print(dht.toFahrenheit(temperature), 1);
            client.print("F. Humidity: ");
            client.print(humidity, 1);
            client.print("%\n");
            delay(2000);
            client.println("<p>");

            client.println("<br><a href=\"https://www.facebook.com/miaw.supanan/\">Facebook: Supanan Rueangsook</a>");

            client.println("<body>");
            client.println("<html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /ledon_5")) LED_Status_5 = HIGH;
        if (currentLine.endsWith("GET /ledoff_5")) LED_Status_5 = LOW;
        if (currentLine.endsWith("GET /ledon_18")) LED_Status_18 = HIGH;
        if (currentLine.endsWith("GET /ledoff_18")) LED_Status_18 = LOW;
        if (currentLine.endsWith("GET /ledon_19")) LED_Status_19 = HIGH;
        if (currentLine.endsWith("GET /ledoff_19")) LED_Status_19 = LOW;
        if (currentLine.endsWith("GET /ledon_21")) LED_Status_21 = HIGH;
        if (currentLine.endsWith("GET /ledoff_21")) LED_Status_21 = LOW;
      }
    }
    client.stop(); // close the connection:
    Serial.println("Client Disconnected.");
  }
}
