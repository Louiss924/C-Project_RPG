#include "Game.h"
#include "Battle.h"
#include <iostream>
#include <conio.h>

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
        
        Battle battle(player, monster);
        bool victory = battle.start();
        
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
            std::cout << std::endl;
            std::cout << "⚔️ 關卡 " << currentLevel << "-" << currentRound << " 勝利！" << std::endl;
            std::cout << "即將晉級至下一個回合。" << std::endl;
            std::cout << "請按任意鍵繼續..." << std::endl;
            _getch();
            
            currentRound++;
        }
    }
}
