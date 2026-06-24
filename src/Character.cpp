#include "Character.h"
#include <windows.h>
#include <algorithm>

Character::Character(std::string name, int hp, int maxHp)
    : name(name), hp(hp), maxHp(maxHp), armor(0), isStunned(false) {}

std::string Character::getName() const { return name; }
int Character::getHp() const { return hp; }
int Character::getMaxHp() const { return maxHp; }
int Character::getArmor() const { return armor; }
bool Character::getIsStunned() const { return isStunned; }

void Character::setHp(int newHp) {
    hp = newHp;
    if (hp > maxHp) hp = maxHp;
    if (hp < 0) hp = 0;
}

void Character::setMaxHp(int newMaxHp) {
    maxHp = newMaxHp;
    if (hp > maxHp) hp = maxHp;
}

void Character::setArmor(int newArmor) {
    armor = newArmor;
    if (armor < 0) armor = 0;
}

void Character::setIsStunned(bool state) {
    isStunned = state;
}

void Character::takeDamage(int damage, bool isTrueDamage, std::function<void()> drawCallback) {
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

void Character::resetTurnState() {
    armor = 0;
}
