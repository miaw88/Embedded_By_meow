#include <WiFi.h>
const char* ssid = "meow";
const char* password = "meowmeow";
int pin2 = 2;
int pin4 = 4;
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  pinMode(pin2, OUTPUT); // set the LED pin mode
  pinMode(pin4, OUTPUT); // set the LED pin mode
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
bool LED_Status_2 = LOW;
bool LED_Status_4 = LOW;
void loop() {
  digitalWrite(pin2, LED_Status_2);
  digitalWrite(pin4, LED_Status_4);
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
            client.println("<h1>LED Status</h1>");
            client.println("<p>");
            if (LED_Status_2 == HIGH)
              client.println("LED On 2");
            else if (LED_Status_2 == LOW)
              client.println("LED Off 2");
            client.println(",");
            if (LED_Status_4 == HIGH)
              client.println("LED On 4");
            else if (LED_Status_4 == LOW)
              client.println("LED Off 4");
            client.println("<p>");
            client.println("<a href=\"/ledon_2\"><button style = \"background-color: #BF40BF;\">LED On</button></a>");
            client.println("<a href=\"/ledoff_2\"><button style = \"background-color: #BF40BF;\">LED Off</button></a>");
            client.println("</p>");

            client.println("<a href=\"/ledon_4\"><button style = \"background-color: #76D7C4;\">LED On</button></a>");
            client.println("<a href=\"/ledoff_4\"><button style = \"background-color: #76D7C4;\">LED Off</button></a>");
            client.println("</p>");

            client.println("<body>");
            client.println("<html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /ledon_2")) LED_Status_2 = HIGH;
        if (currentLine.endsWith("GET /ledoff_2")) LED_Status_2 = LOW;
        if (currentLine.endsWith("GET /ledon_4")) LED_Status_4 = HIGH;
        if (currentLine.endsWith("GET /ledoff_4")) LED_Status_4 = LOW;
      }
    }
    client.stop(); // close the connection:
    Serial.println("Client Disconnected.");
  }
}
