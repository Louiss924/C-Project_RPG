#include "Game.h"
#include <cstdlib>

int main() {
    // 強制呼叫 system("chcp 65001 > nul") 解決 Windows 控制台中文與圖形字元亂碼
    system("chcp 65001 > nul");
    
    Game game;
    game.run();
    
    return 0;
}
