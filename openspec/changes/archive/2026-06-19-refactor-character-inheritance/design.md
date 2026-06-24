## Context

目前遊戲中的 `Player` 與 `Monster` 類別分別獨立擁有 `name`, `hp`, `maxHp`, `armor`, `isStunned` 屬性，且兩者對於 `takeDamage` 受到傷害扣減及動畫邏輯完全一致，形成重度重複程式碼。

## Goals / Non-Goals

**Goals:**
- 新增 `Character` 為共同基底類別，實作共有屬性的封裝、存取子以及 `takeDamage` 動態扣減動畫的核心演算邏輯。
- 讓 `Player` 與 `Monster` 繼承自 `Character`，重構其建構子，並移除其中重複的成員變數與方法。
- 保留玩家專屬的 SP 與卡牌機制，以及怪物專屬的意圖與招式機制。
- 維持遊戲既有功能與行為完全不變。

**Non-Goals:**
- 不修改 `Card` 或其他系統的架構。
- 不調整原本的戰鬥邏輯、傷害公式或動畫時間。

## Decisions

### 1. 基底類別成員變數的存取權限 (Access Specifier)
- **選擇**：將共有變數設為 `protected`，例如 `protected: std::string name;`。
- **原因**：`protected` 允許衍生類別（`Player`, `Monster`）直接讀取與寫入這些核心變數，在繼承體系中更為直觀，且依然對外部類別（如 `Battle`）維持封裝保護。

### 2. `takeDamage` 的多型設計 (Virtual Function)
- **選擇**：將 `takeDamage` 聲明為 `virtual void takeDamage(...)`，並在基底類別中實作預設的逐點扣血動畫 logic。
- **原因**：這能確保玩家和怪物都能共用這一套核心受傷動畫。且如果未來有特定怪物（或玩家狀態）需要特殊受傷規則，可以直接在衍生類別中進行覆寫（Override）。

### 3. 建構子重構 (Constructor Initialization)
- **選擇**：重構 `Player` 與 `Monster` 的建構建構子，呼叫基底類別的成員初始化列表：
  - `Player(...) : Character("勇者", hp, maxHp), ...`
  - `Monster(name, hp, maxHp, ...) : Character(name, hp, maxHp), ...`
- **原因**：這是 C++ 繼承的標準做法，確保基底類別的成員能被正確初始化。

## Risks / Trade-offs

- **風險：繼承後建構順序導致的未定義行為**
  - *緩解措施*：確認 C++ 初始化順序為「先基底類別，後衍生類別」，在衍生類別建構子體中不使用未初始化的基底類別變數。
- **風險：多型調用下的記憶體洩漏**
  - *緩解措施*：為 `Character` 類別加上虛擬解構子（`virtual ~Character() = default;`），確保未來以基底類別指標進行 `delete` 時能正確釋放衍生類別資源。
