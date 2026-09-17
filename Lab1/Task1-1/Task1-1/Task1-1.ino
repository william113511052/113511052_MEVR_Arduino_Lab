const int potPin = A0;
const int ledPin = 9;

// 宣告變數來儲存上一次印出資料的時間
unsigned long previousMillis = 0; 
// 設定更新間隔為 1000 毫秒
const long interval = 1000; 

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int sensorValue = analogRead(potPin);
  int pwmValue = sensorValue / 4; 
  analogWrite(ledPin, pwmValue);
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.print("Data is ");
    Serial.println(sensorValue);
  }
}
