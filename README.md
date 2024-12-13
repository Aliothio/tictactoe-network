# PA8: TicTacToe on the server

### Learner Objectives
At the conclusion of this lab assignment, participants should be able to:
* Understand network programming basics (using sockets)
* Implementing a turn-based game

## Objective:
Develop a client-server Tic-Tac-Toe game in C, where the client sends user moves to the server, and the server responds by making its own moves. The server and client will communicate over a network using sockets.

## Instructions
You will write two C programs: one for the server and one for the client. The client allows a user to play Tic-Tac-Toe by entering moves, while the server acts as the second player and handles game logic. The game is played between the client (Player X) and the server (Player O), with the client taking the first turn.

## Requirements
### 1. Server Program (server.c)
The server should:
 * Accept incoming connections from a client.
 * Maintain the Tic-Tac-Toe board and handle game logic.
 * Make a move each time the client sends a move, ensuring valid gameplay.
 * Validate moves to ensure neither player can play on an already-occupied square.
 * Check for a win or a draw after each move.
 * Send updated board states to the client after each move.
#### Game flow:
 * The server initializes the board and listens for a connection.
 * The server waits to receive the client's move.
 * After receiving the client's move, the server makes its own move.
 * The server sends the updated board to the client after each turn.
 * The server checks if there is a winner or if the game is a draw and sends the game status to the client.

### 2. Client Program (client.c)
The client should:
 * Connect to the server using an IP address and port specified as command-line arguments.
 * Prompt the user to enter their move (row and column).
 * Send the user's move to the server and receive the updated board from the server after each move.
 * Display the updated board and game status (ongoing, win, or draw).
 * Continue allowing moves until the game concludes.
   
### 3. Game Rules
Tic-Tac-Toe is played on a 3x3 grid.
 * Player X (the client) and Player O (the server) take turns placing their symbol in an empty cell.
 * The game ends when:
 *   A player has three of their symbols in a row, column, or diagonal.
 *   All cells are filled without a winner (a draw).
 * 

### Other Requirements
- [ ] **Input validation**:  Only allow legal moves to be entered.  The row and column MUST be 1, 2, or 3. The selected board location must currently be empty (still have an `'*'` character).
- [ ] Commit your code throughout the development process. 
- [ ] Add file header comments and function header comments. Also, add line comments when necessary.

## Program output

**Example of the program Server side**
```
$ ./Server 6000
Waiting for the new player to connect...
The player is connected...
    1   2   3
1   *   *   *
2   *   *   *
3   *   *   *
Player turn...
Player enter: 1 1
    1   2   3
1   X   *   *
2   *   *   *
3   *   *   *
Computer turn...
Computer enter a row, column: 3 2
    1   2   3
1   X   *   *
2   *   *   *
3   *   O   *
Player turn...
Player enter: 2 2
    1   2   3
1   X   *   *
2   *   X   *
3   *   O   *
Computer turn...
Computer enter a row, column: 1 3
    1   2   3
1   X   *   O
2   *   X   *
3   *   O   *
Player turn...
Player enter: 3 3
    1   2   3
1   X   *   O
2   *   X   *
3   *   O   X
Player won!!!
Waiting for the new player to connect...

```

**Example of the program Client side**
```
$ ./Client 127.0.0.1 6000
Welcome to the TicTacToe game
    1   2   3
1   *   *   *
2   *   *   *
3   *   *   *
Player turn...
Enter a row, column: 1 1
You enter: 1 1
    1   2   3
1   X   *   *
2   *   *   *
3   *   *   *
Computer turn...
Computer enter a row, column: 3 2
    1   2   3
1   X   *   *
2   *   *   *
3   *   O   *
Player turn...
Enter a row, column: 2 2
You enter: 2 2
    1   2   3
1   X   *   *
2   *   X   *
3   *   O   *
Computer turn...
Computer enter a row, column: 1 3
    1   2   3
1   X   *   O
2   *   X   *
3   *   O   *
Player turn...
Enter a row, column: 3 3
You enter: 3 3
    1   2   3
1   X   *   O
2   *   X   *
3   *   O   X
Player won!!!

$ 

```


## Submitting Assignments
- [ ] It is VERY IMPORTANT that besides pushing the code to GitHub you still submit the GitHub URL of this lab assignment in Canvas. This allows the instructor to be notified of your final submission.

> **_NOTE: By submitting your code to be graded, you are stating that your submission does not violate the Academic Integrity Policy outlined in the syllabus._**
