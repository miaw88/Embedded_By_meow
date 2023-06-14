#include "ModbusMaster.h"
#define SLAVE_ID 11
#define CTRL 5
#define RX 16
#define TX 17
ModbusMaster modbus;
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
  modbus.begin(SLAVE_ID, Serial2);
  modbus.preTransmission(preTransmission);
  modbus.postTransmission(postTransmission);
}
long lastMillis = 0;
void loop() {
  long currentMillis = millis();
  if (currentMillis - lastMillis > 1000) {
    uint8_t result = modbus.readInputRegisters(1, 2); // start addr, read size
    if (getResultMsg(&modbus, result)) {
      Serial.println();
      double res_buffer = modbus.getResponseBuffer(0) / 10;
      String response = "Temperature: " + String(res_buffer) + " C\r\n";
      res_buffer = modbus.getResponseBuffer(1) / 10;
      response += "Humidity: " + String(res_buffer) + " %";
      Serial.println(response);
    }
    lastMillis = currentMillis;
  }
}
bool getResultMsg(ModbusMaster *node, uint8_t result) {
  String tmpstr2 = "\r\n";
  switch (result) {
    case node->ku8MBSuccess:
      return true;
      break;
    case node->ku8MBIllegalFunction:
      tmpstr2 += "Illegal Function";
      break;
    case node->ku8MBIllegalDataAddress:
      tmpstr2 += "Illegal Data Address";
      break;
    case node->ku8MBIllegalDataValue:
      tmpstr2 += "Illegal Data Value";
      break;
    case node->ku8MBSlaveDeviceFailure:
      tmpstr2 += "Slave Device Failure";
      break;
    case node->ku8MBInvalidSlaveID:
      tmpstr2 += "Invalid Slave ID";
      break;
    case node->ku8MBInvalidFunction:
      tmpstr2 += "Invalid Function";
      break;
    case node->ku8MBResponseTimedOut:
      tmpstr2 += "Response Timed Out";
      break;
    case node->ku8MBInvalidCRC:
      tmpstr2 += "Invalid CRC";
      break;
    default:
      tmpstr2 += "Unknown error: " + String(result);
      break;
  }
  Serial.println(tmpstr2);
  return false;
}
