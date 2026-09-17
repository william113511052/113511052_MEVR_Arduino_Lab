# Lab 1 課題報告：讓LED、按鍵、可變電阻動起來

- **學生姓名**：[黃威霖]
- **學生學號**：[113511052]
- **完成日期**：2026-09-17

---

## Advanced Task 1-1: Analog Input
### 1. 實驗目標
- 學習使用可變電阻與 `analogRead()` 讀取類比輸入數值 (0~1023)。
- 將類比輸入數值映射為 PWM 訊號以調整 LED 亮度（數值越大越亮）。
- 學習使用 Serial Monitor 觀察即時感測數據。

### 2. 設備與元件
- PC
- USB TYPE-B 線
- Arduino Uno 開發板 x 1
- 可變電阻 x 1
- LED x 1、限流電阻 x 1
- 杜邦線 若干

### 3. 操作說明與成果
1. **電路連接**：可變電阻左右兩腳分別接 5V 與 GND，中間訊號腳接至 Analog In (如 A0~A5)。
2. **程式撰寫**：於 `setup()` 設定 `Serial.begin(9600)`。在 `loop()` 讀取可變電阻數值，將其轉換後以 `analogWrite()` 控制 LED，並每秒使用 `Serial.println()` 印出讀數。
3. **實驗成果**：旋轉可變電阻時 LED 亮度即時改變，同時 Serial Monitor 成功顯示 `Data is [數值]` 的格式輸出 (0~1023)。

