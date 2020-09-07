#include <SoftwareSerial.h>
#include <Servo.h>

#define LED_POWER 12
#define BUTTON_POWER 2

Servo servo;

volatile byte state = LOW;

void setup() {
  pinMode(LED_POWER, OUTPUT);
  pinMode(BUTTON_POWER, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_POWER), powerToggle, FALLING);

  servo.attach(9);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_POWER, state);
  servo.write(0 + 90 * state);

  String str;
  
  if (Serial.available()) {
    str = Serial.readString();
    Serial.println("'" + str + "'");
  }
  
  if (str == "t\r\n") {
    state = !state;
  }
}

void powerToggle() {
  // prevent chattering
  delayMicroseconds(400000);
  if (digitalRead(BUTTON_POWER) != LOW) return;
  Serial.println("TOGGLE");
  
  Serial.println(state);
  
  state = !state;
}
