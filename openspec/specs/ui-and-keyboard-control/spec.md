# UI and Keyboard Control Spec

## Purpose
提供基於控制台的 UI 渲染、利用 `_getch()` 監聽上下方向鍵切換卡牌與 Enter 鍵出牌、出牌動作鎖定、以及血條漸進式扣減動畫。
## Requirements
### Requirement: Keyboard Navigation and Selection Control
系統必須全面禁用數字鍵進行出牌選擇。必須使用 `<conio.h>` 的 `_getch()` 監聽鍵盤上的方向鍵（↑/↓）在玩家手牌（或普通攻擊選項）之間進行高亮切換，並按下 Enter 鍵確認出牌或執行動作。

#### Scenario: Navigate Down Through Hand
- **WHEN** 玩家手牌選取游標在第 1 張卡，且玩家按下鍵盤上的下方向鍵（Down Arrow）
- **THEN** 游標必須移動至第 2 張卡，且畫面必須重繪以高亮顯示第 2 張卡

#### Scenario: Confirm Play Action
- **WHEN** 玩家按下 Enter 鍵確認選中的手牌
- **THEN** 系統必須發起出牌邏輯，驗證能量（SP）並執行卡牌技能

### Requirement: Screen Rendering Lock during Action
在玩家出牌或怪物執行招式時，系統必須鎖定鍵盤輸入，在畫面上暫停展示該動作的文字描述，避免玩家因連續敲擊鍵盤而跳過戰鬥細節的視覺呈現。

#### Scenario: Visual Display Lock
- **WHEN** 玩家打出卡牌或怪物發動攻擊
- **THEN** 系統必須在畫面上清楚顯示動作文字描述，並在指定時間內（例如 1 秒）忽略所有玩家的鍵盤輸入

### Requirement: Animated Health Bar Decreasing
當任何角色（玩家或怪物）受到傷害導致生命值扣除時，其血量條（Health Bar）與血量數值不得瞬間驟降。必須使用 `std::this_thread::sleep_for` 進行逐點或逐格扣減的動態重繪演出。

#### Scenario: Dynamic HP Reduction Animation
- **WHEN** 怪物受到 3 點傷害，其 HP 自 10 扣減至 7
- **THEN** 系統必須在每次扣除 1 點 HP 時，更新並重繪該怪物的血條與數值（顯示 10 -> 9 -> 8 -> 7），並在每次扣減點數之間暫停固定時間（例如 100 毫秒）

### Requirement: Card Drafting and Boss Warning Animation
在卡牌抽取階段以及 Boss 戰開始前，系統必須播放對應的動畫：包含滾動的隨機卡牌抽取動畫，以及 Boss 回合開始前的 Warning 閃爍警告動畫。

#### Scenario: Card Drafting Animation
- **WHEN** 卡牌抽取階段啟動
- **THEN** 控制台畫面必須動態滾動卡牌名稱，並以減速停格效果顯示最終獲得的卡牌

#### Scenario: Boss Warning Flashing Animation
- **WHEN** 玩家確認進入第 3 回合 Boss 戰
- **THEN** 畫面必須在進入戰鬥主畫面之前，播放交替閃爍的 WARNING 警告文字與警告框

### Requirement: Start Menu Keyboard Navigation
主選單畫面必須使用 `<conio.h>` 的 `_getch()` 監聽方向鍵（↑/↓）在選單選項之間切換高亮，並使用 Enter 鍵確認選擇。且必須無視其他非方向鍵與 Enter 鍵的輸入（除了在說明畫面按任意鍵返回外）。

#### Scenario: Navigate Start Menu
- **WHEN** 玩家選單高亮在第一個選項「開始冒險」並按下下方向鍵
- **THEN** 系統必須移動高亮至下一個選項「遊戲說明」，並重繪選單畫面

### Requirement: Horizontal Card Grid Display
系統在戰鬥介面的手牌展示區，必須以橫向並排 ASCII 卡牌框的形式渲染玩家的所有手牌。手牌必須自動依據卡牌類型（攻擊型 ➡️ 防禦型 ➡️ 輔助型）進行排序，且每張卡牌內部必須展示種類標籤。當手牌總數大於 5 張時，系統必須限制每行最多顯示 5 張卡牌，其餘卡牌自動換行（多行顯示）。

#### Scenario: Render 5 Cards in a Single Row
- **WHEN** 進入戰鬥，玩家手牌數為 5 張，且游標選在「普通攻擊」
- **THEN** 系統必須在手牌區依種類排序橫向並排渲染 5 張卡牌，每張卡牌展示種類標籤、卡名、SP消耗與效果描述。未選取卡牌的邊框顏色必須依種類上色（攻擊為淡紅色，防禦為淡藍色，輔助為淡綠色）

#### Scenario: Highlight Selected Hand Card
- **WHEN** 玩家切換游標並選取手牌中的第 2 張卡牌
- **THEN** 系統必須將第 2 張卡牌的邊框改為金黃色高亮邊框（*===*），其餘未選取的卡牌維持其種類的專屬顏色邊框

#### Scenario: Wrap Hand Cards on Exceeding Limit
- **WHEN** 玩家手牌為 10 張（如關卡 1-1 開局）
- **THEN** 系統必須將其渲染為兩列，第一列顯示前 5 張卡牌，第二列顯示後 5 張卡牌，且兩列卡牌皆依種類排序並標記顏色



