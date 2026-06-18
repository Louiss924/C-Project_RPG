#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
private:
    Player player;
    int currentLevel;
    int currentRound;
    void displayLevelStartMessage();
    void displayVictoryScreen();
    void displayDefeatScreen();
    void draftCardsPhase();
    void playBossWarningAnimation();
public:
    Game();
    void run();
};

#endif // GAME_H
