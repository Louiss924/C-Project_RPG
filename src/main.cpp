#define _WIN32_WINNT 0x0500
#include "Game.h"
#include <cstdlib>
#include <windows.h>

int main() {
    // 強制呼叫 system("chcp 65001 > nul") 解決 Windows 控制台中文與圖形字元亂碼
    system("chcp 65001 > nul");
    
    // 獲取主控台視窗控制把手，並將視窗最大化
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        ShowWindow(hwnd, SW_MAXIMIZE);
    }
    
    Game game;
    game.run();
    
    return 0;
}
