#include <SoftwareSerial.h>

#define DEBUG

SoftwareSerial bluetooth(14, 15); // Rx, Tx

const int AIN1 = 2;
const int AIN2 = 4;
const int PWMA = 3;
const int BIN1 = 7;
const int BIN2 = 8;
const int PWMB = 5;
const int STBY = 6;

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
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);
}

void loop() {
    while(bluetooth.available()) {
      //Serial.println(bluetooth.read());
      switch(bluetooth.read()) {
        case 'w':
          #ifdef DEBUG
          Serial.println("Going forward!");
          #endif
          goForward();
          break;
        case 's':
          #ifdef DEBUG
          Serial.println("Going backward!");
          #endif
          goBackward();
          break;
        case 'a':
          #ifdef DEBUG
          Serial.println("Turn left!");
          #endif
          turnLeft();
          break;
        case 'd':
          #ifdef DEBUG
          Serial.println("Turn right!");
          #endif
          turnRight();
          break;
        case 'x':
        case 'z':
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

void turnLeft() {
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, targetSpeed);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, targetSpeed);  
}

void turnRight() {
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, targetSpeed);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, targetSpeed);  
}

void stopMotors() {
  analogWrite(PWMB, 0);
  analogWrite(PWMA, 0);  
}
