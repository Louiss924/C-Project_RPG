## 1. 宣告與實作關卡選擇方法

- [x] 1.1 在 `include/Game.h` 中新增私有方法 `void selectStartingLevelPhase();`。
- [x] 1.2 在 `src/Game.cpp` 中實作 `Game::selectStartingLevelPhase()`，利用方向鍵控制高亮選項、Enter 鍵確認選擇，並在確認後設定 `currentLevel` 為所選關卡、`currentRound` 為 1。

## 2. 整合至主選單邏輯

- [x] 2.1 修改 `src/Game.cpp` 中 `Game::run()` 的主選單「開始冒險」區塊（`menuCursor == 0`），使其呼叫 `selectStartingLevelPhase()` 而非直接進入 Level 1。
- [x] 2.2 在進入關卡選擇前與完成後，加上鍵盤快取清除機制，確保輸入流不會發生搶按的干擾。
