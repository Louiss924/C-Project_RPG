# 傳奇勇者：卡牌冒險 (Legend of Card Hero) - 系統架構與類別設計圖

本文件提供專案的**類別關係圖 (UML Class Diagram)**與**系統架構流程圖 (System Architecture & Game Flow)**，協助您在專題報告、簡報與 Demo 中清晰展現 C++ 專案的物件導向結構與執行邏輯。

---

## 1. 類別關係圖 (UML Class Diagram)

本圖展現了專案核心類別的繼承、關聯與聚合關係：
- **繼承關係** (`Character` ➡️ `Player` / `Monster`) 展現 C++ 物件導向的多型與繼承。
- **組合與聚合關係** (`Player` 包含多張 `Card`；`Monster` 包含多組 `MonsterMove`)。
- **依賴與控制關係** (`Game` 驅動 `Battle` 與 `Player`；`Battle` 負責具體戰鬥邏輯的互動)。

```mermaid
classDiagram
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

    class Card {
        - string name
        - int spCost
        - CardEffectType effectType
        - int value
        - string description
        + Card(name, spCost, effectType, value, description)
        + getName() string
        + getSpCost() int
        + getEffectType() CardEffectType
        + getValue() int
        + getDescription() string
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

    class Battle {
        - Player& player
        - Monster& monster
        - int currentLevel
        + Battle(player, monster, currentLevel)
        + start(isFirstRound) bool
        - playerTurn() bool
        - monsterTurn() void
        - executeMonsterTurn() void
        - displayBattleState() void
        - displayLogs() void
    }

    class Game {
        - Player player
        - int currentLevel
        - int currentRound
        - int menuCursor
        - int totalElapsedSeconds
        - bool defeatedLevel1
        - time_point startTime
        - displayMainMenu() void
        - displayInstructions() void
        - saveGame() void
        - loadGame() bool
        - hasSaveFile() bool
        - displayLevelStartMessage() void
        - displayVictoryScreen() void
        - displayDefeatScreen() void
        - draftCardsPhase() void
        - playBossWarningAnimation() void
        - displayStoryDialogue() void
        - selectStartingLevelPhase() void
        + Game()
        + run() void
    }

    Character <|-- Player : 繼承 (Inheritance)
    Character <|-- Monster : 繼承 (Inheritance)
    Player "1" *-- "*" Card : 組合關係 (Composition)
    Monster "1" *-- "*" MonsterMove : 組合關係 (Composition)
    Game "1" *-- "1" Player : 控制與擁有 (Owns)
    Battle --> Player : 參照 (References)
    Battle --> Monster : 參照 (References)
    Game ..> Battle : 實體化與驅動 (Creates & Runs)

---

## 2. 系統架構與遊戲流程圖 (System Architecture & Game Flow)

本圖說明了整個程式從啟動 (`main.cpp`) 到主選單、存取檔管理、戰鬥迴圈（Player/Monster 回合交替）及關卡推進的執行脈絡：

```mermaid
flowchart TD
    Start([主程式啟動 main.cpp]) --> InitConsole[初始化控制台: 設定 UTF-8 編碼與 VT 處理以支援 ANSI 顏色及視窗最大化]
    InitConsole --> MainMenu{主選單 Game::displayMainMenu}

    MainMenu -->|開始冒險| SelectLvl[選擇起始關卡: 第一關/第二關]
    MainMenu -->|繼續冒險| LoadFile[載入存檔 Game::loadGame]
    MainMenu -->|遊戲說明| ShowInst[顯示說明面頁]
    MainMenu -->|離開遊戲| ExitGame([結束程式])

    ShowInst --> MainMenu
    SelectLvl --> InitPlayer[初始化玩家: 預設 HP 80, SP 7, 載入初始牌組]
    LoadFile -->|載入成功| StartLevelLoop
    LoadFile -->|載入失敗| MainMenu
    InitPlayer --> StartLevelLoop[進入關卡大迴圈 Game::run]

    StartLevelLoop --> LevelCond{當前關卡 <= 2 ?}
    LevelCond -->|是| BattleStart[生成對應關卡的魔物與 HP]
    LevelCond -->|否| ShowWin[通關慶典: 遊戲通關，傳奇勇者獲勝！ displayVictoryScreen]
    ShowWin --> DeleteSaveWin[刪除存檔 save.dat] --> ReturnMenu([返回主選單])

    BattleStart --> AutoSave[自動存檔 Game::saveGame]
    AutoSave --> PlayBattle[啟動戰鬥迴圈 Battle::start]

    PlayBattle --> CheckStun{怪物是否被眩暈?}
    CheckStun -->|是| PlayerTurn[玩家回合: 抽牌、顯示手牌顏色標籤與方向鍵選卡、出牌]
    CheckStun -->|否| MonsterTurn[怪物回合: 根據滾動意圖造成傷害/護盾]

    PlayerTurn --> PlayBattle
    MonsterTurn --> PlayBattle

    PlayBattle --> CheckHp{雙方 HP 狀態}
    CheckHp -->|玩家 HP <= 0| ShowDefeat[戰鬥失敗: 顯示勇者戰死畫面 displayDefeatScreen]
    CheckHp -->|怪物 HP <= 0| BattleWin[戰鬥勝利]
    CheckHp -->|皆活著| CheckStun

    ShowDefeat --> DeleteSaveDefeat[刪除存檔 save.dat] --> ReturnMenu

    BattleWin --> RoundCond{是否為 Boss 戰 Round 3 ?}
    
    RoundCond -->|否| DraftCards[進入卡牌增抽階段 draftCardsPhase]
    DraftCards --> SaveNextRound[儲存下一回合存檔]
    SaveNextRound --> AdvanceRound[Round 遞增 1] --> StartLevelLoop

    RoundCond -->|是| LevelCheck{是否為第二關 Level 2?}
    LevelCheck -->|否| GodGuidance[眾神的指引: 選擇隨機或固定傷害加成]
    GodGuidance --> SaveNextLvl[儲存新關卡存檔]
    SaveNextLvl --> AdvanceLevel[Level 遞增 1, Round 重置為 1] --> StartLevelLoop
    LevelCheck -->|是| ShowWin
