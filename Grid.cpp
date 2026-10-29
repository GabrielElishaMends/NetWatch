#include "Grid.hpp"
#include <algorithm>

using namespace std;

Grid::Grid(int width, int height) : width_(width), height_(height) {
    loadDefaultMap();
}

void Grid::loadDefaultMap() {
    map_ = {
        "####################",
        "#@.....#.....$.....#",
        "#.###..#..#######..#",
        "#...#........#.....#",
        "###.#..####..#.###.#",
        "#...#..#..#..#...#.#",
        "#.###..#..#..###.#.#",
        "#......#..#....#...#",
        "#.######..####.###.#",
        "#....$.........#..E#",
        "####################"
    };
    height_ = static_cast<int>(map_.size());
    width_  = static_cast<int>(map_[0].size());
}

bool Grid::inBounds(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

bool Grid::isWalkable(int x, int y) const {
    if (!inBounds(x, y)) return false;
    return map_[y][x] != static_cast<char>(TileType::Firewall);
}

char Grid::getTile(int x, int y) const {
    if (!inBounds(x, y)) return '#';
    return map_[y][x];
}

void Grid::setTile(int x, int y, char tile) {
    if (inBounds(x, y)) {
        map_[y][x] = tile;
    }
}

Vec2 Grid::getNextStepBFS(Vec2 start, Vec2 target) const {
    if (start == target) return start;

    queue<Vec2> frontier;
    frontier.push(start);

    vector<vector<bool>> visited(height_, vector<bool>(width_, false));
    visited[start.y][start.x] = true;

    vector<vector<Vec2>> cameFrom(height_, vector<Vec2>(width_, {-1, -1}));

    const vector<Vec2> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    bool found = false;

    while (!frontier.empty()) {
        Vec2 curr = frontier.front();
        frontier.pop();

        if (curr == target) {
            found = true;
            break;
        }

        for (const auto& d : dirs) {
            Vec2 next{curr.x + d.x, curr.y + d.y};
            if (isWalkable(next.x, next.y) && !visited[next.y][next.x]) {
                visited[next.y][next.x] = true;
                cameFrom[next.y][next.x] = curr;
                frontier.push(next);
            }
        }
    }

    if (!found) return start;

    Vec2 step = target;
    while (cameFrom[step.y][step.x] != start && cameFrom[step.y][step.x] != Vec2{-1, -1}) {
        step = cameFrom[step.y][step.x];
    }
    return step;
}
