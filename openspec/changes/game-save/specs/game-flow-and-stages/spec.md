## ADDED Requirements

### Requirement: Continue Adventure Menu Option
系統必須在主選單畫面檢測存檔檔案 `save.dat` 是否存在。如果存在，主選單必須新增並顯示「繼續冒險」選項。如果不存在，主選單則不顯示此選項。

#### Scenario: Show Continue Adventure Option
- **WHEN** 遊戲啟動且本地目錄下存在 `save.dat` 檔案
- **THEN** 主選單必須渲染「繼續冒險」選項，總選項數變為 4 個，並預設高亮第一個選項

#### Scenario: Hide Continue Adventure Option
- **WHEN** 遊戲啟動且本地目錄下不存在 `save.dat` 檔案
- **THEN** 主選單不得渲染「繼續冒險」選項，僅提供「開始冒險」、「遊戲說明」、「離開遊戲」三個選項
