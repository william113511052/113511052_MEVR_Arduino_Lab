#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); 

const int buttonPin = 2; 
const int ledPin = 13;  

bool lastButtonState = LOW;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
  
  BTSerial.begin(9600); 
  Serial.println("Bluetooth Two-Way System Ready!");
}

void loop() {
  if (BTSerial.available() > 0) {
    char cmd = BTSerial.read();
    
    Serial.print("BT Received: ");
    Serial.println(cmd);

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
      BTSerial.println("Button Pressed!"); 
      Serial.println("Sent via BT: Button Pressed!");
    } else {
      BTSerial.println("Button Released");  
      Serial.println("Sent via BT: Button Released");
    }
    delay(50);
  }
  
  lastButtonState = currentButtonState;
}
