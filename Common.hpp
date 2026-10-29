#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

using namespace std;

struct Vec2 {
    int x{0};
    int y{0};

    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2& other) const {
        return !(*this == other);
    }
};

enum class TileType : char {
    Empty      = '.',
    Firewall   = '#',
    Player     = '@',
    DataCache  = '$',
    Security   = 'X',
    ExitNode   = 'E'
};

// ANSI Color codes
namespace Color {
    inline const string Reset   = "\033[0m";
    inline const string Red     = "\033[31m";
    inline const string Green   = "\033[32m";
    inline const string Yellow  = "\033[33m";
    inline const string Cyan    = "\033[36m";
    inline const string Gray    = "\033[90m";
    inline const string Bold    = "\033[1m";
}

// Function to activate ANSI color sequences in the Windows Command Prompt
inline void enableVirtualTerminal() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}
