#define _WIN32_WINNT 0x0500
#include "Game.h"
#include <cstdlib>
#include <windows.h>

int main() {
    // 強制呼叫 system("chcp 65001 > nul") 解決 Windows 控制台中文與圖形字元亂碼
    system("chcp 65001 > nul");
    
    // 微小延遲確保 Windows 視窗管理器已完全關聯主控台視窗
    Sleep(100);
    
    // 獲取主控台視窗控制把手，並將視窗最大化
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        // 雙重保險：呼叫 ShowWindow 與發送視窗最大化訊息
        ShowWindow(hwnd, SW_MAXIMIZE);
        SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    }
    
    Game game;
    game.run();
    
    return 0;
}
