## 1. 擴充怪物招式結構與屬性

- [x] 1.1 修改 `include/Monster.h` 中的 `MonsterMove` 結構，加入 `hits` (多段攻擊次數)、`drainSp` (吸取 SP 數值)、`stunsPlayer` (眩暈玩家判定) 等屬性，並更新建構子提供預設值。

## 2. 實作特殊怪物技能的戰鬥邏輯

- [x] 2.1 修改 `src/Battle.cpp` 的 `Battle::executeMonsterTurn`：若 `move.hits > 1`，使用迴圈多次呼叫 `player.takeDamage`。
- [x] 2.2 修改 `src/Battle.cpp` 的 `Battle::executeMonsterTurn`：若 `move.drainSp > 0`，則扣除玩家對應的 SP。
- [x] 2.3 修改 `src/Battle.cpp` 的 `Battle::executeMonsterTurn`：若 `move.stunsPlayer` 為真，則對玩家附加眩暈狀態。
- [x] 2.4 在 `Battle::start` (或是玩家回合開始的 handle 邏輯) 處理玩家眩暈狀態：若為眩暈狀態則清除狀態，直接跳過該回合。

## 3. 實作關卡對話文字繪製

- [x] 3.1 於 `Game` 類別中，實作 `displayStoryDialogue` 方法，能夠顯示劇情對話內容並暫停等待玩家確認。
- [x] 3.2 於 `Game::run` 中，在進入 1-2 及 1-3 戰鬥前，呼叫該方法印出開戰前的劇情對話。
- [x] 3.3 於 `Game::run` 中，在 1-2 及 1-3 戰鬥獲勝後，呼叫該方法印出勝利後的劇情對話。

## 4. 重新設計 1-2 和 1-3 的怪物數值配置

- [x] 4.1 修改 `Game::run` 中 1-2 哥布林斥候配置：HP 提升為 40，新增「三連投擲」(hits=3) 與「毒刃突襲」(drainSp=1) 招式。
- [x] 4.2 修改 `Game::run` 中 1-3 哥布林酋長配置：HP 提升為 65，新增「震撼重擊」(stunsPlayer=true) 與「狂暴揮擊」(isTrueDamage=true) 招式。
- [x] 4.3 執行編譯與手動測試，確保對話、多段攻擊、扣 SP 與眩暈玩家之功能無誤。
