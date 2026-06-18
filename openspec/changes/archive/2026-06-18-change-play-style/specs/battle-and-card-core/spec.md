## ADDED Requirements

### Requirement: Round 1 Starting Deck Fixed Size
在每一個大關的第 1 回合，玩家的初始牌組必須固定包含當前卡牌庫中每種不同卡牌各一張，且戰鬥開始時玩家將整副牌組抽入手牌；第 2 回合起，玩家將直接使用並繼承前一回合結束時的牌組。

#### Scenario: Round 1 Start Battle Hand
- **WHEN** 玩家在 Level 1-3 的 Round 1 進入戰鬥
- **THEN** 系統將玩家牌庫初始化為 7 張不同卡牌（每種卡牌各一張），且起始手牌為此 7 張卡牌全部

#### Scenario: Round 2 Keep Existing Deck
- **WHEN** 玩家在 Level 1-3 的 Round 2 進入戰鬥
- **THEN** 系統不重置玩家牌組，僅進行洗牌，並使起始手牌為 5 張卡牌
