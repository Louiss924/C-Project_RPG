#include "Battle.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <algorithm>
#include <windows.h>
#include <random>

// ANSI Escape Codes for Colors
#define COLOR_RESET   "\x1b[0m"
#define COLOR_BOLD    "\x1b[1m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[37m"

// Bright/Light colors
#define COLOR_LRED    "\x1b[91m"
#define COLOR_LGREEN  "\x1b[92m"
#define COLOR_LYELLOW "\x1b[93m"
#define COLOR_LBLUE   "\x1b[94m"
#define COLOR_LMAGENTA "\x1b[95m"
#define COLOR_LCYAN   "\x1b[96m"


Battle::Battle(Player& player, Monster& monster, int level)
    : player(player), monster(monster), cursorIndex(0), 
      isPlayerTurn(true), isBattleOver(false), isPlayerVictor(false), level(level) {
    actionLogs.push_back("戰鬥開始！請選擇你的行動。");
}

void Battle::addLog(const std::string& msg) {
    actionLogs.push_back(msg);
    if (actionLogs.size() > 4) {
        actionLogs.erase(actionLogs.begin());
    }
}

std::vector<std::string> Battle::getMonsterASCIIArt(const std::string& name) const {
    if (name.find("史萊姆") != std::string::npos) {
        return {
            "      _.-._      ",
            "    .'     '.    ",
            "   /  ^   ^  \\   ",
            "  |   ( = )   |  ",
            "   '._     _.'   ",
            "      '---'      "
        };
    } else if (name.find("斥候") != std::string::npos) {
        return {
            "       /\\_/\\     ",
            "      (=*.*=)    ",
            "      / | | \\    ",
            "     (_/|_|\\_)   ",
            "      |  |  |    ",
            "                 "
        };
    } else if (name.find("酋長") != std::string::npos) {
        return {
            "       /\\_/\\     ",
            "      (=0.0=)    ",
            "     /|  Y  |\\   ",
            "    ( |_|_|_| )  ",
            "     /  / \\  \\   ",
            "    (__/   \\__)  "
        };
    } else if (name.find("火山蜥蜴") != std::string::npos) {
        return {
            "     ( `'^-'^ )  ",
            "      ) . . (    ",
            "     (  ___  )   ",
            "     /'-...-'\\   ",
            "    /   ___   \\  ",
            "   (_.-'   '-._) "
        };
    } else if (name.find("岩石巨人") != std::string::npos) {
        return {
            "     .---------. ",
            "    /  -   -   \\ ",
            "   |   [---]    |",
            "   |  #######  | ",
            "    \\_________/  ",
            "    /    |    \\  "
        };
    } else if (name.find("烈焰巨龍") != std::string::npos) {
        return {
            "        /\\_/\\    ",
            "      (( o o ))  ",
            "       \\ = = /   ",
            "       /  -  \\   ",
            "      / /| |\\ \\  ",
            "     (_/ |_| \\_) "
        };
    }
    return {
        "                 ",
        "                 ",
        "                 ",
        "                 ",
        "                 ",
        "                 "
    };
}

std::string Battle::getMonsterColor(const std::string& name) const {
    if (name.find("史萊姆") != std::string::npos) {
        return COLOR_LGREEN;
    } else if (name.find("斥候") != std::string::npos) {
        return COLOR_GREEN;
    } else if (name.find("酋長") != std::string::npos) {
        return COLOR_YELLOW;
    } else if (name.find("火山蜥蜴") != std::string::npos) {
        return COLOR_LMAGENTA;
    } else if (name.find("岩石巨人") != std::string::npos) {
        return COLOR_LCYAN;
    } else if (name.find("烈焰巨龍") != std::string::npos) {
        return COLOR_LRED;
    }
    return COLOR_WHITE;
}


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
        // 檢查並跳過 UTF-8 中的 Variation Selector-16 (U+FE0F): \xef\xb8\x8f
        if (i + 2 < str.length() && c == 0xEF && (unsigned char)str[i+1] == 0xB8 && (unsigned char)str[i+2] == 0x8F) {
            i += 3;
            continue;
        }
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
    auto getCardColor = [](CardEffectType type, bool isSelected) -> std::string {
        if (isSelected) return COLOR_LYELLOW;
        if (type == CardEffectType::DAMAGE || type == CardEffectType::TRUE_DAMAGE || 
            type == CardEffectType::BREAK_ARMOR_DAMAGE || type == CardEffectType::MULTI_DAMAGE) {
            return COLOR_LRED;
        } else if (type == CardEffectType::DEFEND || type == CardEffectType::COUNTER) {
            return COLOR_LBLUE;
        } else {
            return COLOR_LGREEN;
        }
    };

    system("cls");
    
    std::cout << COLOR_LYELLOW << "==========================================================" << COLOR_RESET << std::endl;
    // 1. 怪物意圖預告區
    if (monster.getHp() <= 0) {
        std::cout << COLOR_RED << "【怪物意圖】怪物已死亡" << COLOR_RESET << std::endl;
    } else if (monster.getIsStunned()) {
        std::cout << COLOR_LBLUE << "【怪物意圖】" << monster.getName() << " 下回合將 [眩暈無法行動]" << COLOR_RESET << std::endl;
    } else {
        std::cout << COLOR_LYELLOW << "【怪物意圖】" << COLOR_RESET << monster.getName() << " 下回合將使用 [" 
                  << COLOR_LRED << monster.getNextMove().name << COLOR_RESET << "]，預估傷害: " 
                  << COLOR_LRED << monster.getNextMove().damage << COLOR_RESET;
        if (monster.getNextMove().armorGain > 0) {
            std::cout << "，護盾加值: " << COLOR_LBLUE << monster.getNextMove().armorGain << COLOR_RESET;
        }
        std::cout << std::endl;
    }
    std::cout << COLOR_LYELLOW << "==========================================================" << COLOR_RESET << std::endl;
    std::cout << std::endl;
    
    // 1.5 魔物 ASCII 藝術
    std::vector<std::string> art = getMonsterASCIIArt(monster.getName());
    bool isApocalypseCharging = (monster.getName().find("烈焰巨龍") != std::string::npos && 
                                 monster.getNextMove().name == "毀天滅地" && 
                                 !monster.getIsStunned());
    for (size_t idx = 0; idx < art.size(); ++idx) {
        std::string line = art[idx];
        if (isApocalypseCharging) {
            std::string col = (idx % 2 == 0) ? "\x1b[1;5;91m" : "\x1b[1;5;93m"; // Blinking Bold Red & Yellow
            std::cout << "  " << col << line << COLOR_RESET << std::endl;
        } else {
            std::string monsterColor = getMonsterColor(monster.getName());
            std::cout << "  " << monsterColor << line << COLOR_RESET << std::endl;
        }
    }
    std::cout << std::endl;
    
    // 2. 戰鬥主畫面 (怪物 & 玩家)
    std::cout << "  " << COLOR_BOLD << monster.getName() << COLOR_RESET << " (怪物)" << std::endl;
    std::cout << "  HP: [" << COLOR_LRED << getHealthBar(monster.getHp(), monster.getMaxHp()) << COLOR_RESET << "] " 
              << COLOR_LRED << monster.getHp() << COLOR_RESET << " / " << monster.getMaxHp();
    if (monster.getArmor() > 0) {
        std::cout << " (" << COLOR_LBLUE << "護盾: " << monster.getArmor() << COLOR_RESET << ")";
    }
    if (monster.getIsStunned()) {
        std::cout << " [" << COLOR_LBLUE << "眩暈" << COLOR_RESET << "]";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "  " << COLOR_BOLD << "玩家" << COLOR_RESET << " (勇者)" << std::endl;
    std::cout << "  HP: [" << COLOR_LGREEN << getHealthBar(player.getHp(), player.getMaxHp()) << COLOR_RESET << "] " 
              << COLOR_LGREEN << player.getHp() << COLOR_RESET << " / " << player.getMaxHp();
    if (player.getArmor() > 0) {
        std::cout << " (" << COLOR_LBLUE << "護盾: " << player.getArmor() << COLOR_RESET << ")";
    }
    if (player.getIsCountering()) {
        std::cout << " [" << COLOR_LMAGENTA << "反擊姿勢" << COLOR_RESET << "]";
    }
    if (level == 2 && !player.getAcceptedGodsGuidance()) {
        std::cout << " [" << COLOR_LRED << "🔥 凡人意志" << COLOR_RESET << "]";
    }
    std::cout << std::endl;
    
    std::cout << "  SP: ";
    for (int i = 0; i < player.getMaxSp(); ++i) {
        if (i < player.getSp()) {
            std::cout << COLOR_LYELLOW << "◆" << COLOR_RESET; // 實心能量
        } else {
            std::cout << COLOR_WHITE << "◇" << COLOR_RESET; // 空心能量
        }
    }
    std::cout << " (" << COLOR_LYELLOW << player.getSp() << COLOR_RESET << " / " << player.getMaxSp() << ")" << std::endl;
    std::cout << std::endl;
    std::cout << COLOR_LCYAN << "==========================================================" << COLOR_RESET << std::endl;
    
    // 3. 戰鬥日誌區
    std::cout << COLOR_LCYAN << "【戰鬥日誌】" << COLOR_RESET << std::endl;
    for (const auto& log : actionLogs) {
        if (log.find("玩家打出") != std::string::npos || log.find("玩家使用了") != std::string::npos || log.find("觸發反擊") != std::string::npos || log.find("玩家抽卡") != std::string::npos) {
            std::cout << "  " << COLOR_LGREEN << log << COLOR_RESET << std::endl;
        } else if (log.find("怪物 [") != std::string::npos || log.find("被擊敗") != std::string::npos || log.find("戰鬥失敗") != std::string::npos) {
            std::cout << "  " << COLOR_LRED << log << COLOR_RESET << std::endl;
        } else if (log.find("戰鬥勝利") != std::string::npos || log.find("恭喜獲得") != std::string::npos) {
            std::cout << "  " << COLOR_LYELLOW << log << COLOR_RESET << std::endl;
        } else {
            std::cout << "  " << log << std::endl;
        }
    }
    for (size_t i = actionLogs.size(); i < 4; ++i) {
        std::cout << std::endl;
    }
    std::cout << COLOR_LCYAN << "==========================================================" << COLOR_RESET << std::endl;
    std::cout << std::endl;
    
    // 4. 手牌與動作選擇區
    if (isPlayerTurn && !isBattleOver) {
        std::cout << "【手牌與動作】(使用方向鍵移動，Enter 鍵確認出牌/行動)" << std::endl;
        std::cout << std::endl;
        
        // 4.1 普通攻擊 (獨立的一列)
        bool isSelectedNormal = (cursorIndex == 0);
        if (isSelectedNormal) {
            std::cout << COLOR_LYELLOW << "  *==============*" << COLOR_RESET << std::endl;
            std::cout << COLOR_LYELLOW << "  *" << COLOR_RESET << COLOR_BOLD << padUTF8Text("* 普通攻擊 *", 14) << COLOR_RESET << COLOR_LYELLOW << "*" << COLOR_RESET << std::endl;
            std::cout << COLOR_LYELLOW << "  *" << COLOR_RESET << padUTF8Text("回復: 2 SP", 14) << COLOR_LYELLOW << "*" << COLOR_RESET << std::endl;
            std::cout << COLOR_LYELLOW << "  *" << COLOR_RESET << padUTF8Text("造成 5 點傷害", 14) << COLOR_LYELLOW << "*" << COLOR_RESET << std::endl;
            std::cout << COLOR_LYELLOW << "  *==============*" << COLOR_RESET << std::endl;
        } else {
            std::cout << COLOR_WHITE << "  .--------------." << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  |" << COLOR_RESET << padUTF8Text("普通攻擊", 14) << COLOR_WHITE << "|" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  |" << COLOR_RESET << padUTF8Text("回復: 2 SP", 14) << COLOR_WHITE << "|" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  |" << COLOR_RESET << padUTF8Text("造成 5 點傷害", 14) << COLOR_WHITE << "|" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  '--------------'" << COLOR_RESET << std::endl;
        }
        std::cout << std::endl;
        std::cout << "  ----------------手牌列表----------------" << std::endl;
        std::cout << std::endl;
        
        // 4.2 手牌 (橫向並排 ASCII 卡牌框，每行最多 5 張)
        const auto& hand = player.getHand();
        int totalHand = hand.size();
        for (int startIdx = 0; startIdx < totalHand; startIdx += 5) {
            int endIdx = std::min(startIdx + 5, totalHand);
            
            // 第一行：頂框
            for (int i = startIdx; i < endIdx; ++i) {
                int optionId = i + 1;
                bool isSelected = (cursorIndex == optionId);
                const auto& card = hand[i];
                std::string cardColor = getCardColor(card.getEffectType(), isSelected);
                if (isSelected) {
                    std::cout << cardColor << "*==============*" << COLOR_RESET;
                } else {
                    std::cout << cardColor << ".--------------." << COLOR_RESET;
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第二行：種類分類
            for (int i = startIdx; i < endIdx; ++i) {
                int optionId = i + 1;
                bool isSelected = (cursorIndex == optionId);
                const auto& card = hand[i];
                std::string cardColor = getCardColor(card.getEffectType(), isSelected);
                
                std::string typeStr = "";
                CardEffectType type = card.getEffectType();
                if (type == CardEffectType::DAMAGE || type == CardEffectType::TRUE_DAMAGE || 
                    type == CardEffectType::BREAK_ARMOR_DAMAGE || type == CardEffectType::MULTI_DAMAGE) {
                    typeStr = "⚔️ 攻擊";
                } else if (type == CardEffectType::DEFEND || type == CardEffectType::COUNTER) {
                    typeStr = "🛡️ 防禦";
                } else {
                    typeStr = "🌳 輔助";
                }
                std::string paddedType = padUTF8Text(typeStr, 14);
                
                if (isSelected) {
                    std::cout << cardColor << "*" << COLOR_RESET << COLOR_BOLD << paddedType << COLOR_RESET << cardColor << "*" << COLOR_RESET;
                } else {
                    std::string typeColor;
                    if (typeStr == "⚔️ 攻擊") typeColor = COLOR_LRED;
                    else if (typeStr == "🛡️ 防禦") typeColor = COLOR_LBLUE;
                    else typeColor = COLOR_LGREEN;
                    std::cout << cardColor << "|" << COLOR_RESET << typeColor << paddedType << COLOR_RESET << cardColor << "|" << COLOR_RESET;
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第三行：卡牌名稱
            for (int i = startIdx; i < endIdx; ++i) {
                int optionId = i + 1;
                bool isSelected = (cursorIndex == optionId);
                const auto& card = hand[i];
                std::string cardColor = getCardColor(card.getEffectType(), isSelected);
                std::string nameStr = isSelected ? ("* " + card.getName() + " *") : card.getName();
                std::string paddedName = padUTF8Text(nameStr, 14);
                if (isSelected) {
                    std::cout << cardColor << "*" << COLOR_RESET << COLOR_BOLD << paddedName << COLOR_RESET << cardColor << "*" << COLOR_RESET;
                } else {
                    std::cout << cardColor << "|" << COLOR_RESET << paddedName << cardColor << "|" << COLOR_RESET;
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第四行：能量消耗
            for (int i = startIdx; i < endIdx; ++i) {
                int optionId = i + 1;
                bool isSelected = (cursorIndex == optionId);
                const auto& card = hand[i];
                std::string cardColor = getCardColor(card.getEffectType(), isSelected);
                std::string spStr = "消耗: " + std::to_string(card.getSpCost()) + " SP";
                std::string paddedSp = padUTF8Text(spStr, 14);
                if (isSelected) {
                    std::cout << cardColor << "*" << COLOR_RESET << paddedSp << cardColor << "*" << COLOR_RESET;
                } else {
                    std::cout << cardColor << "|" << COLOR_RESET << paddedSp << cardColor << "|" << COLOR_RESET;
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第五行：效果描述
            for (int i = startIdx; i < endIdx; ++i) {
                int optionId = i + 1;
                bool isSelected = (cursorIndex == optionId);
                const auto& card = hand[i];
                std::string cardColor = getCardColor(card.getEffectType(), isSelected);
                std::string desc = getCardShortDesc(card.getName());
                std::string paddedDesc = padUTF8Text(desc, 14);
                if (isSelected) {
                    std::cout << cardColor << "*" << COLOR_RESET << paddedDesc << cardColor << "*" << COLOR_RESET;
                } else {
                    std::cout << cardColor << "|" << COLOR_RESET << paddedDesc << cardColor << "|" << COLOR_RESET;
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 第六行：底框
            for (int i = startIdx; i < endIdx; ++i) {
                int optionId = i + 1;
                bool isSelected = (cursorIndex == optionId);
                const auto& card = hand[i];
                std::string cardColor = getCardColor(card.getEffectType(), isSelected);
                if (isSelected) {
                    std::cout << cardColor << "*==============*" << COLOR_RESET;
                } else {
                    std::cout << cardColor << "'--------------'" << COLOR_RESET;
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
            
            // 卡牌行間隔
            std::cout << std::endl;
        }
        std::cout << COLOR_WHITE << "==========================================================" << COLOR_RESET << std::endl;
    } else {
        std::cout << "【等待中...】正在處理回合行動..." << std::endl;
        std::cout << COLOR_WHITE << "==========================================================" << COLOR_RESET << std::endl;
    }
}

void Battle::showActionMessage(const std::string& msg) {
    addLog(msg);
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
        const auto& hand = player.getHand();
        int totalHand = hand.size();
        
        if (cursorIndex == 0) {
            // 在普通攻擊（最上方）時
            if (next_ch == 80) { // 按向下，進入手牌第一張
                if (totalHand > 0) {
                    cursorIndex = 1;
                }
                drawUI();
            } else if (next_ch == 72) { // 按向上，循環到手牌的最後一張
                if (totalHand > 0) {
                    cursorIndex = totalHand;
                }
                drawUI();
            }
            // 左右鍵在普通攻擊時不做動作，保持選取
        } else {
            // 在手牌時 (1 .. totalHand)
            if (next_ch == 75) { // 方向鍵左 (僅在手牌之間循環)
                cursorIndex--;
                if (cursorIndex < 1) {
                    cursorIndex = totalHand;
                }
                drawUI();
            } else if (next_ch == 77) { // 方向鍵右 (僅在手牌之間循環)
                cursorIndex++;
                if (cursorIndex > totalHand) {
                    cursorIndex = 1;
                }
                drawUI();
            } else if (next_ch == 72) { // 方向鍵上
                if (cursorIndex <= 5) { // 手牌第一排，按上回到普通攻擊
                    cursorIndex = 0;
                } else {
                    cursorIndex -= 5;
                }
                drawUI();
            } else if (next_ch == 80) { // 方向鍵下
                int nextIndex = cursorIndex + 5;
                if (nextIndex <= totalHand) {
                    cursorIndex = nextIndex;
                } else {
                    cursorIndex = 0; // 超出範圍，循環回最上方的普通攻擊
                }
                drawUI();
            }
        }
    } else if (ch == 13 || ch == 10) { // Enter 鍵
        executePlayerAction();
    }
    // 忽略數字鍵及其他非方向鍵/Enter鍵輸入
}

void Battle::executePlayerAction() {
    if (cursorIndex == 0) {
        // 普通攻擊
        showActionMessage("▶ 玩家使用了 [普通攻擊]，對怪物造成 5 點傷害，並回復 2 點 SP！");
        monster.takeDamage(5, false, [this]() { this->drawUI(); });
        player.gainSP(2);
        
        if (monster.getHp() <= 0) {
            player.incrementTotalTurns();
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
            addLog("❌ 能量（SP）不足，無法使用該卡牌！");
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
            int multiplier = 1;
            bool isCrit = false;
            int finalDmg = val;
            if (level == 2) {
                std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
                if (player.getAcceptedGodsGuidance()) {
                    multiplier = std::uniform_int_distribution<int>(2, 4)(generator);
                } else {
                    multiplier = 2;
                }
                isCrit = (std::uniform_int_distribution<int>(1, 100)(generator) <= 25);
                finalDmg = val * multiplier;
                if (isCrit) finalDmg *= 2;
            }
            if (level == 2) {
                if (player.getAcceptedGodsGuidance()) {
                    logMsg += "獲得眾神指引 (" + std::to_string(multiplier) + "倍傷害" + (isCrit ? " + 💥爆擊" : "") + ")，";
                } else {
                    logMsg += "自立自強 (" + std::to_string(multiplier) + "倍傷害" + (isCrit ? " + 💥爆擊" : "") + ")，";
                }
            }
            logMsg += "對怪物造成 " + std::to_string(finalDmg) + " 點傷害！";
            showActionMessage(logMsg);
            monster.takeDamage(finalDmg, false, [this]() { this->drawUI(); });
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
            int multiplier = 1;
            bool isCrit = false;
            int finalDmg = val;
            if (level == 2) {
                std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
                if (player.getAcceptedGodsGuidance()) {
                    multiplier = std::uniform_int_distribution<int>(2, 4)(generator);
                } else {
                    multiplier = 2;
                }
                isCrit = (std::uniform_int_distribution<int>(1, 100)(generator) <= 25);
                finalDmg = val * multiplier;
                if (isCrit) finalDmg *= 2;
            }
            if (level == 2) {
                if (player.getAcceptedGodsGuidance()) {
                    logMsg += "獲得眾神指引 (" + std::to_string(multiplier) + "倍傷害" + (isCrit ? " + 💥爆擊" : "") + ")，";
                } else {
                    logMsg += "自立自強 (" + std::to_string(multiplier) + "倍傷害" + (isCrit ? " + 💥爆擊" : "") + ")，";
                }
            }
            logMsg += "對怪物造成 " + std::to_string(finalDmg) + " 點真實傷害（穿透護盾）！";
            showActionMessage(logMsg);
            monster.takeDamage(finalDmg, true, [this]() { this->drawUI(); });
        } else if (type == CardEffectType::BREAK_ARMOR_DAMAGE) {
            int multiplier = 1;
            bool isCrit = false;
            int finalDmg = val;
            if (level == 2) {
                std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
                if (player.getAcceptedGodsGuidance()) {
                    multiplier = std::uniform_int_distribution<int>(2, 4)(generator);
                } else {
                    multiplier = 2;
                }
                isCrit = (std::uniform_int_distribution<int>(1, 100)(generator) <= 25);
                finalDmg = val * multiplier;
                if (isCrit) finalDmg *= 2;
            }
            if (level == 2) {
                if (player.getAcceptedGodsGuidance()) {
                    logMsg += "獲得眾神指引 (" + std::to_string(multiplier) + "倍傷害" + (isCrit ? " + 💥爆擊" : "") + ")，";
                } else {
                    logMsg += "自立自強 (" + std::to_string(multiplier) + "倍傷害" + (isCrit ? " + 💥爆擊" : "") + ")，";
                }
            }
            logMsg += "一擊粉碎了怪物的護盾，並造成 " + std::to_string(finalDmg) + " 點傷害！";
            showActionMessage(logMsg);
            monster.setArmor(0);
            monster.takeDamage(finalDmg, false, [this]() { this->drawUI(); });
        } else if (type == CardEffectType::MULTI_DAMAGE) {
            int multiplier = 1;
            bool isCrit = false;
            int finalDmg = val;
            if (level == 2) {
                std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
                if (player.getAcceptedGodsGuidance()) {
                    multiplier = std::uniform_int_distribution<int>(2, 4)(generator);
                } else {
                    multiplier = 2;
                }
                isCrit = (std::uniform_int_distribution<int>(1, 100)(generator) <= 25);
                finalDmg = val * multiplier;
                if (isCrit) finalDmg *= 2;
            }
            for (int i = 0; i < 3; ++i) {
                std::string hitMsg = "▶ 玩家打出 [" + card.getName() + "] (第 " + std::to_string(i + 1) + " 連擊)，";
                if (level == 2) {
                    if (player.getAcceptedGodsGuidance()) {
                        hitMsg += "獲得眾神指引 (" + std::to_string(multiplier) + "倍傷害" + (isCrit ? " + 💥爆擊" : "") + ")，";
                    } else {
                        hitMsg += "自立自強 (" + std::to_string(multiplier) + "倍傷害" + (isCrit ? " + 💥爆擊" : "") + ")，";
                    }
                }
                hitMsg += "對怪物造成 " + std::to_string(finalDmg) + " 點傷害！";
                showActionMessage(hitMsg);
                monster.takeDamage(finalDmg, false, [this]() { this->drawUI(); });
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
            player.incrementTotalTurns();
            isBattleOver = true;
            isPlayerVictor = true;
            return;
        }
        
        // 每次打出卡牌行動後回復 2 點 SP
        player.gainSP(2);
        showActionMessage("▶ 行動完畢，玩家回復了 2 點 SP！");
        
        isPlayerTurn = false;
    }
}

void Battle::executeMonsterTurn() {
    // 怪物回合開始，重置上回合殘留的護盾與狀態
    monster.resetTurnState();

    if (monster.getIsStunned()) {
        if (monster.getName().find("烈焰巨龍") != std::string::npos && monster.getNextMove().name == "毀天滅地") {
            showActionMessage("▶ 怪物 [" + monster.getName() + "] 處於眩暈狀態，其蓄力招式 [毀天滅地] 被成功中斷！");
        } else {
            showActionMessage("▶ 怪物 [" + monster.getName() + "] 處於眩暈狀態，本回合無法行動！");
        }
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
    
    // 增加總回合數
    player.incrementTotalTurns();
    
    // 補抽牌至手牌有 5 張 (保留手牌，不丟棄)
    int currentHandSize = player.getHand().size();
    if (currentHandSize < 5) {
        std::vector<Card> drawn = player.drawCards(5 - currentHandSize);
        std::string drawMsg = "▶ 玩家抽卡：";
        for (size_t i = 0; i < drawn.size(); ++i) {
            drawMsg += "[" + drawn[i].getName() + "]";
            if (i < drawn.size() - 1) {
                drawMsg += ", ";
            }
        }
        addLog(drawMsg);
    }
    
    // 增加怪物行動次數
    monster.incrementActionCount();

    // 怪物決定下回合招式
    monster.rollIntent();

    // 命運之手保底機制：若意圖為毀天滅地且手牌無電擊術，強制抽調
    if (monster.getName().find("烈焰巨龍") != std::string::npos && monster.getNextMove().name == "毀天滅地") {
        bool hasStunCard = false;
        for (const auto& c : player.getHand()) {
            if (c.getName() == "電擊術") {
                hasStunCard = true;
                break;
            }
        }
        if (!hasStunCard) {
            std::vector<Card> currentHand = player.getHand();
            std::vector<Card> currentDeck = player.getDeck();
            std::vector<Card> currentDiscard = player.getDiscardPile();
            
            bool found = false;
            // 先從牌組尋找
            for (auto it = currentDeck.begin(); it != currentDeck.end(); ++it) {
                if (it->getName() == "電擊術") {
                    currentHand.push_back(*it);
                    currentDeck.erase(it);
                    found = true;
                    break;
                }
            }
            if (!found) {
                // 再從棄牌堆尋找
                for (auto it = currentDiscard.begin(); it != currentDiscard.end(); ++it) {
                    if (it->getName() == "電擊術") {
                        currentHand.push_back(*it);
                        currentDiscard.erase(it);
                        found = true;
                        break;
                    }
                }
            }
            if (!found) {
                // 如果整個牌組都沒有，直接創建一張給予
                currentHand.push_back(Player::createCardByName("電擊術"));
                addLog("⚠️ 偵測到致命危機！神明憐憫，直接賜予你一張 [電擊術]！");
            } else {
                addLog("⚠️ 偵測到致命危機！命運之手引導你抽出了 [電擊術]！");
            }
            player.setDeckState(currentDeck, currentHand, currentDiscard);
        }
    }
    
    // 游標重置，回歸玩家回合
    cursorIndex = 0;
    isPlayerTurn = true;
    addLog("你的回合。請選擇你的行動。");
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
    addLog("戰鬥開始！請選擇你的行動。");
    
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
