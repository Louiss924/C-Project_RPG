#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <functional>

class Character {
protected:
    std::string name;
    int hp;
    int maxHp;
    int armor;
    bool isStunned;

public:
    Character(std::string name, int hp, int maxHp);
    virtual ~Character() = default;

    std::string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getArmor() const;
    bool getIsStunned() const;

    void setHp(int hp);
    void setMaxHp(int maxHp);
    void setArmor(int armor);
    void setIsStunned(bool state);

    virtual void takeDamage(int damage, bool isTrueDamage = false, std::function<void()> drawCallback = nullptr);
    virtual void resetTurnState();
};

#endif // CHARACTER_H
