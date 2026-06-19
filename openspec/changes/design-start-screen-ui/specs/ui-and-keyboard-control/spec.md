## ADDED Requirements

### Requirement: Start Menu Keyboard Navigation
主選單畫面必須使用 `<conio.h>` 的 `_getch()` 監聽方向鍵（↑/↓）在選單選項之間切換高亮，並使用 Enter 鍵確認選擇。且必須無視其他非方向鍵與 Enter 鍵的輸入（除了在說明畫面按任意鍵返回外）。

#### Scenario: Navigate Start Menu
- **WHEN** 玩家選單高亮在第一個選項「開始冒險」並按下下方向鍵
- **THEN** 系統必須移動高亮至下一個選項「遊戲說明」，並重繪選單畫面
