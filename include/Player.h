#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <functional>
#include <string>
#include "Card.h"

class Player {
private:
    int hp;
    int maxHp;
    int sp;
    int maxSp;
    int armor;
    bool isCountering;
    bool isStunned;

    std::vector<Card> deck;
    std::vector<Card> hand;
    std::vector<Card> discardPile;

public:
    Player(int hp = 80, int maxHp = 80, int sp = 3, int maxSp = 10);

    // 狀態存取
    int getHp() const;
    int getMaxHp() const;
    int getSp() const;
    int getMaxSp() const;
    int getArmor() const;
    bool getIsCountering() const;
    bool getIsStunned() const;

    void setHp(int hp);
    void setMaxHp(int maxHp);
    void setSp(int sp);
    void setArmor(int armor);
    void setIsCountering(bool state);
    void setIsStunned(bool state);

    // 效果修改器
    void gainSP(int amount);
    bool useSP(int amount);
    void gainArmor(int amount);
    void heal(int amount);
    void gainMaxHP(int amount);

    // 受到傷害 (包含護盾扣減與血條逐點扣減動畫)
    void takeDamage(int damage, bool isTrueDamage = false, std::function<void()> drawCallback = nullptr);
    // 卡牌管理
    void initStartingDeck();
    void shuffleDeck();
    void drawCards(int count);
    void discardHand();
    void playCard(int index);
    
    const std::vector<Card>& getHand() const;
    const std::vector<Card>& getDeck() const;
    const std::vector<Card>& getDiscardPile() const;

    // 回合結束狀態重置 (例如護盾清零、反擊狀態重置)
    void resetTurnState();
};

#endif // PLAYER_H
