# Battle and Card Core Spec

## Purpose
管理回合制戰鬥邏輯、抽牌與手牌管理、SP 能量計算、卡牌效果（傷害、回復、護盾、反擊、最大生命提升、眩暈）與普通攻擊（SP 回復）、以及怪物的行動意圖預告。
## Requirements
### Requirement: Player Base Actions and SP Management
玩家在每回合的戰鬥階段中，必須能選擇執行「普通攻擊」或「使用手牌（卡牌技能）」。普通攻擊不消耗 SP 且會使 SP 回復 1 點；使用手牌必須消耗該卡牌指定的 SP，若 SP 不足則不允許出牌。

#### Scenario: Normal Attack SP Recovery
- **WHEN** 玩家選擇普通攻擊並確認執行
- **THEN** 玩家的 SP 必須增加 1 點（不超過最大能量上限），並對怪物造成基礎攻擊傷害

#### Scenario: Card Usage SP Check
- **WHEN** 玩家選擇消耗 X 點 SP 的手牌並確認出牌，且當前 SP >= X
- **THEN** 系統必須扣除玩家 X 點 SP，並執行該卡牌的對應技能效果

#### Scenario: Insufficient SP Block
- **WHEN** 玩家選擇消耗 X 點 SP 的手牌並確認出牌，且當前 SP < X
- **THEN** 系統必須拒絕執行出牌，並在畫面上顯示能量不足的警示，維持當前出牌選擇狀態

### Requirement: Card Effects and Random Draw
系統必須支援手牌隨機抽取機制，且卡牌效果必須涵蓋：回復血量、造成攻擊、防禦（護盾）、反擊部分傷害、提高最大生命值上限（以防禦怪物扣除生命值百分比之招式）、電暈（使怪物暫停動作一回合）。

#### Scenario: Play Heal Card
- **WHEN** 玩家成功打出「回復」卡牌
- **THEN** 玩家 HP 必須增加指定數值，但不得超過當前的最大 HP 上限

#### Scenario: Play Defend Card
- **WHEN** 玩家成功打出「防禦」卡牌
- **THEN** 玩家獲得與卡牌防禦值等額的護盾，該護盾必須能全額抵免怪物在下一回合造成的傷害（超出護盾的傷害則扣除 HP）

#### Scenario: Play Counter Card
- **WHEN** 玩家成功打出「反擊」卡牌
- **THEN** 系統必須為玩家附加反擊狀態，在怪物下一回合攻擊時，將所受傷害的特定比例（如 50%）反彈給怪物

#### Scenario: Play Max HP Upgrade Card
- **WHEN** 玩家成功打出「提升最大生命」卡牌
- **THEN** 玩家的最大 HP 上限與當前 HP 必須同時增加指定數值

#### Scenario: Play Stun Card
- **WHEN** 玩家成功打出「電暈」卡牌
- **THEN** 系統必須為怪物附加眩暈狀態，使怪物在下一回合無法採取 any 行動（跳過怪物回合）

### Requirement: Monster Intent Preview
在玩家決定該回合的出牌或攻擊動作前，畫面最上方必須清楚預告怪物的下一回合意圖（招式名稱與預計造成的傷害），以利玩家進行防禦或反擊的策略決策。

#### Scenario: Show Enemy Intent Before Action
- **WHEN** 進入新的玩家回合，且玩家尚未進行 any 輸入
- **THEN** 系統必須在畫面上方居中或明顯位置，繪製並顯示「怪物下回合招式：[招式名稱]，預估傷害：[數值]」

### Requirement: Round 1 Starting Deck Fixed Size
在每一個大關的第 1 回合，玩家的初始牌組必須固定包含當前卡牌庫中每種不同卡牌各一張，且戰鬥開始時玩家將整副牌組抽入手牌；第 2 回合起，玩家將直接使用並繼承前一回合結束時的牌組。

#### Scenario: Round 1 Start Battle Hand
- **WHEN** 玩家在 Level 1-3 的 Round 1 進入戰鬥
- **THEN** 系統將玩家牌庫初始化為 7 張不同卡牌（每種卡牌各一張），且起始手牌為此 7 張卡牌全部

#### Scenario: Round 2 Keep Existing Deck
- **WHEN** 玩家在 Level 1-3 的 Round 2 進入戰鬥
- **THEN** 系統不重置玩家牌組，僅進行洗牌，並使起始手牌為 5 張卡牌

