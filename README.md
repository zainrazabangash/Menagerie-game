# Menagerie - Match-3 Puzzle Game

A colorful match-3 puzzle game built with C++ and SFML (Simple and Fast Multimedia Library). Match three or more identical animal sprites to score points and progress through levels.

## Game Features

**Two Game Modes:**
- Normal Mode: Complete levels by filling the progress bar
- Time Trial Mode: Race against time with a decreasing progress bar

**Two Levels:**
- Level 1: Turn-based gameplay with 20 moves
- Level 2: Time-based challenge with 120 seconds

**Interactive Gameplay:**
- Click and drag to swap adjacent animal sprites
- Match 3 or more identical animals to clear them
- Chain reactions for bonus points
- Visual feedback with blue highlighting for matched pieces

## How to Play

1. Starting the Game: Click "Start Game" or "Time Trial" from the main menu
2. Making Moves: Click and drag to swap adjacent animal sprites
3. Scoring: Match 3+ identical animals in a row or column to score points
4. Progress: Fill the progress bar to advance to the next level
5. Winning: Complete Level 2 to win the game

## Requirements

- SFML 2.x (Simple and Fast Multimedia Library)
- C++ Compiler (GCC, Clang, or MSVC)
- Windows/Linux/macOS

## Installation & Setup

### Prerequisites
Install SFML library for your platform:
- Windows: Download from [SFML website](https://www.sfml-dev.org/download.php)
- Linux: `sudo apt-get install libsfml-dev` (Ubuntu/Debian)
- macOS: `brew install sfml`

### Compilation

**Using Makefile:**
```bash
make
make run
```

**Using CMake:**
```bash
mkdir build
cd build
cmake ..
make
./menagerie
```

**Manual compilation:**
```bash
g++ -o menagerie main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./menagerie
```

### Windows (Visual Studio)
1. Add SFML include and library directories to your project
2. Link against: `sfml-graphics`, `sfml-window`, `sfml-system`, `sfml-audio`
3. Copy `openal32.dll` to your executable directory

## Project Structure

```
├── main.cpp              # Main game source code
├── sprites/              # Game assets
│   ├── *.jpg            # Animal sprites and backgrounds
│   ├── *.png            # UI elements
│   └── *.wav            # Audio files
├── arial.ttf            # Font file
├── openal32.dll         # Audio library (Windows)
├── CMakeLists.txt       # CMake build configuration
├── Makefile             # Make build configuration
└── README.md            # This file
```

## Game Assets

The game uses various animal sprites including:
- Camel, Tiger, Hippo, Deer, Elephant, Giraffe, Goat

## Audio

- Background music support
- Sound effects for game interactions

## Scoring System

- Basic Match: 1 point per matched animal
- Chain Reactions: Bonus points for multiple matches
- Multiplier: Extra points for matches of 4+ animals

## Known Issues

- Some hardcoded coordinates for UI elements

## Contributing

Feel free to fork this project and submit pull requests for improvements!

## License

This project is open source. Please check the LICENSE file for details.

## Authors

- AI & DS Programming Fundamentals Project
- Fall 2022 Semester

---

**Note**: This game was created as part of a Programming Fundamentals course project focusing on C++ game development with SFML.
