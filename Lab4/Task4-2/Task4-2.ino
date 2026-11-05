#include <Servo.h>

// ================= 腳位 =================
const uint8_t TRIG_PIN  = 10;
const uint8_t ECHO_PIN  = 11;
const uint8_t SERVO_PIN = 9;

// ================= 機構參數 =================
float baseAngle = 120.0;
const float TILT_LIMIT = 17.0;
const int   DIR = +1;
const float MIN_CM = 2.0;
const float MAX_CM = 25.0;

// ================= PID 參數 =================
float setpoint = 10.5;
float Kp = 2.0;
float Ki = 0.7;
float Kd = 4.5;
const float I_LIMIT  = 5.0;
const float I_BAND   = 3.0;
const float D_ALPHA  = 0.5;

// ================= 取樣 / 濾波參數 =================
const unsigned long SAMPLE_MS = 50;
const uint8_t N_AVG = 4;
const float JUMP_CM = 3.0;
const uint8_t JUMP_MAX = 3;

Servo servo;

// ================= 全域狀態變數 =================
// 濾波器狀態
float lastValid = 0;
uint8_t jumpCount = 0;
float hist[3];
float avgBuf[N_AVG];
uint8_t avgIdx = 0;
float avgSum = 0;

// PID 狀態
float integral = 0;
float prevPos  = 0;
float dFilt    = 0;
unsigned long lastMs = 0;

// 系統共享狀態 (供 Telemetry 使用)
float currentPos = 0;
float currentTilt = 0;

// 序列指令狀態
char cmdBuf[16];
uint8_t cmdLen = 0;

// 印資料狀態
unsigned long printMs = 200;
unsigned long lastPrintMs = 0;
unsigned long holdStart = 0;
const unsigned long HOLD_MS = 3000;


// ------------------------------------------------------------
// 底層功能：感測與致動
// ------------------------------------------------------------
float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long us = pulseIn(ECHO_PIN, HIGH, 6000UL);
  if (us == 0) return -1;
  return us / 58.0;
}

float median3(float a, float b, float c) {
  return max(min(a, b), min(max(a, b), c));
}

float filterDistance(float raw) {
  if (raw < MIN_CM || raw > MAX_CM) {
    raw = lastValid;
  } else if (fabs(raw - lastValid) > JUMP_CM && jumpCount < JUMP_MAX) {
    raw = lastValid;
    jumpCount++;
  } else {
    jumpCount = 0;
  }
  lastValid = raw;

  hist[0] = hist[1];
  hist[1] = hist[2];
  hist[2] = raw;
  float m = median3(hist[0], hist[1], hist[2]);

  avgSum -= avgBuf[avgIdx];
  avgBuf[avgIdx] = m;
  avgSum += m;
  avgIdx = (avgIdx + 1) % N_AVG;
  return avgSum / N_AVG;
}

float computePID(float pos, float dt) {
  float error = setpoint - pos;
  float P = Kp * error;

  if (fabs(error) < I_BAND) integral += error * dt;
  if (Ki > 0) integral = constrain(integral, -I_LIMIT / Ki, I_LIMIT / Ki);
  float I = Ki * integral;

  float vel = (pos - prevPos) / dt;
  prevPos = pos;
  dFilt += D_ALPHA * (vel - dFilt);
  float D = -Kd * dFilt;

  return P + I + D;
}

void writeServo(float deg) {
  int us = 544 + (int)(deg / 180.0 * (2400 - 544));
  servo.writeMicroseconds(us);
}


// ------------------------------------------------------------
// 任務 1：序列指令處理
// ------------------------------------------------------------
void printParams() {
  Serial.print(F("# Kp=")); Serial.print(Kp);
  Serial.print(F(" Ki="));  Serial.print(Ki);
  Serial.print(F(" Kd="));  Serial.print(Kd);
  Serial.print(F(" set=")); Serial.print(setpoint);
  Serial.print(F(" base="));Serial.print(baseAngle);
  Serial.print(F(" print="));Serial.println(printMs);
  holdStart = millis();
}

void runCommand(char *s) {
  float v = atof(s + 1);
  switch (s[0]) {
    case 'p': Kp = v; break;
    case 'i': Ki = v; integral = 0; break;
    case 'd': Kd = v; break;
    case 's': setpoint = v; break;
    case 'b': baseAngle = v; break;
    case 't': printMs = (v < 0) ? 0 : (unsigned long)v; break;
    case 'r': integral = 0; break;
    case '?': break;
    default:
      Serial.println(F("# 指令: p i d s b t r ?"));
      holdStart = millis();
      return;
  }
  printParams();
}

void taskSerial() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (cmdLen > 0) {
        cmdBuf[cmdLen] = '\0';
        runCommand(cmdBuf);
        cmdLen = 0;
      }
    } else if (cmdLen < sizeof(cmdBuf) - 1) {
      cmdBuf[cmdLen++] = c;
    }
  }
}


// ------------------------------------------------------------
// 任務 2：PID 控制核心
// ------------------------------------------------------------
void taskControl(unsigned long now) {
  if (now - lastMs < SAMPLE_MS) return;
  float dt = (now - lastMs) / 1000.0;
  lastMs = now;

  // 1. 感測與濾波
  currentPos = filterDistance(readDistanceCm());
  
  // 2. 運算 PID
  currentTilt = constrain(computePID(currentPos, dt), -TILT_LIMIT, TILT_LIMIT);
  
  // 3. 輸出至致動器
  writeServo(baseAngle + DIR * currentTilt);
}


// ------------------------------------------------------------
// 任務 3：數據回報 (Telemetry)
// ------------------------------------------------------------
void taskTelemetry(unsigned long now) {
  bool holding = (now - holdStart < HOLD_MS);
  if (printMs > 0 && !holding && (now - lastPrintMs >= printMs)) {
    lastPrintMs = now;
    Serial.print(F("target:")); Serial.print(setpoint);
    Serial.print(F(",pos:"));   Serial.print(currentPos);
    Serial.print(F(",tilt:"));  Serial.println(currentTilt);
  }
}


// ------------------------------------------------------------
// 主程式
// ------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  servo.attach(SERVO_PIN);
  writeServo(baseAngle);
  delay(1000);

  // 初始讀值填滿濾波器
  float d = readDistanceCm();
  if (d < MIN_CM || d > MAX_CM) d = setpoint;
  lastValid = d;
  for (uint8_t i = 0; i < 3; i++) hist[i] = d;
  for (uint8_t i = 0; i < N_AVG; i++) avgBuf[i] = d;
  avgSum = d * N_AVG;
  prevPos = d;

  printParams();
  lastMs = millis();
}

void loop() {
  unsigned long now = millis();
  
  taskSerial();           // 任務 1：監聽與解析使用者指令
  taskControl(now);       // 任務 2：執行 50ms 週期的感測與 PID 控制
  taskTelemetry(now);     // 任務 3：處理 Serial Plotter 繪圖輸出
}
