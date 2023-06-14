#define RS485TX HIGH
#define RS485RX LOW
#define RS485CTRL 5
#define LED_MONITOR 2
int stepCount = 0;
int eindex = 0;
byte echo[20];
byte slaveID = 0x05;
byte modbusCMD = 0x05;
byte h_relayID = 0x00;
byte l_relayID = 0x00;
byte relay_on = 0xFF;
byte relay_off = 0x00;
byte on_off_delay = 0x00;
byte h_byteCRC = 0;
byte l_byteCRC = 0;
void setup() {
 pinMode(RS485CTRL, OUTPUT);
 pinMode(LED_MONITOR, OUTPUT);
 Serial.begin(9600);
 Serial2.begin(9600);
 digitalWrite(RS485CTRL, RS485RX);
 Serial.println("Start Test MODBUS RTU");
}
uint16_t CRC16_Update(uint16_t tempCRC, uint8_t inData) {
 tempCRC ^= inData;
 for(int i = 0; i < 8; i++) {
 if(tempCRC & 1) {
 tempCRC = (tempCRC >> 1) ^ 0xA001;
 }
 else {
 tempCRC = tempCRC >> 1;
 }
 }
 return tempCRC;
}
uint16_t sendByte_CRCUpdate(uint16_t tempCRC, uint8_t inData) {
 Serial2.write(inData);
 if(inData < 0x10) Serial.print("0");
 Serial.print(inData, HEX);
 Serial.print(" ");
 tempCRC = CRC16_Update(tempCRC, inData);
 return tempCRC;
}
void relayCTRL(int relay_id, byte relay_cmd) {
 uint16_t calculateCRC = 0xFFFF;
 h_relayID = highByte(relay_id);
 l_relayID = lowByte(relay_id);
 digitalWrite(LED_MONITOR, HIGH);
 digitalWrite(RS485CTRL, RS485TX);
 delay(10);
 calculateCRC = sendByte_CRCUpdate(calculateCRC, slaveID);
 calculateCRC = sendByte_CRCUpdate(calculateCRC, modbusCMD);
 calculateCRC = sendByte_CRCUpdate(calculateCRC, h_relayID);
 calculateCRC = sendByte_CRCUpdate(calculateCRC, l_relayID);
 calculateCRC = sendByte_CRCUpdate(calculateCRC, relay_cmd);
 calculateCRC = sendByte_CRCUpdate(calculateCRC, on_off_delay);
 h_byteCRC = highByte(calculateCRC);
 l_byteCRC = lowByte(calculateCRC);
 calculateCRC = sendByte_CRCUpdate(calculateCRC, l_byteCRC);
 calculateCRC = sendByte_CRCUpdate(calculateCRC, h_byteCRC);
 delay(10);
 digitalWrite(RS485CTRL, RS485RX);
 digitalWrite(LED_MONITOR, LOW);
 Serial.println();
}
void loop() {
 for(int relay = 0; relay < 2; relay++) {
 relayCTRL(relay, relay_on);
 delay(3000);
 }
 for(int relay = 0; relay < 2; relay++) {
 relayCTRL(relay, relay_off);
 delay(3000);
 }
}
