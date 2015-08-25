#include <SoftwareSerial.h>

#define DEBUG

SoftwareSerial bluetooth(15, 14); // Rx, Tx

const int BIN1 = 2;
const int BIN2 = 4;
const int PWMB = 3;
const int AIN1 = 7;
const int AIN2 = 8;
const int PWMA = 5;

int targetSpeed = 150;

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  bluetooth.begin(9600);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() {
    while(bluetooth.available()) {
      //Serial.println(bluetooth.read());
      switch(bluetooth.read()) {
        case 'f':
          #ifdef DEBUG
          Serial.println("Going forward!");
          #endif
          goForward();
          break;
        case 'b':
          #ifdef DEBUG
          Serial.println("Going backward!");
          #endif
          goBackward();
          break;
        case 's':
          #ifdef DEBUG
          Serial.println("Stop motors!");
          #endif
          stopMotors();
          break;
        default:
          #ifdef DEBUG
          Serial.println("Unknow command!");
          #endif
          stopMotors();
          break;
      }
    }
}

void goForward() {
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, targetSpeed);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, targetSpeed);  
}

void goBackward() {
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, targetSpeed);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, targetSpeed);  
}

void stopMotors() {
  analogWrite(PWMB, 0);
  analogWrite(PWMA, 0);  
}
