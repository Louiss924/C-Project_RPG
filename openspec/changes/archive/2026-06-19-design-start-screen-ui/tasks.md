## 1. 聲明主選單相關方法與狀態變數

- [x] 1.1 在 `include/Game.h` 中，為 `Game` 類別新增 `displayMainMenu()` 與 `displayInstructions()` 成員方法。
- [x] 1.2 在 `include/Game.h` 的 `Game` 類別私有成員中，新增用於記錄主選單高亮選項游標的 `int menuCursor`。

## 2. 實作主畫面選單渲染與互動邏輯

- [x] 2.1 在 `src/Game.cpp` 中實作 `Game::displayMainMenu()`：用 `cls` 清除畫面，繪製帶有 ASCII Art 遊戲名稱的標題，以 `>` 標註高亮選項，並以 `_getch()` 讀取 ↑/↓ 鍵與 Enter 鍵更新 `menuCursor` 或返回選中結果。
- [x] 2.2 在 `src/Game.cpp` 中實作 `Game::displayInstructions()`：以排版清晰的文字展現遊戲卡牌三大分類（攻擊型、防禦型、輔助型）與操作規則，並等待按任意鍵返回。

## 3. 調整遊戲生命週期啟動點與輸入快取清除

- [x] 3.1 在 `src/Game.cpp` 的 `Game::run()` 中，於進入關卡迴圈前引進主選單迴圈。根據選擇分別路由至「開始冒險」（跳出迴圈）、「遊戲說明」（執行說明頁並返回）、「離開遊戲」（調用 `exit(0)`）。
- [x] 3.2 在確認進入「開始冒險」並跳出選單迴圈後，呼叫鍵盤快取清除迴圈（以 `_kbhit()` 與 `_getch()` 清除），防止主選單按 Enter 的指令延續至關卡 1-1 的對話。
