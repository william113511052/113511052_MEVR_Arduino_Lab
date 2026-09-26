// --- A 組：外部中斷 ---
const int buttonPinA = 2; 
const int ledPinA = 13;
volatile bool ledStateA = LOW;

// --- B 組：輪詢 ---
const int buttonPinB = 4; 
const int ledPinB = 12;
bool ledStateB = LOW;
bool lastButtonStateB = LOW; 

void setup() {
  pinMode(ledPinA, OUTPUT);
  pinMode(buttonPinA, INPUT); 
  attachInterrupt(digitalPinToInterrupt(buttonPinA), buttonISR, RISING);

  pinMode(ledPinB, OUTPUT);
  pinMode(buttonPinB, INPUT);
}

void buttonISR() {
  ledStateA = !ledStateA;
  digitalWrite(ledPinA, ledStateA);
}

void loop() {
  bool currentButtonStateB = digitalRead(buttonPinB);
  
  if (currentButtonStateB == HIGH && lastButtonStateB == LOW) {
    ledStateB = !ledStateB;
    digitalWrite(ledPinB, ledStateB);
  }

  lastButtonStateB = currentButtonStateB;

  delay(2000); 
}
