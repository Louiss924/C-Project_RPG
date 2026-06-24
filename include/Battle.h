#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Monster.h"
#include <string>
#include <vector>

class Battle {
private:
    Player& player;
    Monster& monster;
    int cursorIndex;
    std::vector<std::string> actionLogs;
    bool isPlayerTurn;
    bool isBattleOver;
    bool isPlayerVictor;
    int level;

    void drawUI();
    void handleInput();
    void executePlayerAction();
    void executeMonsterTurn();
    void showActionMessage(const std::string& msg);
    std::string getHealthBar(int hp, int maxHp, int length = 20) const;
    static int getUTF8DisplayWidth(const std::string& str);
    static std::string padUTF8Text(const std::string& text, int targetWidth);
    std::vector<std::string> getMonsterASCIIArt(const std::string& name) const;
    std::string getMonsterColor(const std::string& name) const;
    void addLog(const std::string& msg);



public:
    Battle(Player& player, Monster& monster, int level = 1);
    
    // 開始戰鬥，回傳玩家是否獲勝
    bool start(bool forceAllCards = false);
};

#endif // BATTLE_H
