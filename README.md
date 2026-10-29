# NetWatch // Terminal Hacker

A tactical terminal-based infiltration puzzle built in modern C++. Navigate secure network sectors, decrypt sensitive data caches, and reach the extraction node before clock cycles expire or autonomous security patrols intercept your connection.

---

## Highlights

- **Breadth-First Search (BFS) AI**: Security nodes dynamically calculate the shortest traversal path toward the player each turn.
- **Cross-Platform ANSI Rendering**: Styled retro terminal interface with zero heavy external UI dependencies.
- **Clean Architecture**: Modular object-oriented separation between game engine, coordinate logic, and grid state.

---

## Quick Start

### Build with Code::Blocks
1. Open `NetWatch.cbp` in Code::Blocks.
2. Enable `-std=c++17` in **Settings** -> **Compiler...** -> **Compiler Flags**.
3. Press `F9` (Build and Run).

### Build with CMake / CLI
```bash
git clone [https://github.com/GabrielElishaMends/NetWatch.git](https://github.com/GabrielElishaMends/NetWatch.git)
cd NetWatch
cmake -B build
cmake --build build
./build/NetWatch

---

### How to Play
W / A / S / D: Move Up, Left, Down, Right
Q: Abort run
Objective: Collect all data caches ($) and make it to the extraction gateway (E) while evading security patrols (X) before your clock cycles hit zero.

###Tech Stack
Language: C++17
Paradigm: Object-Oriented Programming (OOP)
Algorithms: Graph Traversal (Breadth-First Search)
License: MIT