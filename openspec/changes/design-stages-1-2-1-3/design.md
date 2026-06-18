## Context

玩家在 1-2 面對哥布林斥候，1-3 面對哥布林酋長。現有的怪物設定數值偏低（35 HP / 55 HP），且技能單調（僅為純傷害或普通防禦），沒有任何控制或負面狀態技能。同時，戰鬥前後直接切入與切出，缺乏劇情的連貫感與帶入感。

## Goals / Non-Goals

**Goals:**
- 提升 1-2 與 1-3 怪物的 HP（分別調整為 40 HP 與 65 HP），使其具備更好的生存能力。
- 新增怪物的特殊技能機制，包含：
  - 多段攻擊（連續對玩家進行多次傷害判定）。
  - 真實傷害（穿透護盾）。
  - 吸取 SP（造成傷害同時減少玩家當前的 SP）。
  - 眩暈玩家（使玩家在下一回合無法採取行動）。
- 在關卡戰鬥開始前與勝利後，繪製並顯示劇情的對話文本，提昇代入感。

**Non-Goals:**
- 不修改玩家的卡牌效果與基本屬性配置。
- 不修改史萊姆或第二、三大關怪物的數值與招式設計。

## Decisions

### 1. 劇情對話的展現
在 `Game` 類別中新增一個輔助函數 `displayStoryDialogue(const std::string& character, const std::vector<std::string>& lines)`。每次顯示時清空控制台，印出角色名稱以及逐行顯示對話內容，並使用 `_getch()` 讓玩家按任意鍵繼續。
這會在 `Game::run` 進入 `Battle::start` 之前以及戰鬥獲勝之後呼叫。

### 2. 怪物特殊技能的擴充與解析
為了在 C++11 結構中支援這些招式，我們需要在 `MonsterMove` 結構中擴大屬性（或是利用現有的屬性進行解析）。
我們來看一下 `MonsterMove` 結構的定義（在 `include/Monster.h`）。
目前它的欄位大概有：`name`、`damage`、`armorGain`、`description`、`isTrueDamage` 等等。
我們可以擴充 `MonsterMove` 的屬性，在其中增加 `isMultiStrike`、`hits`、`drainSp`、`stunsPlayer` 等欄位，或是新增一個專用建構子，使得擴增的欄位在其他關卡怪物中預設為關閉。

### 3. 戰鬥邏輯的修改
- **多段攻擊**：若 `move.hits > 1`，則在 `Battle::executeMonsterTurn` 中利用迴圈執行 `player.takeDamage` 共 `hits` 次。
- **吸取 SP**：若 `move.drainSp > 0`，在攻擊時呼叫 `player.useSP(move.drainSp)`。
- **眩暈玩家**：若 `move.stunsPlayer` 且攻擊成功對玩家造成傷害（或只要出招），呼叫 `player.setIsStunned(true)`。
- **玩家眩暈檢測**：在 `Battle::start` 內部的戰鬥主迴圈中，當 `isPlayerTurn == true` 時，若 `player.getIsStunned() == true`，則印出提示並將 `player.setIsStunned(false)`，直接將 `isPlayerTurn` 設為 `false` 跳過玩家回合。

## Risks / Trade-offs

- **玩家卡手與眩暈死局**：若怪物高頻率地眩暈玩家或扣除 SP，玩家可能會完全無法還手。
  - *Mitigation*: 眩暈與扣 SP 的招式必須有冷卻或機率性（例如在招式列表中只佔其中一項，怪物不會連續兩回合使用相同招式）。
