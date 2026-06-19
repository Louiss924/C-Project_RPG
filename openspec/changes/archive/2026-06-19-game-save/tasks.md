## 1. 實作卡牌反序列化對照邏輯

- [x] 1.1 在 `include/Player.h` 聲明 `createCardByName` 靜態或非成員輔助函式。
- [x] 1.2 在 `src/Player.cpp` 中實作 `createCardByName`，對應 10 種卡牌名稱並回傳各自的 `Card` 實例。

## 2. 實作遊戲存取檔讀寫核心功能

- [x] 2.1 在 `include/Game.h` 聲明 `saveGame()`、`loadGame()` 和 `hasSaveFile() const`。
- [x] 2.2 在 `src/Game.cpp` 中實作 `hasSaveFile()`，使用 `std::ifstream` 檢測本機目錄下的 `save.dat` 是否存在且可開啟。
- [x] 2.3 在 `src/Game.cpp` 中實作 `saveGame()`，將 `currentLevel`, `currentRound`, `hp`, `maxHp` 寫入第一行，並將玩家牌組的所有卡牌以逗號分隔寫入第二行。
- [x] 2.4 在 `src/Game.cpp` 中實作 `loadGame()`，讀取檔案並還原狀態與重建牌組；實作防錯邏輯（如解析失敗時視為存檔損毀並予以重置）。

## 3. 主選單與遊戲迴圈整合

- [x] 3.1 在 `src/Game.cpp` 中修改 `displayMainMenu()`，動態判斷若有存檔則插入選項「繼續冒險」，更新總選項個數至 4 個並調整游標 Wrap 邏輯與選項排版。
- [x] 3.2 在 `src/Game.cpp` 的 `Game::run()` 中，新增「繼續冒險」選單分支：呼叫 `loadGame()` 載入存檔、清除輸入快取、並開始執行還原後的關卡。
- [x] 3.3 在 `src/Game.cpp` 的關卡流程關鍵點（如一般小關勝利、Draft 增抽確認、大關 Boss 勝利切換）加入 `saveGame()` 的呼叫，以進行自動存檔。
