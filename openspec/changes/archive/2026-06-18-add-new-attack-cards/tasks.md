## 1. 擴充 CardEffectType 列舉定義

- [x] 1.1 修改 `include/Card.h` 中的 `CardEffectType` 列舉，新增 `TRUE_DAMAGE`、`BREAK_ARMOR_DAMAGE` 與 `MULTI_DAMAGE`。

## 2. 實作新型卡牌效果的戰鬥邏輯

- [x] 2.1 修改 `src/Battle.cpp` 的 `Battle::executePlayerAction`：實作 `TRUE_DAMAGE` (貫穿擊，真實傷害無視護盾)。
- [x] 2.2 修改 `src/Battle.cpp` 的 `Battle::executePlayerAction`：實作 `BREAK_ARMOR_DAMAGE` (破甲重錘，清除怪物護盾後造成傷害)。
- [x] 2.3 修改 `src/Battle.cpp` 的 `Battle::executePlayerAction`：實作 `MULTI_DAMAGE` (迅捷連擊，連續造成 3 次傷害)。

## 3. 配置新卡牌至玩家起始牌組與 Draft 卡牌池

- [x] 3.1 修改 `src/Player.cpp` 的 `Player::initStartingDeck`：在牌組中新增「迅捷連擊」、「貫穿擊」、「破甲重錘」三張卡牌的定義。
- [x] 3.2 修改 `src/Game.cpp` 的 `Game::draftCardsPhase` 抽卡池：加入此三張新卡牌的定義。
- [x] 3.3 執行編譯與手動測試，確保新卡牌能正確發牌、抽牌並打出其對應效果。
