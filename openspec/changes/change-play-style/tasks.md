## 1. 調整玩家初始化與牌組邏輯

- [x] 1.1 修改 `Player::initStartingDeck` 方法。支援參數 `bool forceAllCards`，當為 `true` 時牌組精確填充目前所有 7 種卡牌各 1 張。
- [x] 1.2 修改 `Battle::start` 方法。當為 Round 1 或 Round 2 時，初始抽牌數量直接使用牌庫總張數（7張），使玩家首回合直接將整副牌組抽入手牌。

## 2. 實作魔王關前隨機卡牌抽取與動畫

- [x] 2.1 於 `Game` 類別中實作 `draftCardsPhase` 方法，定義隨機抽取 2 張卡牌邏輯，將其永久加入玩家的牌組。
- [x] 2.2 於 `Game` 類別實作滾動停格選牌動畫，使用 `Sleep()` 達成速度遞減的動態選卡效果。
- [x] 2.3 於 `Game::run` 中擊敗 Round 2 怪物後、進入 Round 3 前，插入該卡牌抽取階段。

## 3. 實作 Boss 戰前 WARNING 閃爍警告動畫

- [x] 3.1 於 `Game` 類別中實作 `playBossWarningAnimation` 方法，繪製「⚠️ WARNING! BOSS APPROACHING! ⚠️」警示區塊。
- [x] 3.2 實作利用 `Sleep(200)` 交替閃爍文字與警示邊框的清屏重繪動畫，閃爍 5 次。
- [x] 3.3 於 `Game::run` 進入 Round 3 (Boss 戰) 前插入此 WARNING 警告閃爍動畫。
- [x] 3.4 完整編譯測試，驗證從 Round 1 到 Round 3 的初始手牌、卡牌抽取動畫及 WARNING 警示演出之邏輯與視覺流暢度。
