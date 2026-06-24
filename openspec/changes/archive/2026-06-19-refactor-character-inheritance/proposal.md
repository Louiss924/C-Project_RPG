## Why

目前專案中的 `Player`（玩家）與 `Monster`（怪物）雖然都是戰鬥中的角色實體，但它們的程式碼中存在高度重複的屬性（如名稱 name、生命值 hp、最大生命值 maxHp、護盾值 armor、眩暈狀態 isStunned）以及完全相同的受到傷害動態扣減與動畫邏輯（`takeDamage`）。
這導致程式碼冗餘度高、維護困難。本變更將引入基底類別 `Character`，並將共同的屬性與受傷演算法抽離至基底類別中，藉此呈現 C++ 的類別繼承（Class Inheritance）與程式碼重用設計。

## What Changes

1. **新增 `Character` 基底類別**：
   - 提取並實作共同的屬性（name, hp, maxHp, armor, isStunned）及其 Getters/Setters 方法。
   - 將 `takeDamage` 受到傷害的核心演算邏輯（含護盾扣減與血量逐步扣減動畫）搬移至 `Character` 類別中，作為虛擬方法（Virtual Method）。
2. **重構 `Player` 類別**：
   - 使 `Player` 繼承自 `Character`。
   - 移除 `Player` 中重複的 HP/Armor 屬性、Getters/Setters 以及 `takeDamage` 的重複實作。
   - 保留 `Player` 特有的 SP 能量與手牌管理等方法。
3. **重構 `Monster` 類別**：
   - 使 `Monster` 繼承自 `Character`。
   - 移除 `Monster` 中重複的 HP/Armor 屬性、Getters/Setters 以及 `takeDamage` 的重複實作。
   - 保留 `Monster` 特有的意圖隨機決定（intent rolling）等方法。

## Capabilities

### New Capabilities

無。

### Modified Capabilities

無。

## Impact

- 影響 `include/Player.h`、`src/Player.cpp`、`include/Monster.h` 和 `src/Monster.cpp`。
- 新增 `include/Character.h` 和 `src/Character.cpp`。
- 由於繼承關係及建構子重構，需要調整 `src/Game.cpp` 與 `src/Battle.cpp` 中初始化 `Player` 與 `Monster` 的建構呼叫。
