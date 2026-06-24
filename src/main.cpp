#include "Game.h"
#include <cstdlib>

int main() {
    // 強制呼叫 system("chcp 65001 > nul") 解決 Windows 控制台中文與圖形字元亂碼
    system("chcp 65001 > nul");
    // 設定控制台視窗大小為 95 欄寬、35 列高，以完美適配卡牌與戰鬥介面
    system("mode con: cols=95 lines=35");
    
    Game game;
    game.run();
    
    return 0;
}
