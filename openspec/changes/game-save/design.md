## Context

為滿足 C++ 的檔案讀寫需求，我們需要在遊戲中引入存讀檔功能。為此需要定義遊戲進度的序列化儲存格式，以及檔案讀寫異常時的防錯處理。

## Goals / Non-Goals

**Goals:**
- 定義存檔格式並於 `Game` 中實作 `saveGame()` 和 `loadGame()`。
- 自動在戰鬥勝利與 Draft 結束後執行自動存檔（Auto-save）。
- 根據本地是否存在存檔 `save.dat`，動態在主選單渲染並分流至「繼續冒險」選項。
- 實作反序列化建立卡牌的對照邏輯。

**Non-Goals:**
- 不存檔當前進行中的戰鬥狀態（只在關卡結算/過場時存檔，中途戰鬥中關閉仍需重打該 Round）。
- 不對存檔檔案進行加密（採用人類可讀的純文字格式即可，符合學術/展示專案直觀原則）。

## Decisions

### 1. 存檔檔案格式設計 (`save.dat`)
採用純文字檔 (Plain Text File) 格式，定義兩行：
- **第一行**：`currentLevel currentRound playerHp playerMaxHp` （以空格分隔的整數）。
- **第二行**：以逗號 `,` 分隔的牌組卡牌名稱。
例如：
```text
1 2 75 80
重擊,重擊,防禦,治療術,反擊姿態,迅捷連擊
```

### 2. 卡牌重建對照表 (Deserialization Map)
在 `Player.h` 與 `Player.cpp` 或 `Game` 輔助程式中，新增一個輔助函式 `Card createCardByName(const std::string& name)`。
根據讀取的字串名稱返回對應的卡牌物件：
- 「重擊」 ➡️ `Card("重擊", 1, CardEffectType::DAMAGE, 8, ...)`
- 其他卡牌依此類推。

### 3. `Game` 類別方法與主選單動態路由
- 新增 `bool hasSaveFile()`：使用 `std::ifstream` 測試開啟 `save.dat`，回傳檔案是否存在。
- 修改 `displayMainMenu()`：
  - 若 `hasSaveFile()` 爲 `true`，選單選項有 4 個：`0: 開始冒險`、`1: 繼續冒險`、`2: 遊戲說明`、`3: 離開遊戲`。
  - 若爲 `false`，則維持原本的 3 個選項。
  - 配合選項個數（3 或 4），調整游標上下移動的 Wrap 模除邊界（`% 3` 或 `% 4`）。

### 4. 存檔時機 (Triggers)
在 `Game::run()` 的主循環中，在以下情況下觸發 `saveGame()`：
- 每一小關戰鬥勝利後。
- 完成 Boss 戰前的卡牌 Draft 並確認後。
- 擊敗關卡 Boss 且關卡切換（Level 推進）後。

## Risks / Trade-offs

- **存檔檔案毀損或手動修改錯誤**：如果檔案內容毀損或被使用者惡意亂改，讀檔可能崩潰。
  - *Mitigation*: 在 `loadGame()` 中進行嚴格格式驗證。使用 `std::stringstream` 逐一提取數值。若讀取數值失敗、小於等於 0、或提取到未定義的卡牌名稱，則直接報錯「存檔損毀」，清空損毀的檔案並引導玩家重開新遊戲。
