#define _WIN32_WINNT 0x0500
#include "Game.h"
#include <cstdlib>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

int main() {
    // 強制呼叫 system("chcp 65001 > nul") 解決 Windows 控制台中文與圖形字元亂碼
    system("chcp 65001 > nul");
    
    // 1. 設定臨時唯一標題，確保在各類控制台容器中都能定位視窗
    SetConsoleTitle("LCRPG_TEMP_TITLE_12345");
    Sleep(100); 
    
    // 2. 優先用 FindWindow 搜尋該標題的視窗控制把手
    HWND hwnd = FindWindow(NULL, "LCRPG_TEMP_TITLE_12345");
    if (hwnd == NULL) {
        hwnd = GetConsoleWindow();
    }
    
    if (hwnd != NULL) {
        // 3. 還原標題為遊戲名稱
        SetConsoleTitle("傳奇勇者：卡牌冒險 (Legend of Card Hero)");
        // 4. 雙重指令進行視窗最大化
        ShowWindow(hwnd, SW_MAXIMIZE);
        SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    }
    
    // 5. 啟用虛擬終端機處理 (Virtual Terminal Processing) 以支援 ANSI 顏色
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
    
    Game game;
    game.run();
    
    return 0;
}

