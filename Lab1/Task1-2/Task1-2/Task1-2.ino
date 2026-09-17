const int potPin = A0;   
const int buttonPin = 2;   

const int pinB = 9;        
const int pinR = 10;     
const int pinG = 11;      

bool greenState = false; 

void setup() {
  pinMode(pinB, OUTPUT);
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(buttonPin, INPUT); 
  
  Serial.begin(9600);
}

void loop() {
  
  int sensorValue = analogRead(potPin);
  int bluePwm = sensorValue / 4; 
  analogWrite(pinB, bluePwm);

  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(pinR, HIGH);
  } else {
    digitalWrite(pinR, LOW);
  }

  if (Serial.available() > 0) {
    char inChar = Serial.read();
    
    if (inChar == '1') {
      greenState = true;
      Serial.println("Green Light Brightness: 255");
    } 
    else if (inChar == '0') {
      greenState = false;
      Serial.println("Green Light Brightness: 0");
    }
  }

  if (greenState) {
    digitalWrite(pinG, HIGH);
  } else {
    digitalWrite(pinG, LOW);
  }
}
