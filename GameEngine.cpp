#include "GameEngine.hpp"

using namespace std;

GameEngine::GameEngine() : grid_(20, 11) {
    securityNodes_.push_back({10, 5});
    securityNodes_.push_back({15, 3});
}

void GameEngine::clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void GameEngine::render() {
    clearScreen();

    cout << Color::Cyan << "========================================\n"
         << "       NETWATCH // TERMINAL HACKER      \n"
         << "========================================\n" << Color::Reset;

    cout << " Clock Cycles: " << (clockCycles_ < 20 ? Color::Red : Color::Green)
         << clockCycles_ << Color::Reset
         << " | Data Left: " << Color::Yellow << dataRemaining_ << Color::Reset << "\n\n";

    for (int y = 0; y < grid_.getHeight(); ++y) {
        for (int x = 0; x < grid_.getWidth(); ++x) {
            Vec2 currentPos{x, y};

            if (currentPos == playerPos_) {
                cout << Color::Cyan << Color::Bold << "@" << Color::Reset << " ";
                continue;
            }

            bool isSecurity = false;
            for (const auto& sec : securityNodes_) {
                if (currentPos == sec) {
                    cout << Color::Red << Color::Bold << "X" << Color::Reset << " ";
                    isSecurity = true;
                    break;
                }
            }
            if (isSecurity) continue;

            char tile = grid_.getTile(x, y);
            if (tile == '#') {
                cout << Color::Gray << "#" << Color::Reset << " ";
            } else if (tile == '$') {
                cout << Color::Yellow << "$" << Color::Reset << " ";
            } else if (tile == 'E') {
                cout << Color::Green << "E" << Color::Reset << " ";
            } else {
                cout << ". ";
            }
        }
        cout << "\n";
    }

    cout << "\nStatus: " << statusMessage_ << "\n";
    cout << "Commands: [W/A/S/D] Move, [Q] Abort Run -> ";
}

bool GameEngine::processInput() {
    char input;
    if (!(cin >> input)) return false;

    int dx = 0, dy = 0;
    if (input == 'w' || input == 'W') dy = -1;
    else if (input == 's' || input == 'S') dy = 1;
    else if (input == 'a' || input == 'A') dx = -1;
    else if (input == 'd' || input == 'D') dx = 1;
    else if (input == 'q' || input == 'Q') return false;
    else return true;

    Vec2 target{playerPos_.x + dx, playerPos_.y + dy};

    if (grid_.isWalkable(target.x, target.y)) {
        playerPos_ = target;
        clockCycles_--;

        if (grid_.getTile(target.x, target.y) == '$') {
            dataRemaining_--;
            grid_.setTile(target.x, target.y, '.');
            statusMessage_ = "Data segment decrypted!";
        }

        if (grid_.getTile(target.x, target.y) == 'E') {
            if (dataRemaining_ == 0) {
                gameWon_ = true;
                gameOver_ = true;
                return true;
            } else {
                statusMessage_ = "Extraction denied: Retrieve all data caches first!";
            }
        }
    } else {
        statusMessage_ = "Action rejected: Firewall obstacle encountered.";
    }

    return true;
}

void GameEngine::updateEnemies() {
    for (auto& sec : securityNodes_) {
        Vec2 nextStep = grid_.getNextStepBFS(sec, playerPos_);
        sec = nextStep;

        if (sec == playerPos_) {
            gameOver_ = true;
            gameWon_ = false;
            statusMessage_ = "ALERT: Security Node captured your connection!";
            return;
        }
    }

    if (clockCycles_ <= 0) {
        gameOver_ = true;
        gameWon_ = false;
        statusMessage_ = "FAIL: Clock cycles exhausted. Trace completed by remote host.";
    }
}

void GameEngine::run() {
    while (!gameOver_) {
        render();
        if (!processInput()) break;
        if (!gameOver_) {
            updateEnemies();
        }
    }

    render();
    if (gameWon_) {
        cout << "\n" << Color::Green << Color::Bold
             << "[SYSTEM COMPROMISED: MISSION SUCCESSFUL]" << Color::Reset << "\n";
    } else {
        cout << "\n" << Color::Red << Color::Bold
             << "[CONNECTION TERMINATED: MISSION FAILED]" << Color::Reset << "\n";
    }
}
