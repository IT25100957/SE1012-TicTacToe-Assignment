# SE1012-TicTacToe-Assignment
C programming assignment for SE1012 - Modular Tic-Tac-Toe game with dynamic memory allocation, supporting 2-3 players and computer AI

##Progress in First commit
- Created a Repo and created a readme file

##Progress in Second Commit
- initializeBoard() → Fills the game board with spaces 
- displayBoard() → Displays the board in a grid format 
- Memory allocation and cleanup in main()

##Progress in Third Commit 
- BoardSize() → Gets board size from user (3-10) with validation
- initializeBoard() → Creates empty grid with spaces
- displayBoard() → Prints current state of the board in grid format
- MoveValidity() → Validates move input (bounds and empty cell check)
- makeMove() → Places player symbol on the board
- conditionWin() → Checks rows, columns, and diagonals for win condition
- conditionDraw() → Checks if the board is full (draw condition)
- logMove() → Records each move to game_log.txt file
- instruct() → Displays game instructions and welcome message
- playGame() → Main game loop with player turns and game logic
- Complete two-player Tic-Tac-Toe implementation
- Dynamic board allocation with proper memory management
- File logging of all game moves 
-  

##------------------PART 1 OF THE GAME COMPLETED----------------------##

##Progress in Fourth Commit
- logMove() → Records the entire board for each move of the player during a game to game_log.txt file in the game directory
- Added proper comments for the previous code 
- Removed the header files in the main program and made a seperate tictactoe.h file for the header

##Progress in Fifth Commit
- selectGameMode() → Game mode selection menu (Two Players vs User vs Computer)
- generateComputerMove() → Random computer move generation for AI opponent
- Enhanced playGame() → Handles both game modes with appropriate logic
- Computer AI implementation with random valid move selection
- Updated game logging to indicate selected mode (User vs User or User vs Computer)
- Different win messages for each game mode ("You win!" vs "Computer wins!")
- Added time.h header for random number generation
- Maintained all Part 1 functionality while adding new features
- Complete User vs Computer game mode implementation

##------------------PART 2 OF THE GAME COMPLETED----------------------##
