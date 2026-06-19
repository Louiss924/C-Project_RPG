#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Monster.h"
#include <string>

class Battle {
private:
    Player& player;
    Monster& monster;
    int cursorIndex;
    std::string actionLog;
    bool isPlayerTurn;
    bool isBattleOver;
    bool isPlayerVictor;

    void drawUI();
    void handleInput();
    void executePlayerAction();
    void executeMonsterTurn();
    void showActionMessage(const std::string& msg);
    std::string getHealthBar(int hp, int maxHp, int length = 20) const;
    static int getUTF8DisplayWidth(const std::string& str);
    static std::string padUTF8Text(const std::string& text, int targetWidth);

public:
    Battle(Player& player, Monster& monster);
    
    // 開始戰鬥，回傳玩家是否獲勝
    bool start(bool forceAllCards = false);
};

#endif // BATTLE_H
