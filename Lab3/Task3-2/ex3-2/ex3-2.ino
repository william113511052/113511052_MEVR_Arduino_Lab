const int buttonPin = 2; 
const int ledPin = 13;   

bool lastButtonState = LOW; 

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600); 
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == '1') {
      digitalWrite(ledPin, HIGH);
    } 
    else if (cmd == '0') {
      digitalWrite(ledPin, LOW);
    }
  }

  bool currentButtonState = digitalRead(buttonPin);
  
  if (currentButtonState != lastButtonState) {
    if (currentButtonState == HIGH) {
      Serial.println("Button Pressed!");  
    } else {
      Serial.println("Button Released");  
    }
    delay(50); 
  }
  
  lastButtonState = currentButtonState;
}
