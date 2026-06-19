## ADDED Requirements

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
