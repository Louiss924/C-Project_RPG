#include "Battle.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <algorithm>
#include <windows.h>

Battle::Battle(Player& player, Monster& monster)
    : player(player), monster(monster), cursorIndex(0), 
      actionLog("戰鬥開始！請選擇你的行動。"), isPlayerTurn(true), 
      isBattleOver(false), isPlayerVictor(false) {}

std::string Battle::getHealthBar(int hp, int maxHp, int length) const {
    if (maxHp <= 0) return "";
    int filled = (hp * length) / maxHp;
    if (filled < 0) filled = 0;
    if (filled > length) filled = length;
    
    std::string bar = "";
    for (int i = 0; i < filled; ++i) {
        bar += "■"; // 實心
    }
    for (int i = filled; i < length; ++i) {
        bar += "□"; // 空心
    }
    return bar;
}

void Battle::drawUI() {
    system("cls");
    
    std::cout << "==========================================================" << std::endl;
    // 1. 怪物意圖預告區
    if (monster.getHp() <= 0) {
        std::cout << "【怪物意圖】怪物已死亡" << std::endl;
    } else if (monster.getIsStunned()) {
        std::cout << "【怪物意圖】" << monster.getName() << " 下回合將 [眩暈無法行動]" << std::endl;
    } else {
        std::cout << "【怪物意圖】" << monster.getName() << " 下回合將使用 [" 
                  << monster.getNextMove().name << "]，預估傷害: " 
                  << monster.getNextMove().damage;
        if (monster.getNextMove().armorGain > 0) {
            std::cout << "，護盾加值: " << monster.getNextMove().armorGain;
        }
        std::cout << std::endl;
    }
    std::cout << "==========================================================" << std::endl;
    std::cout << std::endl;
    
    // 2. 戰鬥主畫面 (怪物 & 玩家)
    std::cout << "  " << monster.getName() << " (怪物)" << std::endl;
    std::cout << "  HP: [" << getHealthBar(monster.getHp(), monster.getMaxHp()) << "] " 
              << monster.getHp() << " / " << monster.getMaxHp();
    if (monster.getArmor() > 0) {
        std::cout << " (護盾: " << monster.getArmor() << ")";
    }
    if (monster.getIsStunned()) {
        std::cout << " [眩暈]";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "  玩家 (勇者)" << std::endl;
    std::cout << "  HP: [" << getHealthBar(player.getHp(), player.getMaxHp()) << "] " 
              << player.getHp() << " / " << player.getMaxHp();
    if (player.getArmor() > 0) {
        std::cout << " (護盾: " << player.getArmor() << ")";
    }
    if (player.getIsCountering()) {
        std::cout << " [反擊姿勢]";
    }
    std::cout << std::endl;
    
    std::cout << "  SP: ";
    for (int i = 0; i < player.getMaxSp(); ++i) {
        if (i < player.getSp()) {
            std::cout << "◆"; // 實心能量
        } else {
            std::cout << "◇"; // 空心能量
        }
    }
    std::cout << " (" << player.getSp() << " / " << player.getMaxSp() << ")" << std::endl;
    std::cout << std::endl;
    std::cout << "==========================================================" << std::endl;
    
    // 3. 戰鬥日誌區
    std::cout << "【戰鬥日誌】" << std::endl;
    std::cout << "  " << actionLog << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << std::endl;
    
    // 4. 手牌與動作選擇區
    if (isPlayerTurn && !isBattleOver) {
        std::cout << "【手牌與動作】(使用 ↑/↓ 方向鍵移動，Enter 鍵確認出牌)" << std::endl;
        
        // Option 0: 普通攻擊
        if (cursorIndex == 0) {
            std::cout << " > [普通攻擊] (消耗: 0 SP) | 造成 5 點傷害，回復 1 點 SP" << std::endl;
        } else {
            std::cout << "   [普通攻擊] (消耗: 0 SP) | 造成 5 點傷害，回復 1 點 SP" << std::endl;
        }
        
        // Option 1..N: 手牌
        const auto& hand = player.getHand();
        for (int i = 0; i < static_cast<int>(hand.size()); ++i) {
            int optionId = i + 1;
            const auto& card = hand[i];
            if (cursorIndex == optionId) {
                std::cout << " > [" << card.getName() << "] (消耗: " << card.getSpCost() << " SP) | "
                          << card.getDescription() << std::endl;
            } else {
                std::cout << "   [" << card.getName() << "] (消耗: " << card.getSpCost() << " SP) | "
                          << card.getDescription() << std::endl;
            }
        }
        std::cout << "==========================================================" << std::endl;
    } else {
        std::cout << "【等待中...】正在處理回合行動..." << std::endl;
        std::cout << "==========================================================" << std::endl;
    }
}

void Battle::showActionMessage(const std::string& msg) {
    actionLog = msg;
    drawUI();
    Sleep(1000);
    // 清除期間的鍵盤輸入，避免玩家搶按
    while (_kbhit()) {
        _getch();
    }
}

void Battle::handleInput() {
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        int next_ch = _getch();
        if (next_ch == 72) { // 方向鍵上
            cursorIndex--;
            if (cursorIndex < 0) {
                cursorIndex = player.getHand().size();
            }
            drawUI();
        } else if (next_ch == 80) { // 方向鍵下
            cursorIndex++;
            if (cursorIndex > static_cast<int>(player.getHand().size())) {
                cursorIndex = 0;
            }
            drawUI();
        }
    } else if (ch == 13 || ch == 10) { // Enter 鍵
        executePlayerAction();
    }
    // 忽略數字鍵及其他非方向鍵/Enter鍵輸入
}

void Battle::executePlayerAction() {
    if (cursorIndex == 0) {
        // 普通攻擊
        showActionMessage("▶ 玩家使用了 [普通攻擊]，對怪物造成 5 點傷害，並回復 1 點 SP！");
        monster.takeDamage(5, false, [this]() { this->drawUI(); });
        player.gainSP(1);
        
        if (monster.getHp() <= 0) {
            isBattleOver = true;
            isPlayerVictor = true;
            return;
        }
        
        isPlayerTurn = false;
    } else {
        int cardIdx = cursorIndex - 1;
        const Card& card = player.getHand()[cardIdx];
        
        if (player.getSp() < card.getSpCost()) {
            // SP不足
            actionLog = "❌ 能量（SP）不足，無法使用該卡牌！";
            drawUI();
            return;
        }
        
        // 扣除 SP
        player.useSP(card.getSpCost());
        
        // 根據效果類型執行
        std::string logMsg = "▶ 玩家打出 [" + card.getName() + "]，";
        CardEffectType type = card.getEffectType();
        int val = card.getValue();
        
        if (type == CardEffectType::DAMAGE) {
            logMsg += "對怪物造成 " + std::to_string(val) + " 點傷害！";
            showActionMessage(logMsg);
            monster.takeDamage(val, false, [this]() { this->drawUI(); });
        } else if (type == CardEffectType::HEAL) {
            logMsg += "回復自身 " + std::to_string(val) + " 點生命值！";
            showActionMessage(logMsg);
            player.heal(val);
        } else if (type == CardEffectType::DEFEND) {
            logMsg += "獲得 " + std::to_string(val) + " 點護盾！";
            showActionMessage(logMsg);
            player.gainArmor(val);
        } else if (type == CardEffectType::COUNTER) {
            logMsg += "進入反擊姿態！下回合將反彈受到的 50% 傷害。";
            showActionMessage(logMsg);
            player.setIsCountering(true);
        } else if (type == CardEffectType::MAX_HP_UP) {
            logMsg += "生命上限與當前生命值提升 " + std::to_string(val) + " 點！";
            showActionMessage(logMsg);
            player.gainMaxHP(val);
        } else if (type == CardEffectType::STUN) {
            logMsg += "電暈了怪物！使其下回合眩暈無法行動。";
            showActionMessage(logMsg);
            monster.setIsStunned(true);
        }
        
        // 棄置卡牌
        player.playCard(cardIdx);
        
        // 游標位置重置與範圍調整
        cursorIndex = 0;
        
        if (monster.getHp() <= 0) {
            isBattleOver = true;
            isPlayerVictor = true;
            return;
        }
        
        isPlayerTurn = false;
    }
}

void Battle::executeMonsterTurn() {
    if (monster.getIsStunned()) {
        showActionMessage("▶ 怪物 [" + monster.getName() + "] 處於眩暈狀態，本回合無法行動！");
        monster.setIsStunned(false);
    } else {
        MonsterMove move = monster.getNextMove();
        
        // 怪物先獲得護盾（如果有）
        if (move.armorGain > 0) {
            showActionMessage("▶ 怪物 [" + monster.getName() + "] 使用 [" + move.name + "]，獲得了 " + std::to_string(move.armorGain) + " 點護盾！");
            monster.setArmor(move.armorGain);
        }
        
        // 怪物造成傷害
        if (move.damage > 0) {
            std::string attackMsg = "▶ 怪物 [" + monster.getName() + "] 使用 [" + move.name + "]，對玩家造成 " + std::to_string(move.damage) + " 點傷害！";
            showActionMessage(attackMsg);
            
            int originalHp = player.getHp();
            int originalArmor = player.getArmor();
            
            player.takeDamage(move.damage, move.isTrueDamage, [this]() { this->drawUI(); });
            
            // 計算實際受到的扣血與護盾扣減
            int damageTaken = originalHp - player.getHp();
            // 反擊判斷 (根據扣除的血量加護盾扣除量，也就是怪物本來要造成的傷害，或者是扣血。
            // 規格書：將所受傷害的特定比例反彈。通常是以怪物的攻擊數值為準，我們以 move.damage 做反擊基數)
            if (player.getIsCountering()) {
                int counterDmg = move.damage * 0.5;
                if (counterDmg <= 0) counterDmg = 1; // 至少反彈 1 點
                
                showActionMessage("▶ 玩家觸發反擊！對怪物反彈了 " + std::to_string(counterDmg) + " 點傷害！");
                monster.takeDamage(counterDmg, false, [this]() { this->drawUI(); });
            }
        } else if (move.armorGain == 0) {
            // 其他招式 (例如純蓄力或防守)
            showActionMessage("▶ 怪物 [" + monster.getName() + "] 使用 [" + move.name + "]：" + move.description);
        }
    }
    
    if (player.getHp() <= 0) {
        isBattleOver = true;
        isPlayerVictor = false;
        return;
    }
    
    if (monster.getHp() <= 0) {
        isBattleOver = true;
        isPlayerVictor = true;
        return;
    }
    
    // 回合結束重置
    player.resetTurnState();
    monster.resetTurnState();
    
    // 棄牌並抽 5 張新牌
    player.discardHand();
    player.drawCards(5);
    
    // 怪物決定下回合招式
    monster.rollIntent();
    
    // 游標重置，回歸玩家回合
    cursorIndex = 0;
    isPlayerTurn = true;
    actionLog = "你的回合。請選擇你的行動。";
}

bool Battle::start(bool forceAllCards) {
    if (forceAllCards) {
        player.initStartingDeck(true);
        player.drawCards(player.getDeck().size());
    } else {
        // 玩家不會重新獲得/重置牌組，而是直接繼承並保留前一回合結束時的牌組（包含所有血量與卡牌狀態）。
        // 且玩家不用洗牌，所以在此不做任何洗牌與抽牌動作，直接使用現有的卡牌狀態。
    }
    
    // 初始化怪物意圖
    monster.rollIntent();
    
    cursorIndex = 0;
    isPlayerTurn = true;
    isBattleOver = false;
    isPlayerVictor = false;
    actionLog = "戰鬥開始！請選擇你的行動。";
    
    drawUI();
    
    while (!isBattleOver) {
        if (isPlayerTurn) {
            handleInput();
        } else {
            executeMonsterTurn();
            if (!isBattleOver) {
                drawUI();
            }
        }
    }
    
    // 結算畫面
    if (isPlayerVictor) {
        showActionMessage("🎉 戰鬥勝利！擊敗了 " + monster.getName() + "！");
        return true;
    } else {
        showActionMessage("💀 戰鬥失敗...你被 " + monster.getName() + " 擊敗了。");
        return false;
    }
}
