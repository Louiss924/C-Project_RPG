## ADDED Requirements

### Requirement: Round 1 and 2 Starting Deck Fixed Size
在每一個大關的第 1 與第 2 回合，玩家的初始牌組必須固定包含當前卡牌庫中每種不同卡牌各一張，且戰鬥開始時玩家將整副牌組抽入手牌。

#### Scenario: Round 1 and 2 Start Battle Hand
- **WHEN** 玩家在 Level 1-3 的 Round 1 或 Round 2 進入戰鬥
- **THEN** 系統將玩家牌庫初始化為 7 張不同卡牌（每種卡牌各一張），且起始手牌為此 7 張卡牌全部
