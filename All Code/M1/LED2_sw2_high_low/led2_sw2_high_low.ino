#define pushButton22 2
#define pushButton23 5
#define LEDPin19 19
#define LEDPin18 18
int buttonState22_19 = 0;
int buttonState23_18 = 0;
void setup() {
  Serial.begin(115200);
  pinMode(pushButton22, INPUT_PULLUP);
  pinMode(pushButton23, INPUT_PULLUP);
  pinMode(LEDPin19, OUTPUT);
  pinMode(LEDPin18, OUTPUT);
}
void loop() {
  if (digitalRead(pushButton22) == LOW) {
//    Serial.println(buttonState);
    buttonState22_19 = 1 - buttonState22_19; //0
//    Serial.println(buttonState);
    digitalWrite(LEDPin19, buttonState22_19); //1
    while (digitalRead(pushButton22) == LOW);
    delay(20);
  }
  else if (digitalRead(pushButton23) == LOW) {
    buttonState23_18 = 1 - buttonState23_18;
    digitalWrite(LEDPin18, buttonState23_18);
    while (digitalRead(pushButton23) == LOW);
    delay(20);
  }
}
