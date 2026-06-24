## Context

目前 `Game::run()` 在處理主選單「開始冒險」選項後，會直接將 `currentLevel` 設為 1，`currentRound` 設為 1，並跳出選單迴圈進入戰鬥關卡。

## Goals / Non-Goals

**Goals:**
- 在主選單點選「開始冒險」後，切換至一個新的「關卡選擇」畫面。
- 支援使用鍵盤（方向鍵與 Enter 鍵）選擇要開始的關卡（Level 1 或 Level 2）。
- 根據玩家的選擇正確更新 `currentLevel` 和 `currentRound`。

**Non-Goals:**
- 不支援直接選擇特定的回合（Round），僅能從大關的第一回合（Round 1）開始。
- 不改變「繼續冒險（讀取存檔）」的邏輯與流程。

## Decisions

### 1. 於 `Game` 類別中新增成員方法 `selectStartingLevelPhase()`
- **設計**：在 `Game` 類別中新增一個私有成員方法 `void selectStartingLevelPhase();` 專門用於處理關卡選擇流程。
- **渲染與輸入邏輯**：
  - 畫面頂部顯示標題。
  - 使用一個本機變數 `levelCursor`（0 代表 Level 1，1 代表 Level 2）。
  - 使用與主選單及卡牌 UI 相同的鍵盤事件監聽器（`_getch()`），攔截方向鍵（↑/↓）更新 `levelCursor`，並用 Enter 鍵確認。
  - 確認後，將 `currentLevel = levelCursor + 1;` 且 `currentRound = 1;`。

### 2. 整合至主選單「開始冒險」事件
- 在 `Game::run()` 的主選單事件處理中：
  ```cpp
  if (menuCursor == 0) {
      // 開始冒險
      selectStartingLevelPhase();
      inMenu = false;
      ...
  }
  ```

## Risks / Trade-offs

- **[風險]**：新增的關卡選擇方法中的 `system("cls")` 和 `_getch()` 與現有控制台輸入可能產生衝突或搶按。
  - *緩解措施*：在進入關卡選擇選單前與完成後，確實呼叫 `while (_kbhit()) { _getch(); }` 清空鍵盤輸入緩衝區。
