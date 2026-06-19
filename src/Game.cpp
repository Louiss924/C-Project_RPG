#include "Game.h"
#include "Battle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <chrono>
#include <random>
#include <windows.h>

Game::Game() : player(80, 80, 7, 10), currentLevel(1), currentRound(1), menuCursor(0) {}

void Game::displayLevelStartMessage() {
    system("cls");
    std::cout << "\n\n\n";
    std::cout << "      ==========================================" << std::endl;
    std::cout << "                ★ 關卡開始 ★" << std::endl;
    std::cout << "                 LEVEL " << currentLevel << " - ROUND " << currentRound << std::endl;
    std::cout << "      ==========================================" << std::endl;
    std::cout << "\n";
    std::cout << "              勇者已準備好迎接新的挑戰！" << std::endl;
    std::cout << "\n";
    std::cout << "              請按任意鍵開始戰鬥..." << std::endl;
    _getch();
}

void Game::displayDefeatScreen() {
    remove("save.dat");
    system("cls");
    std::cout << "\n\n\n";
    std::cout << "      💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀" << std::endl;
    std::cout << "      ☠️                                  ☠️" << std::endl;
    std::cout << "      ☠️            遊 戲 結 束           ☠️" << std::endl;
    std::cout << "      ☠️                                  ☠️" << std::endl;
    std::cout << "      💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀" << std::endl;
    std::cout << "\n";
    std::cout << "              勇者不幸戰死在沙場上..." << std::endl;
    std::cout << "              請按任意鍵退出遊戲。" << std::endl;
    _getch();
}

void Game::displayVictoryScreen() {
    remove("save.dat");
    system("cls");
    std::cout << "\n\n\n";
    std::cout << "      🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << std::endl;
    std::cout << "      🏆                                  🏆" << std::endl;
    std::cout << "      🏆     遊 戲 通 關，勇 者 獲 勝！   🏆" << std::endl;
    std::cout << "      🏆                                  🏆" << std::endl;
    std::cout << "      🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << std::endl;
    std::cout << "\n";
    std::cout << "              你成功的擊敗了最終烈焰巨龍！" << std::endl;
    std::cout << "              拯救了整個王國！傳奇永流傳！" << std::endl;
    std::cout << "              請按任意鍵結束程式。" << std::endl;
    _getch();
}

void Game::run() {
    bool inMenu = true;
    while (inMenu) {
        displayMainMenu();
        bool hasSave = hasSaveFile();
        
        if (menuCursor == 0) {
            // 開始冒險
            inMenu = false;
            while (_kbhit()) {
                _getch();
            }
        } else if (hasSave && menuCursor == 1) {
            // 繼續冒險 (載入存檔)
            if (loadGame()) {
                inMenu = false;
                std::cout << "\n        🎉 存檔載入成功！即將繼續冒險..." << std::endl;
                Sleep(800);
                while (_kbhit()) {
                    _getch();
                }
            } else {
                std::cout << "\n        ❌ 存檔已損毀或載入失敗！請按任意鍵返回..." << std::endl;
                _getch();
            }
        } else if ((hasSave && menuCursor == 2) || (!hasSave && menuCursor == 1)) {
            // 遊戲說明
            displayInstructions();
        } else if ((hasSave && menuCursor == 3) || (!hasSave && menuCursor == 2)) {
            // 離開遊戲
            system("cls");
            std::cout << "\n\n        感謝您的遊玩！再見！\n\n";
            exit(0);
        }
    }

    while (currentLevel <= 3) {
        displayLevelStartMessage();
        
        std::string monsterName;
        int monsterHp = 25;
        std::vector<MonsterMove> moves;
        
        if (currentLevel == 1) {
            if (currentRound == 1) {
                monsterName = "溫和的史萊姆";
                monsterHp = 25;
                moves = {{"撞擊", 4, 0, "撞擊玩家"}, {"分裂準備", 0, 4, "分裂準備：蓄力並獲得 4 點護盾"}};
            } else if (currentRound == 2) {
                monsterName = "哥布林斥候";
                monsterHp = 40;
                moves = {
                    {"飛刀", 6, 0, "向玩家投擲飛刀"},
                    {"格擋姿勢", 0, 6, "格擋：獲得 6 點護盾"},
                    {"三連投擲", 3, 0, "快速投擲三把飛刀 (造成 3 點傷害，重複 3 次)", false, 3},
                    {"毒刃突襲", 4, 0, "毒刃突襲，對玩家造成 4 點傷害並扣減 1 點 SP！", false, 1, 1}
                };
            } else {
                monsterName = "哥布林酋長 (第一關 Boss)";
                monsterHp = 65;
                moves = {
                    {"大棒重擊", 9, 0, "揮舞大棒重擊玩家"},
                    {"狂暴咆哮", 5, 5, "咆哮：造成 5 點傷害並獲得 5 點護盾"},
                    {"震撼重擊", 8, 0, "震撼打擊玩家 (造成 8 點傷害，並使玩家眩暈 1 回合)", false, 1, 0, true},
                    {"狂暴揮擊", 7, 0, "使出狂暴揮擊 (造成 7 點真實傷害！穿透護盾)", true}
                };
            }
        } else if (currentLevel == 2) {
            if (currentRound == 1) {
                monsterName = "哀怨的小幽靈";
                monsterHp = 45;
                moves = {{"靈魂震懾", 7, 0, "震懾玩家心靈"}, {"虛無狀態", 0, 7, "虛無：獲得 7 點護盾"}};
            } else if (currentRound == 2) {
                monsterName = "骷髏精兵";
                monsterHp = 60;
                moves = {{"骨刺突襲", 9, 0, "發動尖銳骨刺突襲"}, {"重盾防禦", 0, 9, "舉起重盾：獲得 9 點護盾"}};
            } else {
                monsterName = "墮落巫妖王 (第二關 Boss)";
                monsterHp = 85;
                moves = {{"死亡凋零", 13, 0, "釋放冰霜死亡凋零 (真實傷害！)", true}, {"亡靈護盾", 4, 8, "召喚護盾：造成 4 點傷害並獲得 8 點護盾", false}};
            }
        } else {
            if (currentRound == 1) {
                monsterName = "火山蜥蜴";
                monsterHp = 70;
                moves = {{"火球噴射", 11, 0, "噴射火球"}, {"熱能護盾", 0, 11, "凝聚熱能：獲得 11 點護盾"}};
            } else if (currentRound == 2) {
                monsterName = "遠古岩石巨人";
                monsterHp = 95;
                moves = {{"巨石重擊", 14, 0, "砸下巨石"}, {"大地防護", 0, 15, "吸收大地之力：獲得 15 點護盾"}};
            } else {
                monsterName = "烈焰巨龍 (最終 Boss)";
                monsterHp = 140;
                moves = {
                    {"毀滅龍息", 18, 0, "噴吐毀滅龍之吐息 (真實傷害！)", true},
                    {"龍鱗防壁", 5, 12, "龍之防壁：造成 5 點傷害並獲得 12 點護盾", false},
                    {"擺尾橫掃", 12, 6, "巨尾橫掃：造成 12 點傷害並獲得 6 點護盾", false}
                };
            }
        }
        
        Monster monster(monsterName, monsterHp, monsterHp, moves);
        
        // 戰鬥前劇情對話
        if (currentLevel == 1) {
            if (currentRound == 2) {
                displayStoryDialogue("哥布林斥候", {
                    "哼，闖入者！前面的史萊姆只是一個誘餌！",
                    "你竟然能走到這一步...但也就到此為止了！",
                    "嘗嘗我的利刃吧！"
                });
            } else if (currentRound == 3) {
                displayStoryDialogue("哥布林酋長 (第一關 Boss)", {
                    "無知的凡人！你竟敢殺害我的斥候，還敢打擾我的安寧！",
                    "這裡將是你的墳墓！",
                    "受死吧，感受酋長的大棒！"
                });
            }
        }
        
        if (currentRound == 3) {
            playBossWarningAnimation();
        }
        
        Battle battle(player, monster);
        bool victory = battle.start(currentRound == 1);
        
        if (!victory) {
            displayDefeatScreen();
            return;
        }
        
        // 戰鬥勝利劇情對話
        if (currentLevel == 1) {
            if (currentRound == 2) {
                displayStoryDialogue("哥布林斥候", {
                    "可惡...你這傢伙竟然...這麼強...",
                    "不過別得意，酋長大人...絕對會替我報仇的...",
                    "他在前方等著你...呃啊..."
                });
            } else if (currentRound == 3) {
                displayStoryDialogue("哥布林酋長 (第一關 Boss)", {
                    "這...這不可能...我堂堂酋長竟然會輸給一個人類...",
                    "我的部落...完了...",
                    "咳...下一關的魔物...不會放過你的..."
                });
            }
        }
        
        if (currentRound == 3) {
            if (currentLevel == 3) {
                displayVictoryScreen();
                return;
            } else {
                std::cout << std::endl;
                std::cout << "🎉 擊敗了當前關卡 Boss！即將晉級至下一關！" << std::endl;
                std::cout << "能量（SP）重置為 7 點，保留當前生命值與生命上限。" << std::endl;
                std::cout << "請按任意鍵繼續..." << std::endl;
                _getch();
                
                player.setSp(7);
                currentLevel++;
                currentRound = 1;
                saveGame();
            }
        } else {
            if (currentRound == 2) {
                std::cout << std::endl;
                std::cout << "⚔️ 關卡 " << currentLevel << "-2 勝利！" << std::endl;
                std::cout << "魔王戰前夕，即將進入卡牌增抽階段！" << std::endl;
                std::cout << "請按任意鍵繼續..." << std::endl;
                _getch();
                
                draftCardsPhase();
                currentRound++;
                saveGame();
            } else {
                std::cout << std::endl;
                std::cout << "⚔️ 關卡 " << currentLevel << "-" << currentRound << " 勝利！" << std::endl;
                std::cout << "即將晉級至下一個回合。" << std::endl;
                std::cout << "請按任意鍵繼續..." << std::endl;
                _getch();
                
                currentRound++;
                saveGame();
            }
        }
    }
}

void Game::draftCardsPhase() {
    system("cls");
    std::cout << "\n\n\n";
    std::cout << "      ==========================================" << std::endl;
    std::cout << "               ★ Boss 戰前卡牌增抽階段 ★" << std::endl;
    std::cout << "               將隨機抽取 2 張卡牌加入牌組！" << std::endl;
    std::cout << "      ==========================================" << std::endl;
    std::cout << "\n              按任意鍵開始抽牌..." << std::endl;
    _getch();

    std::vector<Card> pool = {
        Card("重擊", 1, CardEffectType::DAMAGE, 8, "造成 8 點傷害"),
        Card("防禦", 1, CardEffectType::DEFEND, 6, "獲得 6 點護盾（一般護盾）"),
        Card("護盾", 1, CardEffectType::DEFEND, 5, "獲得 5 點護盾（無法防住真實傷害）"),
        Card("治療術", 2, CardEffectType::HEAL, 10, "回復 10 點生命值"),
        Card("反擊姿態", 2, CardEffectType::COUNTER, 50, "反擊狀態：受到傷害時反彈 50% 給怪物"),
        Card("生命繁茂", 2, CardEffectType::MAX_HP_UP, 15, "最大生命值與當前生命值提升 15 點"),
        Card("電擊術", 3, CardEffectType::STUN, 1, "電暈怪物，使其下一回合眩暈無法行動"),
        Card("迅捷連擊", 2, CardEffectType::MULTI_DAMAGE, 4, "快速連擊 3 次，每次造成 4 點連擊傷害"),
        Card("貫穿擊", 1, CardEffectType::TRUE_DAMAGE, 8, "造成 8 點真實傷害（無視怪物護盾）"),
        Card("破甲重錘", 2, CardEffectType::BREAK_ARMOR_DAMAGE, 7, "粉碎怪物全部護盾，並造成 7 點傷害")
    };

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, pool.size() - 1);

    for (int draw = 1; draw <= 2; ++draw) {
        int targetIdx = distribution(generator);
        
        int delay = 30; 
        int rolls = 25; 
        int currentRollIdx = 0;
        
        for (int i = 0; i < rolls; ++i) {
            system("cls");
            std::cout << "\n\n\n";
            std::cout << "      ==========================================" << std::endl;
            std::cout << "               ★ 正在抽取第 " << draw << " 張卡牌... ★" << std::endl;
            std::cout << "      ==========================================" << std::endl;
            std::cout << "\n";
            
            currentRollIdx = (currentRollIdx + 1) % pool.size();
            std::cout << "              ▶ 滾動中: [" << pool[currentRollIdx].getName() << "] ◀" << std::endl;
            std::cout << "\n";
            std::cout << "      ==========================================" << std::endl;
            
            Sleep(delay);
            if (i > 15) {
                delay += 40;
            }
        }
        
        Card selected = pool[targetIdx];
        for (int blink = 0; blink < 3; ++blink) {
            system("cls");
            std::cout << "\n\n\n";
            std::cout << "      ==========================================" << std::endl;
            std::cout << "               ★ 第 " << draw << " 張卡牌抽取結果 ★" << std::endl;
            std::cout << "      ==========================================" << std::endl;
            std::cout << "\n";
            if (blink % 2 == 0) {
                std::cout << "            ✨✨✨ 恭喜獲得：[" << selected.getName() << "] ✨✨✨" << std::endl;
                std::cout << "                 " << selected.getDescription() << std::endl;
            } else {
                std::cout << std::endl;
                std::cout << std::endl;
            }
            std::cout << "\n";
            std::cout << "      ==========================================" << std::endl;
            Sleep(250);
        }
        
        system("cls");
        std::cout << "\n\n\n";
        std::cout << "      ==========================================" << std::endl;
        std::cout << "               ★ 第 " << draw << " 張卡牌已加入牌組 ★" << std::endl;
        std::cout << "      ==========================================" << std::endl;
        std::cout << "\n";
        std::cout << "            卡牌名稱：[" << selected.getName() << "]" << std::endl;
        std::cout << "            卡牌效果：" << selected.getDescription() << std::endl;
        std::cout << "            能量消耗：" << selected.getSpCost() << " SP" << std::endl;
        std::cout << "\n";
        std::cout << "      ==========================================" << std::endl;
        std::cout << "              按任意鍵繼續..." << std::endl;
        _getch();
        
        player.addCardToDeck(selected);
    }
}

void Game::playBossWarningAnimation() {
    for (int i = 0; i < 5; ++i) {
        system("cls");
        std::cout << "\n\n\n";
        if (i % 2 == 0) {
            std::cout << "      ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️" << std::endl;
            std::cout << "      ⚠️                                           ⚠️" << std::endl;
            std::cout << "      ⚠️        WARNING! BOSS IS APPROACHING!      ⚠️" << std::endl;
            std::cout << "      ⚠️                                           ⚠️" << std::endl;
            std::cout << "      ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️" << std::endl;
        } else {
            std::cout << "      ---------------------------------------------" << std::endl;
            std::cout << "                                                    " << std::endl;
            std::cout << "                WARNING! BOSS IS APPROACHING!       " << std::endl;
            std::cout << "                                                    " << std::endl;
            std::cout << "      ---------------------------------------------" << std::endl;
        }
        std::cout << "\n\n";
        Sleep(200);
    }
    system("cls");
}

void Game::displayStoryDialogue(const std::string& character, const std::vector<std::string>& lines) {
    system("cls");
    std::cout << "\n\n\n";
    std::cout << "      ==================================================" << std::endl;
    std::cout << "       💬 【" << character << "】" << std::endl;
    std::cout << "      --------------------------------------------------" << std::endl;
    for (const auto& line : lines) {
        std::cout << "        " << line << std::endl;
    }
    std::cout << "      ==================================================" << std::endl;
    std::cout << "\n              ( 按任意鍵繼續... )" << std::endl;
    _getch();
}

void Game::displayMainMenu() {
    bool hasSave = hasSaveFile();
    std::vector<std::string> options;
    if (hasSave) {
        options = { "開始冒險", "繼續冒險", "遊戲說明", "離開遊戲" };
    } else {
        options = { "開始冒險", "遊戲說明", "離開遊戲" };
        if (menuCursor >= 3) {
            menuCursor = 0;
        }
    }
    
    int totalOptions = options.size();
    bool selected = false;
    while (!selected) {
        hasSave = hasSaveFile();
        if (hasSave) {
            options = { "開始冒險", "繼續冒險", "遊戲說明", "離開遊戲" };
        } else {
            options = { "開始冒險", "遊戲說明", "離開遊戲" };
            if (menuCursor >= 3) {
                menuCursor = 0;
            }
        }
        totalOptions = options.size();

        system("cls");
        std::cout << "\n\n";
        std::cout << "      ========================================================" << std::endl;
        std::cout << "             🛡️  傳奇勇者：卡牌冒險 (Legend of Card Hero) 🛡️" << std::endl;
        std::cout << "      ========================================================" << std::endl;
        std::cout << "\n\n";
        
        for (int i = 0; i < totalOptions; ++i) {
            if (menuCursor == i) {
                std::cout << "                  > [ " << options[i] << " ] <" << std::endl;
            } else {
                std::cout << "                    [ " << options[i] << " ]  " << std::endl;
            }
            std::cout << "\n";
        }
        std::cout << "      ========================================================" << std::endl;
        std::cout << "           (使用 ↑/↓ 方向鍵移動游標，Enter 鍵確認選擇)" << std::endl;
        
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            int next_ch = _getch();
            if (next_ch == 72) { // Up arrow
                menuCursor = (menuCursor - 1 + totalOptions) % totalOptions;
            } else if (next_ch == 80) { // Down arrow
                menuCursor = (menuCursor + 1) % totalOptions;
            }
        } else if (ch == 13 || ch == 10) { // Enter
            selected = true;
        }
    }
}

void Game::displayInstructions() {
    system("cls");
    std::cout << "\n";
    std::cout << "      ==========================================================" << std::endl;
    std::cout << "                     📜 遊戲說明 (Instructions) 📜" << std::endl;
    std::cout << "      ==========================================================" << std::endl;
    std::cout << "\n";
    std::cout << "      【基礎規則】" << std::endl;
    std::cout << "      - 玩家的最大生命值 (HP) 為 80。歸 0 時遊戲結束。" << std::endl;
    std::cout << "      - 每回合可以選擇 [普通攻擊] (不耗能量，回復 1 SP，造成 5 傷害) 或使用手牌。" << std::endl;
    std::cout << "      - 每一大關的第 3 回合是 Boss 戰。戰勝前夕可自隨機池增抽 2 張卡牌。" << std::endl;
    std::cout << "      - 每回合結束時手牌會清空，並重新補滿 5 張手牌。護盾值亦會每回合清零。" << std::endl;
    std::cout << "\n";
    std::cout << "      【卡牌分類介紹】" << std::endl;
    std::cout << "      1. ⚔️ 攻擊型卡牌 (Offensive)" << std::endl;
    std::cout << "         - 重擊 (1 SP): 造成 8 點傷害。" << std::endl;
    std::cout << "         - 迅捷連擊 (2 SP): 快速連擊 3 次，每次造成 4 點連擊傷害 (共 12 點)。" << std::endl;
    std::cout << "         - 貫穿擊 (1 SP): 造成 8 點真實傷害 (無視怪物護盾)。" << std::endl;
    std::cout << "         - 破甲重錘 (2 SP): 粉碎怪物全部護盾 (歸 0)，並造成 7 點傷害。" << std::endl;
    std::cout << "      2. 🛡️ 防禦與反擊型卡牌 (Defensive & Counter)" << std::endl;
    std::cout << "         - 防禦 (1 SP): 獲得 6 點護盾。" << std::endl;
    std::cout << "         - 護盾 (1 SP): 獲得 5 點護盾（無法抵擋真實傷害）。" << std::endl;
    std::cout << "         - 反擊姿態 (2 SP): 附加反擊狀態，下回合反彈 50% 受到的傷害。" << std::endl;
    std::cout << "      3. 🌳 輔助與回復型卡牌 (Utility & Recovery)" << std::endl;
    std::cout << "         - 治療術 (2 SP): 回復 10 點生命值。" << std::endl;
    std::cout << "         - 生命繁茂 (2 SP): 最大生命值與當前生命值提升 15 點。" << std::endl;
    std::cout << "         - 電擊術 (3 SP): 電暈怪物，使其下一回合眩暈無法行動。" << std::endl;
    std::cout << "\n";
    std::cout << "      【操作說明】" << std::endl;
    std::cout << "      - 於選單或戰鬥出牌時，使用 [方向鍵 ↑/↓] 切換高亮選項。" << std::endl;
    std::cout << "      - 按下 [Enter 鍵] 確認選擇/出牌。" << std::endl;
    std::cout << "      ==========================================================" << std::endl;
    std::cout << "                         ( 按任意鍵返回主選單 )" << std::endl;
    _getch();
}

void Game::saveGame() {
    std::ofstream file("save.dat");
    if (!file.is_open()) {
        std::cerr << "⚠️ 無法寫入存檔檔案！" << std::endl;
        return;
    }
    
    // 第一行：關卡 回合 當前血量 最大血量上限
    file << currentLevel << " " << currentRound << " " << player.getHp() << " " << player.getMaxHp() << "\n";
    
    // 第二行：牌組卡牌（以逗號分隔）
    const auto& deck = player.getDeck();
    for (size_t i = 0; i < deck.size(); ++i) {
        file << deck[i].getName();
        if (i < deck.size() - 1) {
            file << ",";
        }
    }
    file << "\n";

    // 第三行：手牌卡牌（以逗號分隔）
    const auto& hand = player.getHand();
    for (size_t i = 0; i < hand.size(); ++i) {
        file << hand[i].getName();
        if (i < hand.size() - 1) {
            file << ",";
        }
    }
    file << "\n";

    // 第四行：棄牌堆卡牌（以逗號分隔）
    const auto& discard = player.getDiscardPile();
    for (size_t i = 0; i < discard.size(); ++i) {
        file << discard[i].getName();
        if (i < discard.size() - 1) {
            file << ",";
        }
    }
    file << "\n";

    file.close();
}

bool Game::loadGame() {
    std::ifstream file("save.dat");
    if (!file.is_open()) {
        return false;
    }
    
    std::string firstLine;
    if (!std::getline(file, firstLine)) {
        file.close();
        return false;
    }
    
    std::stringstream ss(firstLine);
    int lvl, rnd, hpVal, maxHpVal;
    if (!(ss >> lvl >> rnd >> hpVal >> maxHpVal)) {
        file.close();
        return false;
    }
    
    // 簡單的範圍防錯檢查
    if (lvl < 1 || lvl > 3 || rnd < 1 || rnd > 3 || hpVal < 0 || maxHpVal <= 0) {
        file.close();
        return false;
    }
    
    std::string secondLine = "";
    std::string thirdLine = "";
    std::string fourthLine = "";
    std::getline(file, secondLine);
    std::getline(file, thirdLine);
    std::getline(file, fourthLine);
    
    file.close();

    std::vector<Card> loadedDeck;
    std::stringstream ssDeck(secondLine);
    std::string cardName;
    while (std::getline(ssDeck, cardName, ',')) {
        if (!cardName.empty()) {
            loadedDeck.push_back(Player::createCardByName(cardName));
        }
    }

    std::vector<Card> loadedHand;
    std::stringstream ssHand(thirdLine);
    while (std::getline(ssHand, cardName, ',')) {
        if (!cardName.empty()) {
            loadedHand.push_back(Player::createCardByName(cardName));
        }
    }

    std::vector<Card> loadedDiscard;
    std::stringstream ssDiscard(fourthLine);
    while (std::getline(ssDiscard, cardName, ',')) {
        if (!cardName.empty()) {
            loadedDiscard.push_back(Player::createCardByName(cardName));
        }
    }
    
    // 載入成功，更新遊戲與玩家狀態
    currentLevel = lvl;
    currentRound = rnd;
    player.setMaxHp(maxHpVal);
    player.setHp(hpVal);
    player.setDeckState(loadedDeck, loadedHand, loadedDiscard);
    
    return true;
}

bool Game::hasSaveFile() const {
    std::ifstream file("save.dat");
    return file.good();
}
