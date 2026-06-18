#ifndef CARD_H
#define CARD_H

#include <string>

enum class CardEffectType {
    DAMAGE,      // 造成傷害
    HEAL,        // 回復血量
    DEFEND,      // 增加護盾
    COUNTER,     // 反擊狀態附加
    MAX_HP_UP,   // 提升最大生命上限
    STUN         // 怪物電暈 (眩暈)
};

class Card {
private:
    std::string name;
    int spCost;
    CardEffectType effectType;
    int value;
    std::string description;

public:
    Card(std::string name, int spCost, CardEffectType effectType, int value, std::string description);
    
    std::string getName() const;
    int getSpCost() const;
    CardEffectType getEffectType() const;
    int getValue() const;
    std::string getDescription() const;
    
    std::string getEffectTypeName() const;
};

#endif // CARD_H
