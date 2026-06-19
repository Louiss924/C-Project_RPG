#include "Player.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <windows.h>

Player::Player(int hp, int maxHp, int sp, int maxSp)
    : hp(hp), maxHp(maxHp), sp(sp), maxSp(maxSp), armor(0), isCountering(false), isStunned(false) {}

int Player::getHp() const { return hp; }
int Player::getMaxHp() const { return maxHp; }
int Player::getSp() const { return sp; }
int Player::getMaxSp() const { return maxSp; }
int Player::getArmor() const { return armor; }
bool Player::getIsCountering() const { return isCountering; }
bool Player::getIsStunned() const { return isStunned; }

void Player::setHp(int newHp) {
    hp = newHp;
    if (hp > maxHp) hp = maxHp;
    if (hp < 0) hp = 0;
}

void Player::setMaxHp(int newMaxHp) {
    maxHp = newMaxHp;
    if (hp > maxHp) hp = maxHp;
}

void Player::setSp(int newSp) {
    sp = newSp;
    if (sp > maxSp) sp = maxSp;
    if (sp < 0) sp = 0;
}

void Player::setArmor(int newArmor) {
    armor = newArmor;
    if (armor < 0) armor = 0;
}

void Player::setIsCountering(bool state) { isCountering = state; }
void Player::setIsStunned(bool state) { isStunned = state; }

void Player::gainSP(int amount) {
    sp = std::min(sp + amount, maxSp);
}

bool Player::useSP(int amount) {
    if (sp >= amount) {
        sp -= amount;
        return true;
    }
    return false;
}

void Player::gainArmor(int amount) {
    armor += amount;
}

void Player::heal(int amount) {
    hp = std::min(hp + amount, maxHp);
}

void Player::gainMaxHP(int amount) {
    maxHp += amount;
    hp += amount;
}

void Player::takeDamage(int damage, bool isTrueDamage, std::function<void()> drawCallback) {
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

void Player::initStartingDeck(bool forceAllCards) {
    deck.clear();
    hand.clear();
    discardPile.clear();

    if (forceAllCards) {
        // 每種卡牌精確各 1 張 (共 10 種)
        deck.push_back(Card("重擊", 1, CardEffectType::DAMAGE, 8, "造成 8 點傷害"));
        deck.push_back(Card("防禦", 1, CardEffectType::DEFEND, 6, "獲得 6 點護盾"));
        deck.push_back(Card("護盾", 1, CardEffectType::DEFEND, 5, "獲得 5 點護盾（無法防住真實傷害）"));
        deck.push_back(Card("治療術", 2, CardEffectType::HEAL, 10, "回復 10 點生命值"));
        deck.push_back(Card("反擊姿態", 2, CardEffectType::COUNTER, 50, "反擊狀態：受到傷害時反彈 50% 給怪物"));
        deck.push_back(Card("生命繁茂", 2, CardEffectType::MAX_HP_UP, 15, "最大生命值與當前生命值提升 15 點"));
        deck.push_back(Card("電擊術", 3, CardEffectType::STUN, 1, "電暈怪物，使其下一回合眩暈無法行動"));
        deck.push_back(Card("迅捷連擊", 2, CardEffectType::MULTI_DAMAGE, 4, "快速連擊 3 次，每次造成 4 點連擊傷害"));
        deck.push_back(Card("貫穿擊", 1, CardEffectType::TRUE_DAMAGE, 8, "造成 8 點真實傷害（無視怪物護盾）"));
        deck.push_back(Card("破甲重錘", 2, CardEffectType::BREAK_ARMOR_DAMAGE, 7, "粉碎怪物全部護盾，並造成 7 點傷害"));
    } else {
        // 4張 攻擊 (1 SP, 8 傷害)
        for (int i = 0; i < 4; ++i) {
            deck.push_back(Card("重擊", 1, CardEffectType::DAMAGE, 8, "造成 8 點傷害"));
        }
        // 3張 防禦 (1 SP, 6 護盾)
        for (int i = 0; i < 3; ++i) {
            deck.push_back(Card("防禦", 1, CardEffectType::DEFEND, 6, "獲得 6 點護盾"));
        }
        // 2張 治療 (2 SP, 10 回復)
        for (int i = 0; i < 2; ++i) {
            deck.push_back(Card("治療術", 2, CardEffectType::HEAL, 10, "回復 10 點生命值"));
        }
        // 2張 反擊 (2 SP, 反擊姿勢)
        for (int i = 0; i < 2; ++i) {
            deck.push_back(Card("反擊姿態", 2, CardEffectType::COUNTER, 50, "反擊狀態：受到傷害時反彈 50% 給怪物"));
        }
        // 1張 生命上限提升 (2 SP, +15 MaxHP)
        deck.push_back(Card("生命繁茂", 2, CardEffectType::MAX_HP_UP, 15, "最大生命值與當前生命值提升 15 點"));
        // 1張 眩暈 (3 SP, 電暈)
        deck.push_back(Card("電擊術", 3, CardEffectType::STUN, 1, "電暈怪物，使其下一回合眩暈無法行動"));
        // 2張 護盾 (1 SP, 5 護盾)
        for (int i = 0; i < 2; ++i) {
            deck.push_back(Card("護盾", 1, CardEffectType::DEFEND, 5, "獲得 5 點護盾（無法防住真實傷害）"));
        }
        // 各 1 張新攻擊牌
        deck.push_back(Card("迅捷連擊", 2, CardEffectType::MULTI_DAMAGE, 4, "快速連擊 3 次，每次造成 4 點連擊傷害"));
        deck.push_back(Card("貫穿擊", 1, CardEffectType::TRUE_DAMAGE, 8, "造成 8 點真實傷害（無視怪物護盾）"));
        deck.push_back(Card("破甲重錘", 2, CardEffectType::BREAK_ARMOR_DAMAGE, 7, "粉碎怪物全部護盾，並造成 7 點傷害"));
    }

    shuffleDeck();
}

void Player::shuffleDeck() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void Player::addCardToDeck(const Card& card) {
    deck.push_back(card);
}

void Player::setDeck(const std::vector<Card>& newDeck) {
    deck = newDeck;
    hand.clear();
    discardPile.clear();
}

void Player::drawCards(int count) {
    for (int i = 0; i < count; ++i) {
        if (deck.empty()) {
            if (discardPile.empty()) {
                break;
            }
            deck = discardPile;
            discardPile.clear();
            shuffleDeck();
        }
        hand.push_back(deck.back());
        deck.pop_back();
    }
}

void Player::discardHand() {
    for (const auto& card : hand) {
        discardPile.push_back(card);
    }
    hand.clear();
}

void Player::playCard(int index) {
    if (index >= 0 && index < static_cast<int>(hand.size())) {
        discardPile.push_back(hand[index]);
        hand.erase(hand.begin() + index);
    }
}

const std::vector<Card>& Player::getHand() const { return hand; }
const std::vector<Card>& Player::getDeck() const { return deck; }
const std::vector<Card>& Player::getDiscardPile() const { return discardPile; }

void Player::resetTurnState() {
    armor = 0;
    isCountering = false;
}

Card Player::createCardByName(const std::string& name) {
    if (name == "重擊") {
        return Card("重擊", 1, CardEffectType::DAMAGE, 8, "造成 8 點傷害");
    } else if (name == "防禦") {
        return Card("防禦", 1, CardEffectType::DEFEND, 6, "獲得 6 點護盾");
    } else if (name == "護盾") {
        return Card("護盾", 1, CardEffectType::DEFEND, 5, "獲得 5 點護盾（無法防住真實傷害）");
    } else if (name == "治療術") {
        return Card("治療術", 2, CardEffectType::HEAL, 10, "回復 10 點生命值");
    } else if (name == "反擊姿態") {
        return Card("反擊姿態", 2, CardEffectType::COUNTER, 50, "反擊狀態：受到傷害時反彈 50% 給怪物");
    } else if (name == "生命繁茂") {
        return Card("生命繁茂", 2, CardEffectType::MAX_HP_UP, 15, "最大生命值與當前生命值提升 15 點");
    } else if (name == "電擊術") {
        return Card("電擊術", 3, CardEffectType::STUN, 1, "電暈怪物，使其下一回合眩暈無法行動");
    } else if (name == "迅捷連擊") {
        return Card("迅捷連擊", 2, CardEffectType::MULTI_DAMAGE, 4, "快速連擊 3 次，每次造成 4 點連擊傷害");
    } else if (name == "貫穿擊") {
        return Card("貫穿擊", 1, CardEffectType::TRUE_DAMAGE, 8, "造成 8 點真實傷害（無視怪物護盾）");
    } else if (name == "破甲重錘") {
        return Card("破甲重錘", 2, CardEffectType::BREAK_ARMOR_DAMAGE, 7, "粉碎怪物全部護盾，並造成 7 點傷害");
    }
    // 預設防錯回傳
    return Card("重擊", 1, CardEffectType::DAMAGE, 8, "造成 8 點傷害");
}
