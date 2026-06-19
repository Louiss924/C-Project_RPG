# Game Save System Spec

## Purpose
實作 C++ 檔案讀寫（File I/O），處理遊戲進度的持久化自動儲存（Save）與載入（Load）機制。

## Requirements

### Requirement: Auto Save Progress
系統必須支援自動存檔功能。在每一回合戰鬥獲勝、卡牌增抽完成，或是進入新關卡時，自動將遊戲進度持久化寫入本地檔案 `save.dat`。

#### Scenario: Save After Battle Victory
- **WHEN** 玩家戰勝非 Round 3 Boss 關卡並確認進入下一階段
- **THEN** 系統必須將目前的 Level、Round、玩家 HP、Max HP 以及完整的牌組列表寫入 `save.dat` 中

#### Scenario: Save After Card Drafting
- **WHEN** 玩家完成卡牌增抽階段且增抽卡牌已加入牌組
- **THEN** 系統必須自動更新 `save.dat` 存檔

### Requirement: Restore Save State
系統必須能完整解析 `save.dat` 的內容，還原玩家的當前生命值、最大生命值上限、當前 Level、Round 以及重建其牌組中的所有卡牌。

#### Scenario: Load Save File Successfully
- **WHEN** 玩家在主選單選擇「繼續冒險」且 `save.dat` 格式正確
- **THEN** 系統必須讀取檔案、重置玩家數值與牌組卡牌、並將遊戲流程跳轉至對應關卡起點
