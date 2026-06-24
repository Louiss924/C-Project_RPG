# 傳奇勇者：卡牌冒險 (Legend of Card Hero) - 系統架構與類別設計圖

本文件提供專案的**類別關係圖 (UML Class Diagram)**與**系統架構流程圖 (System Architecture & Game Flow)**，協助您在專題報告、簡報與 Demo 中清晰展現 C++ 專案的物件導向結構與執行邏輯。

為適應橫向簡報 (16:9) 與報告排版，類別圖已模組化拆分，流程圖已調整為由左至右之橫向展開版。

---

## 1. 類別關係圖 (UML Class Diagram)

### 模組 1：角色繼承架構 (Character Inheritance)
*本圖聚焦於專案核心的角色繼承關係，展現 C++ 物件導向的多型與繼承特色。*

```mermaid
classDiagram
    direction LR
    class Character {
        # string name
        # int hp
        # int maxHp
        # int armor
        # bool isStunned
        + Character(name, hp, maxHp)
        + ~Character() virtual
        + getName() string
        + getHp() int
        + getMaxHp() int
        + getArmor() int
        + getIsStunned() bool
        + setHp(hp) void
        + setMaxHp(maxHp) void
        + setArmor(armor) void
        + setIsStunned(state) void
        + takeDamage(damage, isTrueDamage, drawCallback) virtual void
        + resetTurnState() virtual void
    }

    class Player {
        - int sp
        - int maxSp
        - bool isCountering
        - int totalTurns
        - bool acceptedGodsGuidance
        - vector~Card~ deck
        - vector~Card~ hand
        - vector~Card~ discardPile
        - sortHand() void
        + Player(hp, maxHp, sp, maxSp)
        + getSp() int
        + getMaxSp() int
        + getIsCountering() bool
        + setSp(sp) void
        + setIsCountering(state) void
        + gainSP(amount) void
        + useSP(amount) bool
        + gainArmor(amount) void
        + heal(amount) void
        + gainMaxHP(amount) void
        + initStartingDeck(forceAllCards) void
        + shuffleDeck() void
        + addCardToDeck(card) void
        + setDeckState(deck, hand, discard) void
        + drawCards(count) vector~Card~
        + discardHand() void
        + playCard(index) void
        + getHand() vector~Card~
        + getDeck() vector~Card~
        + getDiscardPile() vector~Card~
        + resetTurnState() override void
        + createCardByName(name)$ Card
    }

    class Monster {
        - vector~MonsterMove~ moves
        - MonsterMove nextMove
        - int actionCount
        + Monster(name, hp, maxHp, moves)
        + getNextMove() MonsterMove
        + rollIntent() void
        + incrementActionCount() void
        + getActionCount() int
        + resetActionCount() void
    }

    Character <|-- Player : 繼承 (Inheritance)
    Character <|-- Monster : 繼承 (Inheritance)
```

### 模組 2：戰鬥與卡牌聚合關係 (Combat & Systems)
*本圖展現了主程式、戰鬥引擎、卡牌與怪物的關係，展示組合 (Composition) 與依賴 (Dependency) 設計。*

```mermaid
classDiagram
    direction LR
    class Game {
        - Player player
        - int currentLevel
        - int currentRound
        - int menuCursor
        - int totalElapsedSeconds
        - bool defeatedLevel1
        - time_point startTime
        + Game()
        + run() void
        - saveGame() void
        - loadGame() bool
        - hasSaveFile() bool
        - displayMainMenu() void
        - selectStartingLevelPhase() void
    }

    class Battle {
        - Player& player
        - Monster& monster
        - int currentLevel
        + Battle(player, monster, currentLevel)
        + start(isFirstRound) bool
        - playerTurn() bool
        - monsterTurn() void
        - executeMonsterTurn() void
    }

    class Card {
        - string name
        - int spCost
        - CardEffectType effectType
        - int value
        - string description
        + Card(name, spCost, effectType, value, description)
    }

    class MonsterMove {
        + string name
        + int damage
        + int armorGain
        + string description
        + bool isTrueDamage
        + int hits
        + int drainSp
        + bool stunsPlayer
        + MonsterMove(name, damage, armorGain, description, isTrueDamage, hits, drainSp, stunsPlayer)
    }

    Game ..> Battle : 實體化與驅動 (Creates & Runs)
    Battle --> Player : 參照 (References)
    Battle --> Monster : 參照 (References)
    Player "1" *-- "*" Card : 組合關係 (Composition)
    Monster "1" *-- "*" MonsterMove : 組合關係 (Composition)
```

---

## 2. 系統架構與遊戲流程圖 (System Architecture & Game Flow)

```mermaid
flowchart LR
    Start([主程式啟動 main.cpp]) --> InitConsole[初始化控制台] --> MainMenu{主選單}

    MainMenu -->|開始冒險| SelectLvl[選擇起始關卡]
    MainMenu -->|繼續冒險| LoadFile[載入存檔]
    MainMenu -->|遊戲說明| ShowInst[顯示說明頁]
    MainMenu -->|離開遊戲| ExitGame([結束程式])

    ShowInst --> MainMenu
    SelectLvl --> InitPlayer[初始化玩家與牌組]
    LoadFile -->|載入成功| StartLevelLoop
    LoadFile -->|載入失敗| MainMenu
    InitPlayer --> StartLevelLoop[進入關卡大迴圈]

    StartLevelLoop --> LevelCond{當前關卡 <= 2 ?}
    LevelCond -->|是| BattleStart[生成對應魔物]
    LevelCond -->|否| ShowWin[通關慶典 displayVictoryScreen]
    ShowWin --> DeleteSaveWin[刪除存檔 save.dat] --> ReturnMenu([返回主選單])

    BattleStart --> AutoSave[自動存檔 saveGame]
    AutoSave --> PlayBattle[啟動戰鬥迴圈 Battle::start]

    subgraph "戰鬥迴圈 (Battle Loop)"
        PlayBattle --> CheckStun{是否被眩暈?}
        CheckStun -->|是| PlayerTurn[玩家回合: 選卡/出牌]
        CheckStun -->|否| MonsterTurn[怪物回合: 依意圖行動]
    end

    PlayerTurn --> CheckHp
    MonsterTurn --> CheckHp

    CheckHp{雙方 HP 狀態} -->|玩家死亡| ShowDefeat[戰鬥失敗 displayDefeatScreen]
    CheckHp -->|怪物死亡| BattleWin[戰鬥勝利]
    CheckHp -->|皆存活| PlayBattle

    ShowDefeat --> DeleteSaveDefeat[刪除存檔 save.dat] --> ReturnMenu

    BattleWin --> RoundCond{是否為 Boss 戰 Round 3 ?}
    
    RoundCond -->|否| DraftCards[卡牌增抽階段]
    DraftCards --> SaveNextRound[儲存下一回合存檔]
    SaveNextRound --> AdvanceRound[Round 遞增] --> StartLevelLoop

    RoundCond -->|是| LevelCheck{是否為第二關 Level 2?}
    LevelCheck -->|否| GodGuidance[眾神的指引選擇]
    GodGuidance --> SaveNextLvl[儲存新關卡存檔]
    SaveNextLvl --> AdvanceLevel[Level 遞增, Round重置] --> StartLevelLoop
    LevelCheck -->|是| ShowWin
```
