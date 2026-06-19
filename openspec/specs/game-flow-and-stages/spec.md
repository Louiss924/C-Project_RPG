# Game Flow and Stages Spec

## Purpose
處理關卡流程（3 個關卡，每關 3 回合，第 3 回合為 Boss 戰）、關卡切換、勝敗判定與遊戲初始化。
## Requirements
### Requirement: Levels and Rounds Progression
系統必須支援由 3 個關卡（Levels）組成的進度流程。每個關卡包含 3 個回合（Rounds），其中第 3 回合固定為首領（Boss）回合。在戰鬥勝利後，玩家應能晉級至下一回合或下一關卡。

#### Scenario: Normal Round Victory Progression
- **WHEN** 玩家擊敗當前關卡第 1 或第 2 回合的怪物
- **THEN** 系統必須存檔並自動載入該關卡的下一回合戰鬥（例如從 Round 1 進入 Round 2）

#### Scenario: Boss Round Victory Progression
- **WHEN** 玩家擊敗當前關卡的 Boss（第 3 回合）
- **THEN** 系統必須重置玩家能量（SP）至基礎值，保留當前的生命值（HP）與最大生命值（Max HP）上限，並將玩家推進至下一關卡的第 1 回合；若為第 3 關 Boss 則觸發通關勝利

### Requirement: Game Victory and Defeat Conditions
系統必須在任意戰鬥回合中即時監測玩家與怪物的生命值。當玩家 HP 歸零或以下時判定遊戲結束；當擊敗第三關的 Boss 時判定遊戲通關。

#### Scenario: Player Defeat
- **WHEN** 玩家的 HP 降低至 0 或更低
- **THEN** 系統必須停止戰鬥、鎖定輸入，並於畫面顯示「遊戲結束」提示，隨後退出程式

#### Scenario: Overall Game Victory
- **WHEN** 第 3 關（Level 3）第 3 回合（Round 3）的 Boss HP 降低至 0 或更低
- **THEN** 系統必須顯示「遊戲通關，勇者勝利！」的結算畫面，並在玩家按任意鍵後退出程式

### Requirement: Card Drafting Phase Before Boss
系統必須在擊敗大關第 2 回合怪物後、且進入第 3 回合 Boss 戰前，提供隨機卡牌抽取機制，讓玩家從所有卡牌池中隨機抽取 2 張加入永久牌組。

#### Scenario: Card Drafting Process
- **WHEN** 玩家擊敗當前關卡第 2 回合的怪物並確認進入卡牌抽取
- **THEN** 系統隨機選取並展示抽取卡牌，在玩家確認後將這 2 張卡牌新增至玩家的永久牌組

### Requirement: Story Dialogue Before and After Combat
The system MUST display story dialogue text before the start of a combat and after a combat victory for Level 1-2 and Level 1-3, and wait for player input before proceeding.

#### Scenario: Show Dialogue Before Battle
- **WHEN** entering the battle of Level 1-2 or Level 1-3 before combat starts
- **THEN** the system MUST display the dialogue screen with text and wait for a keypress to start the battle

#### Scenario: Show Dialogue After Battle Victory
- **WHEN** the player defeats the monster of Level 1-2 or Level 1-3
- **THEN** the system MUST display the victory story dialogue and wait for a keypress before progressing

### Requirement: Add New Cards to Player Deck and Draft Pool
The game flow system MUST add the three new offensive cards (Pierce Strike, Armor Smasher, Combo Strike) to the player's 1-1 starting deck and the pre-boss card draft pool.

#### Scenario: Verify New Cards in starting deck
- **WHEN** the player enters battle Level 1-1
- **THEN** the player's starting hand MUST contain Pierce Strike, Armor Smasher, and Combo Strike cards

#### Scenario: Verify New Cards in draft pool
- **WHEN** the card drafting phase starts before entering Round 3
- **THEN** the selection pool MUST include Pierce Strike, Armor Smasher, and Combo Strike cards

### Requirement: Start Screen and Main Menu
在遊戲啟動時，系統必須顯示包含遊戲名稱與選單選項的主畫面。主畫面必須提供「開始冒險」、「遊戲說明」、「離開遊戲」三個選項。

#### Scenario: Show Start Screen at Startup
- **WHEN** 遊戲程式啟動時
- **THEN** 系統必須在畫面上繪製遊戲標題與選項，並預設高亮第一個選項「開始冒險」

#### Scenario: Start Game Selection
- **WHEN** 玩家在高亮選中「開始冒險」時按下 Enter 鍵
- **THEN** 系統必須關閉主畫面，進入 Level 1-1 的關卡流程與戰鬥

#### Scenario: View Instructions Selection
- **WHEN** 玩家在高亮選中「遊戲說明」時按下 Enter 鍵
- **THEN** 系統必須顯示詳細的遊戲說明、規則與按鍵對照表，並在玩家按任意鍵後回到主選單畫面

#### Scenario: Exit Game Selection
- **WHEN** 玩家在高亮選中「離開遊戲」時按下 Enter 鍵
- **THEN** 系統必須優雅地結束程式並退出


