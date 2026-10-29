#pragma once
#include "Grid.hpp"

using namespace std;

class GameEngine {
public:
    GameEngine();
    void run();

private:
    void render();
    bool processInput();
    void updateEnemies();
    void clearScreen();

    Grid grid_;
    Vec2 playerPos_{1, 1};
    vector<Vec2> securityNodes_;
    int clockCycles_{65};
    int dataRemaining_{2};
    bool gameOver_{false};
    bool gameWon_{false};
    string statusMessage_{"Infiltrate the network and extract all data caches."};
};
