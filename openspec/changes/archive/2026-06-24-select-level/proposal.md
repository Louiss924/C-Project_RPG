## Why

目前遊戲在玩家點擊「開始冒險」時，一律強制從第一關第一回合（Level 1 Round 1）開始。為了提供更好的遊戲體驗，並方便測試，本變更將在點擊「開始冒險」後引入一個「關卡選擇選單」，讓玩家能自主選擇要直接挑戰 Level 1 還是 Level 2。

## What Changes

1. **新增關卡選擇選單**：在主選單點擊「開始冒險」後，不直接進入遊戲，而是切換至新設計的關卡選擇畫面，選項包括：
   * Level 1：哥布林關卡 (3回合)
   * Level 2：火山巨龍關卡 (3回合)
2. **初始化關卡設定**：根據玩家選擇的關卡，初始化 `currentLevel` 為 1 或 2，並將 `currentRound` 設為 1，隨後開始冒險。
3. **優化鍵盤操作**：關卡選擇選單應沿用現有的鍵盤方向鍵選擇與 Enter 鍵確認的操作邏輯。

## Capabilities

### New Capabilities

無。

### Modified Capabilities

- `battle-and-card-core`: 調整遊戲開始時的關卡進程與流程，加入玩家自主選擇起始關卡的行為規範。

## Impact

- 影響 `src/Game.cpp` 中主選單處理邏輯 `run()`，並新增關卡選擇選單繪製與處理邏輯（例如新方法 `selectStartingLevelPhase()`）。
- 影響 `include/Game.h` 新增相關方法的宣告。
