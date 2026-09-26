# Lab 2 課題報告：馬達驅動、感測器與中斷

- **學生姓名**：[黃威霖]
- **學生學號**：[113511052]
- **完成日期**：2026-09-24

---

## Advanced Task 2-3: External Interrupt vs Polling
### 1. 實驗目標
- 比較「外部中斷 (Interrupt)」與「輪詢 (Polling)」兩種偵測輸入機制的差異。
- 模擬系統繁忙 (Blocking) 時，兩種機制的反應表現。

### 2. 設備與元件
- USB Type-B 傳輸線 x 1
- 個人電腦（已安裝 Arduino IDE）x 1
- Arduino Uno 開發板 x 1
- 按鍵開關 x 2 (Button A, Button B)
- LED x 2 (LED A, LED B)、限流電阻 x 2
- 下拉電阻 x 2
- 麵包板 x 1
- 杜邦線 若干

### 3. 操作說明與成果
1. **電路與邏輯**：
   - **Set A**：延續 Task 2-3，利用**外部中斷**偵測 Button A，控制 LED A。
   - **Set B**：在 `loop()` 內利用**輪詢**方式 (`digitalRead` 與邊緣觸發偵測) 讀取 Button B 控制 LED B。
   - **Blocking 模擬**：在 `loop()` 結尾加入 `delay(2000)` 模擬系統繁忙。
2. **觀察結果**：
   - 系統繁忙期間按下 Button B (Polling)，程式卡在 delay 無法即時讀取按鍵，LED B 不會有反應或反應遲鈍。
   - 系統繁忙期間按下 Button A (Interrupt)，由於硬體層級的強行介入，LED A 能即時切換狀態，不受 delay 影響。
3. **實驗成果**：實驗驗證了中斷機制在響應即時性上的優勢，特別適合用於緊急停止或高優先級訊號捕捉的機電系統開發。