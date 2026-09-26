#include <Servo.h>

Servo myservo;

const int trigPin = 10;
const int echoPin = 11;

const int servoPin = 9;

void setup() {
  myservo.attach(servoPin);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  
  int distance = duration * 0.034 / 2;
  
  int targetAngle = map(distance, 5, 30, 0, 180);
  
  targetAngle = constrain(targetAngle, 0, 180);
  
  myservo.write(targetAngle);
  
  Serial.print("距離: ");
  Serial.print(distance);
  Serial.print(" cm, 角度: ");
  Serial.println(targetAngle);
  
  delay(100);
}
