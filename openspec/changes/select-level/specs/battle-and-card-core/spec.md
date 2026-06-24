## ADDED Requirements

### Requirement: Starting Level Selection Menu
當玩家在主選單點擊「開始冒險」時，系統必須顯示一個關卡選擇畫面，供玩家選取要挑戰的起始大關。

#### Scenario: Level 1 Selection
- **WHEN** 玩家進入關卡選擇選單，使用方向鍵選擇 Level 1 並點擊 Enter 鍵確認
- **THEN** 系統將玩家的當前關卡 (currentLevel) 初始化為 1，當前回合 (currentRound) 初始化為 1，並載入第一關的關卡開始畫面

#### Scenario: Level 2 Selection
- **WHEN** 玩家進入關卡選擇選單，使用方向鍵選擇 Level 2 並點擊 Enter 鍵確認
- **THEN** 系統將玩家的當前關卡 (currentLevel) 初始化為 2，當前回合 (currentRound) 初始化為 1，並載入第二關的關卡開始畫面
