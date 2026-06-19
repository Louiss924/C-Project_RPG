## Why

目前遊戲啟動時會直接進入關卡 1-1 的戰鬥，缺乏一個正式的遊戲啟動主選單。這對遊戲體驗不夠友善，玩家在開始遊戲前無法閱讀遊戲說明或選擇離開。

## What Changes

1. **新增遊戲啟動主畫面 (Start Screen / Title Menu)**：
   - 遊戲啟動時顯示美觀的 ASCII Art 遊戲標題與邊框。
   - 提供三個選項：「開始冒險」、「遊戲說明」、「離開遊戲」。
2. **鍵盤導覽選單操作**：
   - 延續戰鬥介面的一致性設計，使用方向鍵 (↑/↓) 來切換高亮選中的選項，並以 Enter 鍵確認選擇。
3. **主選單功能**：
   - **開始冒險**：進入原有的關卡 1-1 遊戲流程。
   - **遊戲說明**：在控制台中顯示詳細的卡牌說明、屬性規則與鍵盤操作指南，按下任意鍵後可返回主選單。
   - **離開遊戲**：優雅地結束程式。

## Capabilities

### New Capabilities

無。

### Modified Capabilities

- `game-flow-and-stages`: 修改遊戲初始化與啟動流程，在關卡開始前引入主選單階段。
- `ui-and-keyboard-control`: 實作主選單的控制台渲染，以及基於方向鍵與 Enter 鍵的鍵盤選單導覽。

## Impact

- 影響 `src/Game.cpp` 和 `include/Game.h`：需要新增 `displayMainMenu()` 及相關處理邏輯，修改 `run()` 進入點以先啟動主選單。
- 影響 `src/main.cpp`：配合 `Game` 類別的啟動流程調整。
