## MODIFIED Requirements

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
