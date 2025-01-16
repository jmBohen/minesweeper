# Minesweeper Game Report

## User Manual

### Game Ruless
Minesweeper is a game where the player uncovers squares on a board without hitting any mines. Each uncovered square shows the number of mines in the adjacent squares (0 to 8). The player can flag squares to mark potential mines, preventing accidental uncovering.

### How to Run the Program
1. **Build the Program**: Run `make` in the terminal to compile the program.
2. **Start the Game**: Execute `bin/minesweeper` to start the game.
3. **Choose Difficulty**: The program will prompt you to select a difficulty level:
   - Easy: 9x9 board with 10 mines
   - Medium: 16x16 board with 40 mines
   - Hard: 16x30 board with 99 mines
   - Custom: Define your own board sizse and number of mines
4. **Play the Game**: Use the following commands:
   - `f x y`: Flag/unflag the square at row `x` and column `y`
   - `r x y`: Reveal the square at row `x` and column `y`
5. **End of Game**: The game ends when all non-mine squares are revealed or a mine is uncovered. Enter your name to save your score.

### Running in File Mode
1. **Run the Program with File Input**: Execute `bin/minesweeper -f <file_path>` to load a board and moves from a file.
2. **File Format**: The file should contain the board layout and moves in the same format as terminal commands.
3. **Output**: The program will display the number of correct moves, the score, and whether the game was won or lost.

## Implementation Details

### Module Breakdown
- **board.c**: Handles board creation, settings, and game logic.
- **leaderboard.c**: Manages saving and displaying the leaderboard.
- **user_interface.c**: Manages user input and output.
- **game.c**: Main game loop and initialization.

### Key Functions
- **create_empty_board**: Initializes an empty board.
- **set_settings**: Sets the game settings based on user input.
- **initialize_board**: Sets up the board with mines after the first click.
- **reveal_square**: Reveals a square and its neighbors if there are no adjacent mines.
- **flag_square**: Flags or unflags a square.
- **check_if_game_over**: Checks if the game is over and handles the end game logic.
- **save_to_leaderboard**: Saves the player's score to the leaderboard.
- **print_leaderboard**: Displays the top 5 scores.

### Important Structures
- **Board**: Represents the game board, including size, number of mines, and squares.
- **Square**: Represents a single square on the board, including its state (revealed, flagged, mine) and the number of neighboring mines.

### Tests
- **test_board.c**: Tests board creation and game logic.
- **test_game.c**: Tests the main game loop and initialization.
- **test_leaderboard.c**: Tests saving and displaying the leaderboard.
- **test_user_interface.c**: Tests user input and output.

### Makefile
- **install_ncurses**: Checks and installs the ncurses library.
- **Compilation**: Compiles the source files into object files and links them to create the executable.
- **Clean**: Removes the compiled object files.

## Work Distribution
- **Team Member 1**: Implemented board creation, game logic, and file input handling.
- **Team Member 2**: Implemented user interface, leaderboard management, and testing.

## Summary
- **Implemented Features**: All required features were implemented, including different difficulty levels, file input mode, and leaderboard.
- **Challenges**: Handling user input and ensuring the first move is always safe were challenging. These were resolved by careful input validation and board initialization logic.
- **Conclusion**: The project was successfully completed with all functionalities working as expected. The game is enjoyable and provides a good challenge for players.
