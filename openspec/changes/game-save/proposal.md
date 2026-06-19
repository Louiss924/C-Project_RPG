## Why

目前遊戲沒有存檔與讀檔機制，玩家中途關閉程式會導致所有進度（包含玩家剩餘血量、生命上限、已取得的手牌及當前關卡數）消失。本變更將引入 C++ 檔案讀寫（File I/O），實作自動存檔與讀取檔案，以滿足功能完整性並符合檔案讀寫的實作規範。

## What Changes

1. **實作自動存檔功能 (Auto-save)**：
   - 當玩家在戰鬥取得勝利、完成卡牌增抽（Draft），或進入下一關時，系統會將當前進度自動寫入外部文字檔案（如 `save.dat`）。
   - 存檔內容將包含：當前關卡（Level）、當前回合（Round）、玩家當前生命值（HP）、最大生命值上限（Max HP），以及當前牌組中所有卡牌的完整名稱與配置。
2. **主選單新增「繼續冒險」選項**：
   - 主選單增加一個選項「繼續冒險」：
     - 若檢測到有存檔檔案，此選項顯示為可選取狀態，點選後會讀取 `save.dat` 還原玩家狀態及牌組，直接跳轉至存檔的關卡。
     - 若無存檔檔案，主選單預設只顯示「開始冒險」、「遊戲說明」、「離開遊戲」。
3. **卡牌序列化與反序列化 (Serialization & Deserialization)**：
   - 實作卡牌到檔案文字的儲存格式，以及從檔案讀取卡牌名稱後自動重新實例化（Re-instantiation）為牌組的映射邏輯。

## Capabilities

### New Capabilities

- `game-save-system`: 實作檔案讀寫功能，以 `<fstream>` 處理存檔的寫入與讀取，並進行卡牌資料與玩家屬性的序列化與反序列化。

### Modified Capabilities

- `game-flow-and-stages`: 主選單流程中整合讀檔加載點，關卡推進和戰鬥結算時加入自動存檔觸發點。

## Impact

- 影響 `include/Game.h` 和 `src/Game.cpp`：
  - 新增 `saveGame()`、`loadGame()` 與 `hasSaveFile()` 方法。
  - 修改 `displayMainMenu()` 和 `run()` 的分流邏輯。
- 引入 `<fstream>` 和 `<sstream>` 依賴，無其他外部函式庫依賴。
