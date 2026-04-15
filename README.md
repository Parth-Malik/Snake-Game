***

# Snake-Game in C

A classic Snake game implemented entirely in C for the Windows command prompt. This project demonstrates foundational game development concepts, including real-time game loops, state management, and memory manipulation. 

A primary focus of this project was optimizing terminal rendering. Instead of relying on standard screen-clearing functions that cause severe flickering, the game utilizes the Windows API to manipulate the console cursor, resulting in a smooth, continuous frame rate.

## Features

* **Real-Time Input Handling:** Utilizes non-blocking keyboard input to maintain a continuous game loop.
* **Flicker-Free Rendering:** Implements cursor repositioning via `<windows.h>` to overwrite previous frames directly, eliminating console strobe effects.
* **Dynamic Body Growth:** Array-based shifting logic to manage the snake's body segments as it consumes coordinates.
* **Collision Detection:** Standard boundary and self-intersection tracking.

## Prerequisites

* **Operating System:** Windows (The code relies on `<windows.h>` and `<conio.h>`).
* **Compiler:** GCC (MinGW) or any standard C compiler.

## Compilation and Execution

1. Clone the repository to your local machine.
2. Open your terminal or command prompt in the project directory.
3. Compile the code using GCC:
   ```bash
   gcc Terminal_Snake.c
   ```
4. Run the executable:
   ```bash
   .\a.exe
   ```

## Controls

* `W` - Move Up
* `S` - Move Down
* `A` - Move Left
* `D` - Move Right
* `Q` - Quit Game

## Technical Overview

* **Structs:** Custom `Pair` structs are used to handle X and Y coordinates for the snake body, movement direction, and grid positioning.
* **Windows API:** `SetConsoleCursorPosition` and `SetConsoleCursorInfo` are utilized to manage the standard output handle, hiding the blinking terminal cursor and resetting its position to `0,0` at the start of every frame.
* **Tick Rate:** The game loop uses `Sleep()` to establish a consistent frame rate, decoupling the logic execution speed from the CPU clock speed.
