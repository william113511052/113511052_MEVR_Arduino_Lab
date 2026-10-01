**`Lab3/Task3-2/report.md`（完整示範報告）**

```markdown
# 課題報告：Task 0-1 Hello World 序列埠輸出

- **學生姓名**：[請填寫姓名]
- **學生學號**：[請填寫學號]
- **完成日期**：2026-XX-XX

---

### 1. 實驗目標(可參考課程投影片寫法)
- 驗證 Arduino IDE 開發環境編譯與燒錄功能正常。
- 掌握 `Serial.begin()` 與 `Serial.println()` 之使用方式。
- 學習透過 Arduino IDE「序列埠監控器（Serial Monitor）」接收開發板訊息。

### 2. 設備與元件
- Arduino Uno 開發板 x 1
- USB Type-B 傳輸線 x 1
- 個人電腦（已安裝 Arduino IDE）x 1

### 3. 操作說明與成果
1. **燒錄程式**：使用 USB 線連接 Arduino Uno 至電腦，開啟 `Task0-1.ino` 並點擊「上傳」。
2. **開啟監控器**：開啟 Arduino IDE 的 Serial Monitor，將鮑率（Baud rate）設為 **9600 baud**。
3. **實驗成果**：序列埠監控器成功每秒印出一次 `Hello World from Arduino!` 訊息。
4. **操作影片**：請參閱同目錄下 `video/Task0-1.mp4` 之實際操作畫面。


# Lab 3 課題報告：從 Arduino 走向電腦端程式

- **學生姓名**：[黃威霖]
- **學生學號**：[113511052]
- **完成日期**：2026-10-01

---

## Advanced Task 3-3: LED Control with Wireless Communication
### 1. 實驗目標
- 學習配置與使用 HC-05 藍牙模組進行無線序列埠通訊。
- 注意不同硬體間的邏輯準位差異（Arduino 為 5V、HC-05 為 3.3V），並將前一個任務的有線控制改為藍牙無線控制。

### 2. 設備與元件
- Arduino Uno 開發板 x 1
- USB Type-B 傳輸線 x 1
- HC-05 藍牙模組 x 1
- LED x 1、限流電阻 x 1、分壓電阻（供 HC-05 RXD 降壓使用）
- 麵包板與杜邦線 若干
- 具備藍牙功能之個人電腦 x 1

### 3. 操作說明與成果
1. **硬體接線與設定**：將 HC-05 模組連接至 Arduino（建議於 HC-05 的 RXD 腳位加上分壓電阻，將 Arduino 5V 訊號降至 3.3V），並確認 HC-05 的工作鮑率設定。
2. **藍牙配對與程式調整**：透過電腦藍牙設定搜尋並配對 `HC-05`，確認配對後產生的虛擬序列埠（Virtual COM Port），並據此修改 Arduino 韌體（如使用 `SoftwareSerial` 或對應序列埠）與 C# 程式中的連接埠設定。
3. **實驗成果**：成功在不依賴 USB 傳輸線通訊的情況下，由電腦端 C# 介面透過藍牙無線發送指令給 HC-05，即時控制 Arduino 上的 LED 亮滅。
4. **操作影片**：請參閱 GitHub `Lab 3` 資料夾下之程式碼與展示影片。