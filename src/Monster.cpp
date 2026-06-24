#include "Monster.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <windows.h>

Monster::Monster(std::string name, int hp, int maxHp, const std::vector<MonsterMove>& moves)
    : Character(name, hp, maxHp), moves(moves) {
    rollIntent();
}

MonsterMove Monster::getNextMove() const { return nextMove; }

void Monster::rollIntent() {
    if (moves.empty()) {
        nextMove = {"撞擊", 5, 0, "對目標造成 5 點傷害"};
        return;
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, moves.size() - 1);
    int index = distribution(generator);
    nextMove = moves[index];
}
