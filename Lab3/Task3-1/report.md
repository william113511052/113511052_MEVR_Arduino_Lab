# Lab 3 課題報告：從 Arduino 走向電腦端程式

- **學生姓名**：[黃威霖]
- **學生學號**：[113511052]
- **完成日期**：2026-10-01

---

## Advanced Task 3-1: Timer Interrupt vs Blocking Delay
### 1. 實驗目標
- 比較「計時器中斷（Timer Interrupt）」與「阻塞式延遲（Blocking Delay）」在系統即時響應上的差異。
- 評估兩種機制在機器人與機電整合系統開發中的適用性。

### 2. 設備與元件
- USB Type-B 傳輸線 x 1
- 個人電腦（已安裝 Arduino IDE）x 1
- Arduino Uno 開發板 x 1
- 按鍵開關 x 2（Button A、Button B）
- LED x 2（LED A、LED B）、限流電阻 x 2、下拉電阻 x 2
- 麵包板與杜邦線 若干

### 3. 操作說明與成果
1. **電路與控制邏輯**：
   - **Button A + LED A（Timer Interrupt）**：利用 `TimerOne` 函式庫設定每 50ms（50,000 微秒）觸發一次定時中斷，並於 ISR 內部讀取 Button A 狀態以更新 LED A。
   - **Button B + LED B（Blocking Delay）**：在 `void loop()` 主迴圈內讀取 Button B 狀態並更新 LED B，且於 `loop()` 結尾加入 `delay(1000)`（1 秒延遲）模擬系統繁忙阻塞。
2. **實驗成果**：
   - 當按下 Button B 時，由於主迴圈受到 1 秒 `delay()` 阻塞，LED B 反應會有明顯延遲或漏接按鍵訊號。
   - 當按下 Button A 時，由於計時器中斷每 50ms 固定獨立觸發 ISR，不受主迴圈 `delay()` 影響，LED A 能即時點亮與熄滅。
3. **操作影片**：請參閱 GitHub `Lab 3` 資料夾下之程式碼與展示影片。
