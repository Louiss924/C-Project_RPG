#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>
#include <functional>

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

class Monster {
private:
    std::string name;
    int hp;
    int maxHp;
    int armor;
    bool isStunned;
    
    std::vector<MonsterMove> moves;
    MonsterMove nextMove;

public:
    Monster(std::string name, int hp, int maxHp, const std::vector<MonsterMove>& moves);
    
    std::string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getArmor() const;
    bool getIsStunned() const;
    MonsterMove getNextMove() const;
    
    void setHp(int hp);
    void setArmor(int armor);
    void setIsStunned(bool state);
    
    // 受到傷害 (包含護盾扣減與血條逐點扣減動畫)
    void takeDamage(int damage, bool isTrueDamage = false, std::function<void()> drawCallback = nullptr);
    
    // 隨機決定下一回合意圖
    void rollIntent();
    
    // 清除護盾等回合結束邏輯
    void resetTurnState();
};

#endif // MONSTER_H
