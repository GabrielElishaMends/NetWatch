#include "GameEngine.hpp"
#include "Common.hpp"

using namespace std;

int main() {
    enableVirtualTerminal(); // Turns on color & screen-clearing support

    GameEngine engine;
    engine.run();
    return 0;
}
