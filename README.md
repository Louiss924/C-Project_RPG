# C++ Card RPG 遊戲框架 (C++ Card RPG Framework)

本專案是一個基於 C++11 標準開發的單人卡牌建構（Deckbuilding）RPG 遊戲。設計目標在於提供一個乾淨、結構化的回合制戰鬥引擎，配合 Windows 控制台的優質鍵盤操作與動畫效果，並確保能直接於學校電腦（例如 Dev-C++ / MinGW 環境）進行編譯與順利執行。

## 專案特性

1. **結構化設計**：標頭檔與實作檔分離（`/include` 與 `/src`）。
2. **Windows 控制台支援**：
   - 解決中文與特殊字元亂碼：使用 UTF-8 編碼，並在程式開始時呼叫 `system("chcp 65001 > nul")`。
   - 純鍵盤流操作：使用 `_getch()` 捕捉方向鍵（↑/↓）切換手牌，Enter 鍵確認出牌，禁用數字鍵。
3. **優質視覺效果**：
   - 行動鎖定演出：出牌或怪物行動時顯示詳細日誌，並暫停 1 秒（忽略期間的所有鍵盤輸入，避免搶按）。
   - 血條逐點減少動畫：血量扣減時以 80ms 延遲逐點重繪血條。
4. **完整遊戲流程**：
   - 共 3 大關卡，每關 3 回合（第 3 回合為 Boss 戰）。
   - 擁有 6 種卡牌效果：傷害、回復、護盾、反擊、最大生命值上限提升、眩暈（電暈）。
   - 怪物意圖預告：畫面上方清晰顯示怪物下回合招式與預估傷害。

---

## 學校電腦 (Dev-C++ / MinGW) 編譯與環境移轉指南

為了方便在學校電腦（Dev-C++ 或 MinGW 終端機）進行編譯與執行，請遵循以下步驟：

### 方法一：使用 Dev-C++ 編譯

1. **開啟 Dev-C++**，選擇 `File` -> `New` -> `Project...`。
2. 選擇 **Console Application**，語言選擇 **C++**，為專案命名並選擇儲存路徑。
3. 在左側專案管理員中，將預設產生的 `main.cpp` 移除。
4. 對專案按右鍵選擇 **Add to Project**，將 `/include` 資料夾下的所有 `.h` 檔案與 `/src` 資料夾下的所有 `.cpp` 檔案加入專案。
5. **設定 C++11 支持**（非常重要）：
   - 點選上方選單 `Tools` -> `Compiler Options`。
   - 在 `Compiler` 頁籤中，勾選 `"Add the following commands when calling the compiler"`。
   - 在下方的輸入框中填入：`-std=c++11` (或更高，例如 `-std=c++14`)。
   - 如果遇到編譯器抱怨，請確保使用 TDM-GCC 或 MinGW 4.8.1 以上版本。
6. **設定檔案編碼**：
   - Dev-C++ 預設可能使用 ANSI / Windows-950 (CP950) 開啟檔案。
   - 本專案檔案皆為 **UTF-8（無 BOM）** 編碼。
   - 請在 `Tools` -> `Editor Options` -> `General` -> `Encoding` 中確認編碼設定為 `UTF-8`，以防中文註解與輸出文字變成亂碼。
7. 點選 **Compile & Run** (F11) 即可執行。

### 方法二：使用命令列 (MinGW / GCC) 手動編譯

如果您直接在 Windows 的命令提示字元 (cmd) 或 PowerShell 使用 gcc/g++，請在專案根目錄下執行以下指令：

```bash
# 編譯指令
g++ -std=c++11 -I./include src/*.cpp -o CardRPG.exe

# 執行遊戲
.\CardRPG.exe
```

*註：`-I./include` 參數是為了讓編譯器在編譯 `/src` 裡的實作檔時，能正確找到 `/include` 目錄下的標頭檔。*

---

## 專案結構說明

- `/include`：存放所有類別的定義（標頭檔 `.h`）
- `/src`：存放所有類別的具體邏輯實作（`.cpp`）與入口點 `main.cpp`
- `README.md`：環境移轉與編譯說明（本檔案）
