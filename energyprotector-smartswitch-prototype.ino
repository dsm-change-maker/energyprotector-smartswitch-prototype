//#include <SoftwareSerial.h>
#include <Servo.h>

#define LED_GREEN 11
#define LED_RED 12
#define BUTTON_POWER 2

//#define JSON_SUCCESS_TRUE "{\n\"is_success\":\"true\"}"
//#define JSON_SUCCESS_FALSE "{\n\"is_success\":\"false\"}"

Servo servo;
//SoftwareSerial esp12(4, 5); // esp12(TX, RX)

volatile byte state = LOW;
/*
const char* ssid = "iptime";
const char* pass = "";

bool esp12_reset();
String esp12_sendCmd(const __FlashStringHelper* cmd, unsigned int timeout=10000);
String esp12_readUntil(unsigned int timeout=10000, const char sep=0);
String esp12_emptyBuffer();
*/
void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON_POWER, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_POWER), powerToggle, FALLING);

  servo.attach(9);

  Serial.begin(9600);
  //esp12.begin(9600);
  //esp12.setTimeout(5000);
  
  //esp12_reset();
  
  //delay(1000);
}

void loop() {
  digitalWrite(LED_GREEN, state);
  digitalWrite(LED_RED, !state);
  servo.write(0 + 90 * state);
  /*
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String income_AP = client.readStringUntil('\n');
        if (income_AP.indexOf("switch/on") != -1) {
          state = HIGH;
          json_result = 1;
        } else if (income_AP.indexOf("switch/off") != -1) {
          state = LOW;
          json_result = 1;
        }
        
        digitalWrite(LED_GREEN, state);
        digitalWrite(LED_RED, !state);
        servo.write(0 + 90 * state);
        
        client.flush();
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/json");
        client.println("Connection: close");
        client.println();
        client.print(json_result ? JSON_SUCCESS_TRUE : JSON_SUCCESS_FALSE);
        client.println();
        delay(1);
        break;
      }
    }
    client.stop();
  }
  */
}

void powerToggle() {
  // prevent chattering
  delayMicroseconds(2000);
  if (digitalRead(BUTTON_POWER) != LOW) return;
  
  state = !state;
  //digitalWrite(LED_GREEN, state);
  //digitalWrite(LED_RED, !state);
  //servo.write(0 + 90 * state);
}
/*
bool esp12_reset()
{
  Serial.println(F(">> RESET"));

  esp12_sendCmd(F("AT+RST"));
  delay(4000);
  esp12_emptyBuffer();

  esp12_sendCmd(F("ATE0"));
  
  esp12_sendCmd(F("AT+CWMODE=1"));
  delay(200);

  esp12_sendCmd(F("AT+CIPMUX=1"));
  
  esp12_sendCmd(F("AT+CWQAP"));
  delay(200);

  String s = esp12_sendCmd(F("AT"));
  Serial.println(s);
  
  bool r = s == "\r\nOK\r\n";
  Serial.println(r);

  Serial.print("RES:'");
  for (int i = 0; s.length()>i; i++) {
    Serial.print(((int)s[i]));
    Serial.print(" ");
  }
  Serial.println("'");

  s = '\''+s+'\'';
  Serial.println(s);
  

  return r;
}

String esp12_sendCmd(const __FlashStringHelper* cmd, unsigned int timeout=10000)
{
  esp12_emptyBuffer();
  esp12.println(cmd);
  delay(200);
  String result = esp12_readUntil(timeout);
  Serial.print("RUN CMD : ");
  Serial.println(cmd);
  Serial.print("RUN RES : ");
  Serial.println(result);
  return result;
}

String esp12_readUntil(unsigned int timeout=10000, const char sep=0)
{
  String result = "";
  char c;
  unsigned long start = millis();

  while (millis() - start < timeout) {
    while (esp12.available()) {
      c = (char)esp12.read();
      if (sep != 0 && c == sep) {
        break;
      }
      result += c;
    }
    if (result != "") {
      break;
    }
  }
  
  if (result == "" && millis() - start >= timeout) {
    Serial.print("TIME OUT:");
    Serial.println(result);
    result = "TIME OUT";
  }
  
  return result;
}

String esp12_emptyBuffer()
{
  String result = "";
  char c;
  while(esp12.available()) {
    c = esp12.read();
    result += c;
  }
  return result;
}
*/
