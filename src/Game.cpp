#include "Game.h"
#include "Battle.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <random>
#include <windows.h>

Game::Game() : player(80, 80, 3, 10), currentLevel(1), currentRound(1) {}

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
                monsterHp = 35;
                moves = {{"飛刀", 6, 0, "向玩家投擲飛刀"}, {"格擋姿勢", 0, 6, "格擋：獲得 6 點護盾"}};
            } else {
                monsterName = "哥布林酋長 (第一關 Boss)";
                monsterHp = 55;
                moves = {{"大棒重擊", 9, 0, "揮舞大棒重擊玩家"}, {"狂暴咆哮", 5, 5, "咆哮：造成 5 點傷害並獲得 5 點護盾"}};
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
        
        if (currentRound == 3) {
            playBossWarningAnimation();
        }
        
        Battle battle(player, monster);
        bool victory = battle.start(currentRound == 1);
        
        if (!victory) {
            displayDefeatScreen();
            return;
        }
        
        if (currentRound == 3) {
            if (currentLevel == 3) {
                displayVictoryScreen();
                return;
            } else {
                std::cout << std::endl;
                std::cout << "🎉 擊敗了當前關卡 Boss！即將晉級至下一關！" << std::endl;
                std::cout << "能量（SP）重置為 3 點，保留當前生命值與生命上限。" << std::endl;
                std::cout << "請按任意鍵繼續..." << std::endl;
                _getch();
                
                player.setSp(3);
                currentLevel++;
                currentRound = 1;
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
            } else {
                std::cout << std::endl;
                std::cout << "⚔️ 關卡 " << currentLevel << "-" << currentRound << " 勝利！" << std::endl;
                std::cout << "即將晉級至下一個回合。" << std::endl;
                std::cout << "請按任意鍵繼續..." << std::endl;
                _getch();
                
                currentRound++;
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
        Card("電擊術", 3, CardEffectType::STUN, 1, "電暈怪物，使其下一回合眩暈無法行動")
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
