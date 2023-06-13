#include "ModbusMaster.h" //hIps://github.com/4-20ma/ModbusMaster
#define Slave_ID_WhiteSS 11
#define RX_PIN 26
#define TX_PIN 27
ModbusMaster modbus1;
void setup() {
  Serial.begin(115200, SERIAL_8N1);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  modbus1.begin(Slave_ID_WhiteSS, Serial2);
}
long lastMillis = 0;
double GetData_DBL;
void loop() {
  long currentMillis = millis();
  if (currentMillis - lastMillis > 1000) {
    uint8_t result = modbus1.readInputRegisters(1, 2);
    if (getResultMsg(&modbus1, result)) {
      Serial.println();
      GetData_DBL = modbus1.getResponseBuffer(0) / 10.0;
      String res = "Temperature: " + String(GetData_DBL) + " C\r\n";
      GetData_DBL = modbus1.getResponseBuffer(1) / 10.0;
      res += "Humidity: " + String(GetData_DBL) + " %";
      Serial.println(res);
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
      tmpstr2 += "Illegal FuncSon";
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
      tmpstr2 += "Invalid FuncSon";
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
