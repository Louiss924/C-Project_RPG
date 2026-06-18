## ADDED Requirements

### Requirement: Card Drafting and Boss Warning Animation
在卡牌抽取階段以及 Boss 戰開始前，系統必須播放對應的動畫：包含滾動的隨機卡牌抽取動畫，以及 Boss 回合開始前的 Warning 閃爍警告動畫。

#### Scenario: Card Drafting Animation
- **WHEN** 卡牌抽取階段啟動
- **THEN** 控制台畫面必須動態滾動卡牌名稱，並以減速停格效果顯示最終獲得的卡牌

#### Scenario: Boss Warning Flashing Animation
- **WHEN** 玩家確認進入第 3 回合 Boss 戰
- **THEN** 畫面必須在進入戰鬥主畫面之前，播放交替閃爍的 WARNING 警告文字與警告框
