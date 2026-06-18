## ADDED Requirements

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
