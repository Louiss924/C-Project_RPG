## 1. 建立 Character 共同基底類別

- [x] 1.1 在 `include/Character.h` 中定義 `Character` 類別，包含共有屬性與虛擬建構子/解構子、Getters/Setters，以及 `takeDamage` 受到傷害虛擬函式宣告。
- [x] 1.2 在 `src/Character.cpp` 中實作 `Character` 的建構子、Getters/Setters 以及帶有動畫邏輯的 `takeDamage` 函式。

## 2. 重構 Player 與 Monster 繼承關係

- [x] 2.1 修改 `include/Player.h` 與 `src/Player.cpp`，繼承 `Character` 類別，移除重複成員變數、屬性存取子及重複之 `takeDamage` 實作。
- [x] 2.2 修改 `include/Monster.h` 與 `src/Monster.cpp`，繼承 `Character` 類別，移除重複成員變數、屬性存取子及重複之 `takeDamage` 實作。
- [x] 2.3 在 `src/Game.cpp` 及 `src/Battle.cpp` 中修正對 `Player` 與 `Monster` 建構子的調用與繼承後存取的適應性調整。
