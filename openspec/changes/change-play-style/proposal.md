## Why

為了提升遊戲策略深度與關卡儀式感，我們將調整遊戲的卡牌獲取與關卡銜接機制。在第一、二大關的前兩回合，玩家將直接獲得整副卡牌（各一張）進行戰鬥；而在面對魔王關卡（第 3 回合）之前，系統會以動態隨機抽取動畫向玩家贈送 2 張隨機卡牌，並在進入 Boss 戰前播放震撼的「WARNING」警告閃爍動畫，增加戰鬥的緊張感。

## What Changes

1. **初始牌組與手牌機制（Round 1 & 2）**：
   - 在每個大關的 Round 1 與 Round 2，玩家的初始牌組固定包含卡牌庫中每種卡牌各 1 張（目前共 7 種不同卡牌，即牌組總數為 7）。
   - 戰鬥開始時，玩家直接將此 7 張卡牌全部抽入手牌。
2. **Boss 關卡前隨機卡牌抽取與動畫（Before Round 3）**：
   - 當玩家擊敗 Round 2 怪物後，在進入 Round 3 (Boss 戰) 之前，進入「卡牌抽取階段」。
   - 系統從所有卡牌池中隨機抽取 2 張卡牌加入玩家的永久牌組。
   - 卡牌抽取過程包含動畫演出（在控制台滾動顯示卡牌名稱、減速並鎖定最終抽到的卡牌）。
3. **Boss 戰前警告動畫（Round 3 Start）**：
   - 在進入 Boss 戰鬥前，控制台全螢幕播放「⚠️ WARNING! BOSS APPROACHING! ⚠️」字樣交替閃爍的警告動畫。

## Capabilities

### New Capabilities

無。

### Modified Capabilities

- `battle-and-card-core`:
  - 調整戰鬥初始化的牌組生成邏輯：Round 1 & 2 初始牌組固定為每種卡牌各一張，起始手牌為整副牌組。
  - 支援卡牌庫動態新增卡牌（透過隨機抽取加入）。
- `game-flow-and-stages`:
  - 在 Round 2 勝利與 Round 3 開始之間，插入卡牌抽取（Draft）階段與 Boss 警告階段。
- `ui-and-keyboard-control`:
  - 實作卡牌隨機滾動選取動畫。
  - 實作 Boss 戰前 WARNING 畫面交替閃爍動畫。

## Impact

- 影響 `Player` 的初始化與 `initStartingDeck` 方法。
- 影響 `Game::run` 中的關卡切換邏輯。
- 影響 `Battle` 的初始手牌繪製。
