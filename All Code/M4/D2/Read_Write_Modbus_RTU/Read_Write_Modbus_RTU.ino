#include "ModbusMaster.h"
#define SLAVE_ID 1
#define CTRL 5
#define RX 16
#define TX 17
#define LED_MONITOR 2
ModbusMaster node;
void preTransmission() {
  digitalWrite(CTRL, HIGH);
}
void postTransmission() {
  digitalWrite(CTRL, LOW);
}
void setup() {
  pinMode(CTRL, OUTPUT);
  digitalWrite(CTRL, LOW);
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX, TX);
  node.begin(SLAVE_ID, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}
int read_relay() {
  uint8_t result;
  uint8_t value = 0xff;
  result = node.readDiscreteInputs(0, 8); // Start=0, nByte=4
  if (result == node.ku8MBSuccess) {
    value = node.getResponseBuffer(0); // Read return from 0_Byte
  }
  return value;
}
void binDisplay(int dataIn) {
  if (dataIn == 0xff) {
    Serial.println("Read Error");
  }
  else {
    Serial.print(dataIn >> 1 & 1);
    Serial.print(dataIn >> 0 & 1);
    Serial.println();
  }
}
void loop() {
  node.writeSingleCoil(0, 0x00FF); delay(2000); // On Relay0
  binDisplay(read_relay());
  node.writeSingleCoil(0, 0x0000); delay(2000); // Off Relay0

  node.writeSingleCoil(1, 0x00FF); delay(2000); // On Relay1
  binDisplay(read_relay());
  node.writeSingleCoil(1, 0x0000); delay(2000); // Off Relay1
}
