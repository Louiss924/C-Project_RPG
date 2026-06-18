## Why

目前遊戲中玩家的攻擊手段過於單一，除了普通攻擊外，僅有「重擊」一張卡牌能造成直接傷害，缺乏針對不同怪物防守機制（如高護盾、多段防線）的應對卡牌。我們將新增 3 張各具特色且高策略價值的攻擊性卡牌，以提升卡牌戰鬥的深度與策略樂趣。

## What Changes

1. **新增 3 張新型攻擊卡牌**：
   - **「迅捷連擊」** (消耗: 2 SP)：對怪物連續造成 3 次 3 點傷害（多段攻擊，共計 9 點傷害）。
   - **「貫穿擊」** (消耗: 1 SP)：對怪物造成 6 點真實傷害（無視怪物護盾，直接扣減生命值）。
   - **「破甲重錘」** (消耗: 2 SP)：先清除怪物的全部護盾（將其設為 0），再對怪物造成 5 點傷害。
2. **擴充卡牌效果解析系統**：
   - 引入新的卡牌效果類型（`CardEffectType`），例如真實傷害、破盾攻擊、多段連擊。
3. **擴充初始牌組與抽卡池**：
   - 將這 3 張卡牌加入 1-1 的 `forceAllCards` 初始牌組中，使得初始牌組擴充為 10 張卡牌（首回合全部抽上手）。
   - 將這 3 張卡牌加入 Boss 戰前的隨機 Draft 卡牌池中。

## Capabilities

### New Capabilities
無。

### Modified Capabilities
- `battle-and-card-core`: 擴充 `CardEffectType` 效果類型，並在戰鬥卡牌使用判定中實現多段攻擊、真實傷害與清除護盾效果。
- `game-flow-and-stages`: 將這 3 張卡牌加入 1-1 初始牌組和 Boss 前的 Draft 卡牌池。

## Impact

- 影響 `include/Card.h` 中的 `CardEffectType` 列舉定義。
- 影響 `src/Battle.cpp` 的 `Battle::executePlayerAction`，以實作新增卡牌的效果運算。
- 影響 `src/Player.cpp` 的 `Player::initStartingDeck`，將 3 張新卡牌配置到牌組。
- 影響 `src/Game.cpp` 的 `Game::draftCardsPhase` 抽卡池，以加入 3 張新卡牌。
