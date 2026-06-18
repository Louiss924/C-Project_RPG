#include "Card.h"

Card::Card(std::string name, int spCost, CardEffectType effectType, int value, std::string description)
    : name(name), spCost(spCost), effectType(effectType), value(value), description(description) {}

std::string Card::getName() const {
    return name;
}

int Card::getSpCost() const {
    return spCost;
}

CardEffectType Card::getEffectType() const {
    return effectType;
}

int Card::getValue() const {
    return value;
}

std::string Card::getDescription() const {
    return description;
}

std::string Card::getEffectTypeName() const {
    switch (effectType) {
        case CardEffectType::DAMAGE: return "傷害";
        case CardEffectType::HEAL: return "回復";
        case CardEffectType::DEFEND: return "防禦";
        case CardEffectType::COUNTER: return "反擊";
        case CardEffectType::MAX_HP_UP: return "最大生命值提升";
        case CardEffectType::STUN: return "眩暈";
        default: return "未知";
    }
}
