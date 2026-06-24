#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <functional>
#include <string>
#include "Card.h"
#include "Character.h"

class Player : public Character {
private:
    int sp;
    int maxSp;
    bool isCountering;

    std::vector<Card> deck;
    std::vector<Card> hand;
    std::vector<Card> discardPile;

public:
    Player(int hp = 80, int maxHp = 80, int sp = 7, int maxSp = 10);

    static Card createCardByName(const std::string& name);

    // 狀態存取
    int getSp() const;
    int getMaxSp() const;
    bool getIsCountering() const;

    void setSp(int sp);
    void setIsCountering(bool state);

    // 效果修改器
    void gainSP(int amount);
    bool useSP(int amount);
    void gainArmor(int amount);
    void heal(int amount);
    void gainMaxHP(int amount);

    // 卡牌管理
    void initStartingDeck(bool forceAllCards = false);
    void shuffleDeck();
    void addCardToDeck(const Card& card);
    void setDeckState(const std::vector<Card>& newDeck, const std::vector<Card>& newHand, const std::vector<Card>& newDiscard);
    void drawCards(int count);
    void discardHand();
    void playCard(int index);
    
    const std::vector<Card>& getHand() const;
    const std::vector<Card>& getDeck() const;
    const std::vector<Card>& getDiscardPile() const;

    // 回合結束狀態重置 (例如護盾清零、反擊狀態重置)
    void resetTurnState() override;
};

#endif // PLAYER_H
