#include <TimerOne.h>

// --- A 組 (計時器中斷控制) 腳位 ---
const int buttonPinA = 2;
const int ledPinA = 13;

// --- B 組 (主迴圈輪詢控制) 腳位 ---
const int buttonPinB = 4;
const int ledPinB = 12;

void timer_int() {
  bool stateA = digitalRead(buttonPinA);
  digitalWrite(ledPinA, stateA);
}

void setup() {
  pinMode(buttonPinA, INPUT);
  pinMode(ledPinA, OUTPUT);
  pinMode(buttonPinB, INPUT);
  pinMode(ledPinB, OUTPUT);

  Timer1.initialize(50000); 
  Timer1.attachInterrupt(timer_int); 
}

void loop() {
  bool stateB = digitalRead(buttonPinB);
  digitalWrite(ledPinB, stateB);

  delay(1000); 
}
