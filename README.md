# Hangman-Game

Raffles University BAI22123 Objected-Oriented Programming Project  

---



## Project Details  

- **Subject:** Objected-Oriented Programming  
- **Language:** C++
- **Build Sysystem:** CMake
- **Library:** SFML
- **Game:** Console-based Hangman Game

---



## Project Structure

├── .vscode/  

│   └── tasks.json                 # VS Code build tasks  

├── src/  

│   ├── audio/  

│   │   └── background_music.wav  # Background music file  

│   ├── main.cpp                  # Entry point  

│   ├── modular.cpp               # Modular function logic

│   ├── server.cpp                # Server functions  

│   ├── function.h                # Function declarations  

│   └── server.h                  # Server function headers  

├── CMakeLists.txt                # CMake build configuration  

├── CMakePresets.json             # CMake preset build settings  

└── README.md                     # Project documentation  

---



## Requirement

- C++17 or higher
- CMake 3.10+
- Git
- SFML

---



## How to Compile and Run

1. Clone the Repository

   ```
   ```bash
   git clone <your-repo-url>
   cd HANGMAN-GAME
   ```
2. Configure with CMake

   ```
   cmake -S . -B build
   ```

   > Or, using a preset:
   >

   ```
   cmake --preset x64-debug
   ```
3. Build the Project

   ```
   cmake --build build
   ```

   > After building, the executable Hangman will be located in:  build/bin/Hangman.exe
   >
4. Run the Game

   ```
   ./build/bin/Hangman.exe
   or
   ./out/build/x64-debug/bin/Hangman.exe
   ```

   > Make sure the `background_music.wav` file is in the correct `audio/` subfolder or that it's accessible from your working directory.
   >


## How to Play

* The game randomly selects a word.
* You guess one letter at a time.
* You have limited chances to guess the word correctly.
* A running score and visual status are displayed.
* Background music plays using SFML audio.


## Troubleshooting

* If audio doesn't play, ensure:

  * The `/audio/background_music.wav` file exists at same directory of exe file
  * Your system has audio playback enabled
* If CMake fails to fetch SFML:

  * Ensure Git is installed
  * Check your internet connection
* On Windows, use **PowerShell** or **CMD** from VS Developer Prompt


## License

This project is licensed under the  **MIT License** .
