#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>
#include <functional>
#include "Character.h"

struct MonsterMove {
    std::string name;
    int damage;
    int armorGain; // 招式是否獲得護盾
    std::string description;
    bool isTrueDamage;
    int hits;
    int drainSp;
    bool stunsPlayer;

    MonsterMove(std::string name = "", int damage = 0, int armorGain = 0, std::string description = "", bool isTrueDamage = false, int hits = 1, int drainSp = 0, bool stunsPlayer = false)
        : name(name), damage(damage), armorGain(armorGain), description(description), isTrueDamage(isTrueDamage), hits(hits), drainSp(drainSp), stunsPlayer(stunsPlayer) {}
};

class Monster : public Character {
private:
    std::vector<MonsterMove> moves;
    MonsterMove nextMove;

public:
    Monster(std::string name, int hp, int maxHp, const std::vector<MonsterMove>& moves);
    
    MonsterMove getNextMove() const;
    
    // 隨機決定下一回合意圖
    void rollIntent();
};

#endif // MONSTER_H
