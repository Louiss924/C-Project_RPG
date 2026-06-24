## 1. 手牌自動排序機制 (Player Hand Sorting Mechanism)

- [x] 1.1 在 `include/Player.h` 中宣告私有方法 `void sortHand()`
- [x] 1.2 在 `src/Player.cpp` 中實作 `sortHand()`，定義卡牌種類排序優先權（攻擊型 ➡️ 防禦型 ➡️ 輔助型）
- [x] 1.3 在 `src/Player.cpp` 中的 `drawCards()`、`playCard()`、`setDeckState()` 結尾處呼叫 `sortHand()`

## 2. 戰鬥 UI 種類顯示與邊框色彩化 (Battle UI Type Display and Color Borders)

- [x] 2.1 在 `src/Battle.cpp` 中新增種類顏色判定函式，依據卡牌類型回傳邊框 ANSI 顏色字串（攻擊：`COLOR_LRED`，防禦：`COLOR_LBLUE`，輔助：`COLOR_LGREEN`，選取中：`COLOR_LYELLOW`）
- [x] 2.2 修改 `Battle::drawUI()` 中手牌 ASCII 卡牌的頂框、底框、SP 行與效果描述行的渲染邏輯，使其改用種類邊框顏色
- [x] 2.3 在 `Battle::drawUI()` 的手牌卡牌渲染中，插入「種類分類」列，顯示 `⚔️ 攻擊`、`🛡️ 防禦` 或 `🌳 輔助` 種類標籤與顏色

## 3. 編譯與驗證 (Compilation & Verification)

- [x] 3.1 使用 `g++ src\*.cpp -Iinclude -o game.exe` 編譯專案
- [x] 3.2 啟動遊戲並進入戰鬥，確認手牌是否自動依「攻擊 ➡️ 防禦 ➡️ 輔助」順序排序
- [x] 3.3 檢查手牌 ASCII 邊框是否依種類上色（淡紅、淡藍、淡綠），且當游標移動到對應卡牌時，邊框變為金黃色高亮
- [x] 3.4 檢查每張卡牌內部是否包含種類分類標籤（如 `⚔️ 攻擊`、`🛡️ 防禦` 等）
