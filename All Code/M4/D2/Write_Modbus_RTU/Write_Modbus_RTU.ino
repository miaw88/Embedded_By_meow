#define RS485TX HIGH
#define RS485RX LOW
#define RS485CTRL 5
#define LED_MONITOR 2
int stepCount = 0;
int eindex = 0;
byte byteSend;
byte echo[20];
byte cmd_on[] = {0x03, 0x06, 0x00, 0x01, 0x01, 0x00, 0xD8, 0x78};
byte cmd_off[] = {0x03, 0x06, 0x00, 0x01, 0x02, 0x00, 0xD8, 0x88};
byte cmd_read[] = {0x03, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD4, 0x28};
String mapData(byte number) {
  switch (number) {
    case 1 : return "On";
    case 2 : return "Off";
    default : return "Invalid State";
  }
}
void setup() {
  pinMode(RS485CTRL, OUTPUT);
  pinMode(LED_MONITOR, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(9600);
  digitalWrite(RS485CTRL, RS485RX);
  Serial.println("Start Test MODBUS RTU");
}
void loop() {
  Serial.print("\nTest(");
  Serial.print(++stepCount);
  Serial.print(") > ");
  digitalWrite(LED_MONITOR, HIGH);
  digitalWrite(RS485CTRL, RS485TX);
  delay(10);
  if ((stepCount % 2) == 0) {
    for (int i = 0; i < sizeof(cmd_on); i++) {
      Serial2.write(cmd_on[i]);
    }
  }
  else {
    for (int i = 0; i < sizeof(cmd_off); i++) {
      Serial2.write(cmd_off[i]);
    }
  }
  delay(10);
  digitalWrite(RS485CTRL, RS485RX);
  digitalWrite(LED_MONITOR, LOW);
  delay(10);
  digitalWrite(LED_MONITOR, HIGH);
  digitalWrite(RS485CTRL, RS485TX);
  delay(10);
  for (int i = 0; i < sizeof(cmd_read); i++) {
    Serial2.write(cmd_read[i]);
  }
  delay(10);
  digitalWrite(RS485CTRL, RS485RX);
  digitalWrite(LED_MONITOR, LOW);
  eindex = 0;
  for (long int i = 0; i < 600000; i++) {
    if (Serial2.available())
      echo[eindex++] = Serial2.read();
    if (eindex > 12) i = 999999;
  }
  Serial.print("Relay " + String(echo[1]) + " is " + mapData(echo[2]));

  delay(5000);
}
