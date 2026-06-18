#include "Monster.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <windows.h>

Monster::Monster(std::string name, int hp, int maxHp, const std::vector<MonsterMove>& moves)
    : name(name), hp(hp), maxHp(maxHp), armor(0), isStunned(false), moves(moves) {
    rollIntent();
}

std::string Monster::getName() const { return name; }
int Monster::getHp() const { return hp; }
int Monster::getMaxHp() const { return maxHp; }
int Monster::getArmor() const { return armor; }
bool Monster::getIsStunned() const { return isStunned; }
MonsterMove Monster::getNextMove() const { return nextMove; }

void Monster::setHp(int newHp) {
    hp = newHp;
    if (hp > maxHp) hp = maxHp;
    if (hp < 0) hp = 0;
}

void Monster::setArmor(int newArmor) {
    armor = newArmor;
    if (armor < 0) armor = 0;
}

void Monster::setIsStunned(bool state) { isStunned = state; }
void Monster::takeDamage(int damage, bool isTrueDamage, std::function<void()> drawCallback) {
    int actualDamage = damage;
    if (!isTrueDamage && armor > 0) {
        if (actualDamage <= armor) {
            armor -= actualDamage;
            actualDamage = 0;
        } else {
            actualDamage -= armor;
            armor = 0;
        }
        if (drawCallback) {
            drawCallback();
            Sleep(80);
        }
    }

    if (actualDamage > 0) {
        for (int i = 0; i < actualDamage; ++i) {
            if (hp > 0) {
                hp--;
                if (drawCallback) {
                    drawCallback();
                    Sleep(80);
                }
            } else {
                break;
            }
        }
    }
}

void Monster::rollIntent() {
    if (moves.empty()) {
        nextMove = {"撞擊", 5, 0, "對目標造成 5 點傷害"};
        return;
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, moves.size() - 1);
    int index = distribution(generator);
    nextMove = moves[index];
}

void Monster::resetTurnState() {
    armor = 0;
}
