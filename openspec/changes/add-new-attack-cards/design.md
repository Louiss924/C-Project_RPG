## Context

目前戰鬥中玩家唯一的攻擊性卡牌是「重擊」(造成 8 傷害)，手段十分單一。為了在戰鬥中給予玩家更多元、更具策略性的攻擊手段以對抗具備不同防御屬性的怪物（例如防禦型怪物、高護盾怪等），我們需要引入三張新型攻擊性卡牌。

## Goals / Non-Goals

**Goals:**
- 在 `CardEffectType` 列舉中新增 `TRUE_DAMAGE` (真實傷害)、`BREAK_ARMOR_DAMAGE` (破盾後傷害)、`MULTI_DAMAGE` (多段傷害) 三個效果類型。
- 在 `Battle::executePlayerAction()` 中，正確實作這三種新型卡牌的戰鬥效果：
  - **貫穿擊** (真實傷害)：無視怪物護盾，直接扣減生命值。
  - **破甲重錘** (破盾後傷害)：先清除怪物當前護盾，再造成 5 點普通傷害。
  - **迅捷連擊** (多段傷害)：連續造成 3 次傷害判定（每次 3 點傷害），每次判定都會配合動畫。
- 將這三張卡牌新增至玩家 1-1 的初始手牌中。
- 將這三張卡牌新增至 Boss 戰前的增抽卡牌池 (Draft Card Pool) 中。

**Non-Goals:**
- 不修改原有卡牌（重擊、防禦、護盾、治療術、反擊姿態、生命繁茂、電擊術）的數值與原有邏輯。
- 不調整戰鬥系統除了玩家卡牌效果解析之外的邏輯。

## Decisions

### 1. 列舉擴充
修改 `include/Card.h` 中的 `CardEffectType`，在尾部加入：
```cpp
enum class CardEffectType {
    // ... 原有列舉
    TRUE_DAMAGE,
    BREAK_ARMOR_DAMAGE,
    MULTI_DAMAGE
};
```

### 2. 卡牌效果實作 (`Battle::executePlayerAction`)
在玩家出牌的邏輯處理中，加入以下分支：
- `CardEffectType::TRUE_DAMAGE`：呼叫 `monster.takeDamage(val, true, ...)`，將真實傷害參數設為 `true`。
- `CardEffectType::BREAK_ARMOR_DAMAGE`：先執行 `monster.setArmor(0)` 將護盾設為 0，接著執行 `monster.takeDamage(val, false, ...)`。
- `CardEffectType::MULTI_DAMAGE`：以迴圈執行 3 次 `monster.takeDamage(val, false, ...)`（在此 `val` 為單段傷害 3，共 3 段，即連擊三次）。

### 3. 配置至初始牌組與抽卡池
- 在 `Player::initStartingDeck` 中，當 `forceAllCards` 為 `true` 時，將這三張牌加入，使初始手牌在 1-1 時變為 10 張牌並全部抽上手。
- 在 `Game::draftCardsPhase()` 的 `pool` 列表內加入這三張牌的 Card 物件，使隨機增抽階段能抽到新卡牌。

## Risks / Trade-offs

- **多段傷害反擊判定**：多段傷害在打中處於反擊姿態的怪物（如果未來有怪物支援反擊的話）時可能會造成多次反彈。
  - *Mitigation*: 目前第一關怪物沒有反擊姿態，此影響微乎其微。
