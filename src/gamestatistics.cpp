#include "gamestatistics.hpp"

GameStatistics::GameStatistics() {
    reset();
}

GameStatistics::~GameStatistics() {}

void GameStatistics::reset() {
    scores = fails = skips = 0;
}

void GameStatistics::incScores() {
    scores++;
}
void GameStatistics::incFails() {
    fails++;
}
void GameStatistics::incSkips() {
    skips++;
}

int GameStatistics::getScores() {
    return scores;
}

int GameStatistics::getFails() {
    return fails;
}

int GameStatistics::getSkips() {
    return skips;
}

int GameStatistics::getAccuracy() {
    int attepmpts = scores + fails + skips;
    if (attepmpts) {
        return int(float(scores)* 100.f / float(attepmpts));
    }
    return 100;
}
