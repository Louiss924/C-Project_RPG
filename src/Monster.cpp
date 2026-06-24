#include "Monster.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <windows.h>

Monster::Monster(std::string name, int hp, int maxHp, const std::vector<MonsterMove>& moves)
    : Character(name, hp, maxHp), moves(moves), actionCount(0) {
    rollIntent();
}

MonsterMove Monster::getNextMove() const { return nextMove; }

void Monster::rollIntent() {
    if (moves.empty()) {
        nextMove = {"撞擊", 5, 0, "對目標造成 5 點傷害"};
        return;
    }
    
    // 如果是烈焰巨龍且為第 3 次攻擊 (actionCount == 2)
    if (name.find("烈焰巨龍") != std::string::npos && actionCount == 2) {
        nextMove = {"毀天滅地", 9999, 0, "將在回合結束時召喚烈焰隕石毀天滅地，玩家將直接死亡！必須在本回合使用電擊術將其眩暈中斷！", true};
        return;
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, moves.size() - 1);
    int index = distribution(generator);
    nextMove = moves[index];
}
