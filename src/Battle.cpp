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

int Battle::getUTF8DisplayWidth(const std::string& str) {
    int width = 0;
    size_t i = 0;
    while (i < str.length()) {
        unsigned char c = str[i];
        if (c < 0x80) {
            width += 1;
            i += 1;
        } else if ((c & 0xE0) == 0xC0) {
            width += 1;
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            width += 2;
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            width += 2;
            i += 4;
        } else {
            i += 1;
        }
    }
    return width;
}

std::string Battle::padUTF8Text(const std::string& text, int targetWidth) {
    int currentWidth = getUTF8DisplayWidth(text);
    if (currentWidth >= targetWidth) {
        return text;
    }
    int totalPadding = targetWidth - currentWidth;
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;
    
    std::string result = "";
    for (int i = 0; i < leftPadding; ++i) {
        result += " ";
    }
    result += text;
    for (int i = 0; i < rightPadding; ++i) {
        result += " ";
    }
    return result;
}

static std::string getCardShortDesc(const std::string& name) {
    if (name == "重擊") return "造成 8 點傷害";
    if (name == "防禦") return "獲得 6 點護盾";
    if (name == "護盾") return "獲得 5 點護盾";
    if (name == "治療術") return "回復 10 生命";
    if (name == "反擊姿態") return "反擊 50% 傷害";
    if (name == "生命繁茂") return "生命與上限 +15";
    if (name == "電擊術") return "眩暈怪物 1回合";
    if (name == "迅捷連擊") return "連擊 3次 x 4傷";
    if (name == "貫穿擊") return "8 點真實傷害";
    if (name == "破甲重錘") return "破盾並造成 7傷";
    return "";
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
        std::cout << "【手牌與動作】(使用方向鍵移動，Enter 鍵確認出牌/行動)" << std::endl;
        
        const auto& hand = player.getHand();
        int totalOptions = hand.size() + 1; // 普通攻擊 + 手牌
        for (int startIdx = 0; startIdx < totalOptions; startIdx += 5) {
            int endIdx = std::min(startIdx + 5, totalOptions);
            
            // 第一行：頂框
            for (int i = startIdx; i < endIdx; ++i) {
                bool isSelected = (cursorIndex == i);
                if (isSelected) {
                    std::cout << "*==============*";
                } else {
                    std::cout << ".--------------.";
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第二行：卡牌名稱
            for (int i = startIdx; i < endIdx; ++i) {
                bool isSelected = (cursorIndex == i);
                std::string nameStr;
                if (i == 0) {
                    nameStr = isSelected ? "* 普通攻擊 *" : "普通攻擊";
                } else {
                    const auto& card = hand[i - 1];
                    nameStr = isSelected ? ("* " + card.getName() + " *") : card.getName();
                }
                std::string paddedName = padUTF8Text(nameStr, 14);
                if (isSelected) {
                    std::cout << "*" << paddedName << "*";
                } else {
                    std::cout << "|" << paddedName << "|";
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第三行：能量消耗/效果
            for (int i = startIdx; i < endIdx; ++i) {
                bool isSelected = (cursorIndex == i);
                std::string spStr;
                if (i == 0) {
                    spStr = "回復: 1 SP";
                } else {
                    const auto& card = hand[i - 1];
                    spStr = "消耗: " + std::to_string(card.getSpCost()) + " SP";
                }
                std::string paddedSp = padUTF8Text(spStr, 14);
                if (isSelected) {
                    std::cout << "*" << paddedSp << "*";
                } else {
                    std::cout << "|" << paddedSp << "|";
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第四行：效果描述
            for (int i = startIdx; i < endIdx; ++i) {
                bool isSelected = (cursorIndex == i);
                std::string desc;
                if (i == 0) {
                    desc = "造成 5 點傷害";
                } else {
                    const auto& card = hand[i - 1];
                    desc = getCardShortDesc(card.getName());
                }
                std::string paddedDesc = padUTF8Text(desc, 14);
                if (isSelected) {
                    std::cout << "*" << paddedDesc << "*";
                } else {
                    std::cout << "|" << paddedDesc << "|";
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第五行：底框
            for (int i = startIdx; i < endIdx; ++i) {
                bool isSelected = (cursorIndex == i);
                if (isSelected) {
                    std::cout << "*==============*";
                } else {
                    std::cout << "'--------------'";
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 卡牌行間隔
            std::cout << std::endl;
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
        if (next_ch == 72 || next_ch == 75) { // 方向鍵上 或 左
            cursorIndex--;
            if (cursorIndex < 0) {
                cursorIndex = player.getHand().size();
            }
            drawUI();
        } else if (next_ch == 80 || next_ch == 77) { // 方向鍵下 或 右
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
        } else if (type == CardEffectType::TRUE_DAMAGE) {
            logMsg += "對怪物造成 " + std::to_string(val) + " 點真實傷害（穿透護盾）！";
            showActionMessage(logMsg);
            monster.takeDamage(val, true, [this]() { this->drawUI(); });
        } else if (type == CardEffectType::BREAK_ARMOR_DAMAGE) {
            logMsg += "一擊粉碎了怪物的護盾，並造成 " + std::to_string(val) + " 點傷害！";
            showActionMessage(logMsg);
            monster.setArmor(0);
            monster.takeDamage(val, false, [this]() { this->drawUI(); });
        } else if (type == CardEffectType::MULTI_DAMAGE) {
            for (int i = 0; i < 3; ++i) {
                std::string hitMsg = "▶ 玩家打出 [" + card.getName() + "] (第 " + std::to_string(i + 1) + " 連擊)，對怪物造成 " + std::to_string(val) + " 點傷害！";
                showActionMessage(hitMsg);
                monster.takeDamage(val, false, [this]() { this->drawUI(); });
                if (monster.getHp() <= 0) {
                    break;
                }
            }
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
            int totalDamageDealt = 0;
            
            for (int h = 0; h < move.hits; ++h) {
                std::string hitSuffix = (move.hits > 1) ? (" (第 " + std::to_string(h + 1) + " 段)") : "";
                std::string attackMsg = "▶ 怪物 [" + monster.getName() + "] 使用 [" + move.name + "]" + hitSuffix + "，對玩家造成 " + std::to_string(move.damage) + " 點傷害！";
                showActionMessage(attackMsg);
                
                player.takeDamage(move.damage, move.isTrueDamage, [this]() { this->drawUI(); });
                totalDamageDealt += move.damage;
                
                if (player.getHp() <= 0) {
                    break;
                }
            }
            
            // 反擊判斷 (以本招總傷害為反彈基數)
            if (player.getIsCountering() && player.getHp() > 0) {
                int counterDmg = totalDamageDealt * 0.5;
                if (counterDmg <= 0) counterDmg = 1; // 至少反彈 1 點
                
                showActionMessage("▶ 玩家觸發反擊！對怪物反彈了 " + std::to_string(counterDmg) + " 點傷害！");
                monster.takeDamage(counterDmg, false, [this]() { this->drawUI(); });
            }
            
            // 扣減玩家 SP
            if (move.drainSp > 0 && player.getHp() > 0) {
                showActionMessage("▶ 玩家受到吸能影響，被扣減了 " + std::to_string(move.drainSp) + " 點 SP！");
                player.useSP(move.drainSp);
            }
            
            // 眩暈玩家
            if (move.stunsPlayer && player.getHp() > 0) {
                showActionMessage("▶ 玩家受到震撼打擊，下一回合將 [眩暈無法行動]！");
                player.setIsStunned(true);
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
    
    // 補抽牌至手牌有 5 張 (保留手牌，不丟棄)
    int currentHandSize = player.getHand().size();
    if (currentHandSize < 5) {
        player.drawCards(5 - currentHandSize);
    }
    
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
            if (player.getIsStunned()) {
                showActionMessage("▶ 勇者處於眩暈狀態，本回合無法行動！");
                player.setIsStunned(false);
                isPlayerTurn = false;
                if (!isBattleOver) {
                    drawUI();
                }
            } else {
                handleInput();
            }
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
