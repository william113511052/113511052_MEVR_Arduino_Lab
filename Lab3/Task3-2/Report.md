# Lab 3 課題報告：從 Arduino 走向電腦端程式

- **學生姓名**：[黃威霖]
- **學生學號**：[113511052]
- **完成日期**：2026-10-01

---

## Advanced Task 3-2: LED Control with Serial Communication
### 1. 實驗目標
- 學習使用 Visual Studio 開發電腦端 C# 圖形化使用者介面（GUI）或主控台應用程式。
- 實作電腦端程式（C# Host App）與 Arduino 韌體之間的雙向/單向 UART 序列埠通訊（Serial Communication）。

### 2. 設備與元件
- Arduino Uno 開發板 x 1
- USB Type-B 傳輸線 x 1
- LED x 1、限流電阻 x 1
- 麵包板與杜邦線 若干
- 個人電腦（已安裝 Visual Studio 與 Arduino IDE）x 1

### 3. 操作說明與成果
1. **Arduino 韌體設計**：於 `setup()` 初始化 `Serial.begin(9600)`，並在 `loop()` 中持續監聽序列埠傳入的字串指令，根據收到的資料控制 LED 亮起（On）或熄滅（Off）。
2. **C# 電腦端程式設計**：使用 Visual Studio 建立視窗介面（包含 On 與 Off 按鈕），配置對應的 COM Port 與鮑率（9600 baud，並確保 Arduino IDE 的 Serial Monitor 已關閉以避免序列埠佔用），點擊按鈕時透過序列埠發送控制訊號。
3. **實驗成果**：成功透過電腦螢幕上的 C# GUI 介面點擊「On」與「Off」按鈕，即時控制麵包板上的 LED 亮滅。並偵測按鈕是否按下來改變 GUI 上顯示的文字。
4. **操作影片**：請參閱 GitHub `Lab 3` 資料夾下之程式碼與展示影片。
