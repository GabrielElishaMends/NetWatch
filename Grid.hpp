#pragma once
#include "Common.hpp"

using namespace std;

class Grid {
public:
    Grid(int width, int height);

    void loadDefaultMap();
    bool isWalkable(int x, int y) const;
    bool inBounds(int x, int y) const;

    char getTile(int x, int y) const;
    void setTile(int x, int y, char tile);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    Vec2 getNextStepBFS(Vec2 start, Vec2 target) const;

private:
    int width_;
    int height_;
    vector<string> map_;
};
