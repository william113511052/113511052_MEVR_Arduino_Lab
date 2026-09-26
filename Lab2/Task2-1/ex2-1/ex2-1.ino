const int enPin = 9;   
const int in1Pin = 4;  
const int in2Pin = 5; 
const int potPin = A0;

void setup() {
  pinMode(enPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int motorSpeed = 0;

  if (potValue > 530) {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    
    motorSpeed = map(potValue, 531, 1023, 0, 255);
  }

  else if (potValue < 490) {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    
    motorSpeed = map(potValue, 489, 0, 0, 255);
  }

  else {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    motorSpeed = 0;
  }

  analogWrite(enPin, motorSpeed);
  
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print("\t PWM Speed: ");
  Serial.println(motorSpeed);
  
  delay(50);
}
