#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
private:
    Player player;
    int currentLevel;
    int currentRound;
    int menuCursor; // 記錄主選單游標位置
    void displayMainMenu(); // 顯示主選單並處理輸入
    void displayInstructions(); // 顯示遊戲說明頁面
    void saveGame(); // 儲存存檔
    bool loadGame(); // 載入存檔
    bool hasSaveFile() const; // 檢查是否存在存檔
    void displayLevelStartMessage();
    void displayVictoryScreen();
    void displayDefeatScreen();
    void draftCardsPhase();
    void playBossWarningAnimation();
    void displayStoryDialogue(const std::string& character, const std::vector<std::string>& lines);
    void selectStartingLevelPhase();
public:
    Game();
    void run();
};

#endif // GAME_H
