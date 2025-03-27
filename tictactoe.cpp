#include <iostream>
#include <random>
/**
 * @brief Class to represent a Tic Tac Toe game board. The game board is a 3x3 grid with each field being either free or occupied by a player.
 * @class GameBoard
 *  The 3x3 grid is an array of Fields which are either free or occupied by a player. Since a value can only be X or O, a boolean is used to represent the value. 
 * True represents X and False represents O. A boolean is also used to represent if the field is free or occupied. True represents free and False represents occupied.
 */
class GameBoard {
public:
    /**
     * @brief Struct to represent a field on the game board. A field can either be free or occupied by a player. A field can also have a value of X or O. represented by a boolean.
     */
    struct Field {
    bool isFree;
    bool isValueX;
    /**
     * @brief Constructor for the Field struct. Initializes the field as free and with is ValueX as false. This means that when checking for the winner i always 
     * have to check if the field is free or not. If the field is not free, then i can check if the value is X or O. If I do not do this it will lead to a bug.
     *  In hindsight, I should have just used a char to represent the value of the field. This would have made it easier.
     */
    Field() : isFree(true), isValueX(false) {};
    /**
     * @brief Getter for the isFree attribute of the field.
     * @return bool. True if the field is free, false if the field is occupied.
     */
    bool getFree() { return isFree; };
    /**
     * @brief Getter for the isValueX attribute of the field.
     * @return char. Returns 'X' if the field is occupied by X, 'O' if the field is occupied by O.
     */
    char getValue() {
        if(isValueX){
            return 'X';
        } else {
            return 'O';
        }
        };
    /**
     * @brief Setter for the isFree attribute of the field.
     * @param free bool. 
     */
    void setFree(bool free) { isFree = free; };
    /**
     * @brief Setter for the isValueX attribute of the field.
     * @param value bool. True if the field is shall be occupied by X, false if the field shall be occupied by O.
     */
    void setValue(bool value) { isValueX = value; };
    };

    Field board[3][3];
    /**
     * @brief Constructor for the GameBoard class. Initializes the game board as a 3x3 using the Field struct.
     */
    GameBoard(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                board[i][j] = Field();
            }
        }
    };
    /**
     * @brief Function to print a row of the game board. Uses ASCII art to represent the game board.
     * @param row int. The row to be printed
     * @return void
     * method cout.put was used since we were supposed to use ASCII art. I hope this satisfies the requirement. 32 represents a space, 
     * 124 represents a vertical line, 88 represents an X, 79 represents an O.
     */
    void printrow(int row){
        std::cout << row+1;
        std::cout.put(32).put(124);
        for(int i = 0; i < 3; i++){
            if (board[row][i].getFree()){
                std::cout.put(32).put(32).put(32).put(124);
            } else if (board[row][i].getValue()=='X'){
                std::cout.put(32).put(88).put(32).put(124);
            } else {
                std::cout.put(32).put(79).put(32).put(124);
            }
        }
        std::cout.put('\n');
    };
    /**
     * @brief Function to print a seperator line between the rows of the game board. Uses 13 dashes since to exactly match the provided screenshot.
     * @return void
     * method cout.put was used since we were supposed to use ASCII art. I hope this satisfies the requirement. 32 represents a space, 45 represents a dash.
     */
    void printseperator(){
        std::cout.put(32).put(32);
        for (int i = 0;i<13;i++){
            std::cout.put(45);
        }
        std::cout.put('\n');
    };
    /**
     * @brief Function to print the game board. Uses ASCII art to represent the game board.
     * @return void
     * First prints the column numbers and a seperator line. Then prints each row and a seperator line after each row.
     */
    void printBoard(){
        std::cout << "    1   2   3" << std::endl;
        printseperator();
        for (int k=0;k<3;k++){
            printrow(k);
            printseperator();
        }
    };
    /**
     * @brief Destructor for the GameBoard class.
     */
    ~GameBoard(){};
    /**
     * @brief Function to insert a value into a field on the game board.
     * @param row int. The row of the field to be inserted into.
     * @param column int. The column of the field to be inserted into.
     * @param c char. The value to be inserted into the field. 'X' for X, 'O' for O.
     * @return void
     * If the field is free, the value is inserted into the field. If the field is not free, the value is not inserted.
     */
    void insert(int row, int column, char c){
        if (board[row][column].getFree()){
            if(c == 'X'){
                board[row][column].setValue(true);
                board[row][column].setFree(false);
            } else if (c == 'O'){
                board[row][column].setValue(false);
                board[row][column].setFree(false);
            }
        }

    };
    /**
     * @brief Function to remove a value from a field on the game board.
     * @param row int. The row of the field to be removed from.
     * @param column int. The column of the field to be removed from.
     * @return void
     * Sets the field as free. Used for the minimax algorithm.
     */
    void refree(int row, int column){
        board[row][column].setFree(true);
    };
    /**
     * @brief Function to check if a field is free or occupied.
     * @param row int. The row of the field to be checked.
     * @param column int. The column of the field to be checked.
     * @return bool. True if the field is free, false if the field is occupied.
     */
    bool isFree(int row, int column){
        if (board[row][column].getFree()){
            return true;
        } else {
            return false;
        }
    };
    /**
     * @brief Function to check if a player has won the game.
     * @param c char. The player to be checked. 'X' for X, 'O' for O.
     * @return bool. True if the player has won, false if the player has not won.
     * Checks if the player has won by checking if the player has occupied all fields in a row, column or diagonal.
     */
    bool isWinner(char c){
        for (int i = 0; i < 3; i++){
            if (board[i][0].getValue() == board[i][1].getValue() && board[i][1].getValue() == board[i][2].getValue() && board[i][0].getValue() == c){
                if(board[i][0].getFree() == false && board[i][1].getFree() == false && board[i][2].getFree() == false){
                    return true;
                }
            }
            if (board[0][i].getValue() == board[1][i].getValue() && board[1][i].getValue() == board[2][i].getValue() && board[0][i].getValue() == c){
                if(board[0][i].getFree() == false && board[1][i].getFree() == false && board[2][i].getFree() == false){
                    return true;
                }
            }
        }
        if (board[0][0].getValue() == board[1][1].getValue() && board[1][1].getValue() == board[2][2].getValue() && board[0][0].getValue() == c){
            if(board[0][0].getFree() == false && board[1][1].getFree() == false && board[2][2].getFree() == false){
            return true;
            }
        }
        if (board[0][2].getValue() == board[1][1].getValue() && board[1][1].getValue() == board[2][0].getValue() && board[0][2].getValue() == c){
            if(board[0][2].getFree() == false && board[1][1].getFree() == false && board[2][0].getFree() == false){
            return true;
            }
        }
        return false;
    };
    /**
     * @brief Function to check if the game is a draw.
     * @return bool. True if the game is a draw, false if the game is not a draw.
     * Checks if the game is a draw by checking if all fields are occupied.
     */
    bool isDraw(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board[i][j].getFree()){
                    return false;
                }
            }
        }
        return true;
    };

};
/**
 * @brief Abstract class to represent a player in the Tic Tac Toe game.
 * @class Player
 *  The player class is an abstract class with a pure virtual function play. This function is implemented by the subclasses HumanPlayer and ComputerPlayer.
 */
class Player {
public:
    Player(){};
    virtual void play(GameBoard&) = 0;

};


/**
 * @brief Class to represent a human player in the Tic Tac Toe game.
 * @class HumanPlayer
 *  The HumanPlayer class is a subclass of the Player class.
 */
class HumanPlayer : public Player {
public:
    /**
     * @brief Constructor for the HumanPlayer class.
     */
    HumanPlayer(){};
    /**
     * @brief Function to play a turn in the game. The player is asked to select a row and column to insert their value into. This is always used by Player 1.
     * @param currentBoard GameBoard. The current game board.
     * @return void
     * The player is asked to select a row and column. If the field is free, the value is inserted into the field using the insert method of GameBoard.
     * If the field is not free, the player is asked to select a new field. This is repeated until the player selects a free field.
     * This is only for Player 1. Because of my earlier choices to use a boolean, this was necessary. Player 2 uses the playO method.
     */
    void play(GameBoard& currentBoard){
        int row;
        int column;
        bool turnSuccess = false;
        while(!turnSuccess){
        std::cout << "Select a row: ";
        std::cin >> row;
        std::cout << "Select a column: ";
        std::cin >> column;
        if(row < 1 || row > 3 || column < 1 || column > 3){
            std::cout << "Invalid field selection" << std::endl;
        }
        else if(!currentBoard.isFree(row-1, column-1)){
            std::cout << "Invalid field selection" << std::endl;
        }
        else {
            currentBoard.insert(row-1, column-1, 'X');
            turnSuccess = true;
        }
    }
    };
    /**
     * @brief Function to play a turn in the game. The player is asked to select a row and column to insert their value into. This is always used by Player 2.
     * @param currentBoard GameBoard. The current game board.
     * @return void
     * Same Logic as in the play Method. The only difference is that the value inserted is 'O' instead of 'X'.
     */
    void playO(GameBoard& currentBoard){
        int row;
        int column;
        bool turnSuccess = false;
        while(!turnSuccess){
        std::cout << "Select a row:";
        std::cin >> row;
        std::cout << "Select a column:";
        std::cin >> column;
        if(row < 1 || row > 3 || column < 1 || column > 3){
            std::cout << "Invalid field selection" << std::endl;
        }
        else if(!currentBoard.isFree(row-1, column-1)){
            std::cout << "Invalid field selection" << std::endl;
        }
        else {
            currentBoard.insert(row-1, column-1, 'O');
            turnSuccess = true;
        }
    }
    };
};
/**
 * @brief Class to represent a computer player in the Tic Tac Toe game.
 * @class ComputerPlayer
 *  The ComputerPlayer class is a subclass of the Player class.
 */
class ComputerPlayer : public Player {
public:
    /**
     * @brief Struct to represent a move in the game. This is necessary for the minimax algorithm.
     */
    struct Move {
        int row;
        int column;
    };
    bool rdm;
    /**
     * @brief Constructor for the ComputerPlayer class.
     * @param prdm bool. True if the computer player is a random player, false if the computer uses minimax.
     */
    ComputerPlayer(bool prdm){
        rdm = prdm;
    };
    /**
     * @brief Getter for the rdm attribute of the ComputerPlayer class.
     * @return bool. True if the computer player is a random player, false if the computer uses minimax.
     */
    bool getRdm(){
        return rdm;
    };
    /**
     * @brief Function to play a turn in the game. The computer selects a random field to insert their value into.
     * @param currentBoard GameBoard. The current game board.
     * @param c char. The value of the computer. To allow for the algorithm to be player 1 and player 2
     * @return void
     * The computer selects a random row and column. If the field is free, the value is inserted into the field using the insert method of GameBoard.
     * If the field is not free, the computer selects a new field. This is repeated until the computer selects a free field.
     * I have chosen not to print every error message for the computer since it could be a lot of messages if the values are selected randomly.
     */
    void play(GameBoard& currentBoard){
        if(rdm){
        int row;
        int column;
        bool turnSuccess = false;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distr(1,3);
        while(!turnSuccess){
        if(rdm){
            row = distr(gen);
            column = distr(gen);
        }
        if(row < 1 || row > 3 || column < 1 || column > 3){
            std::cout << "Invalid field selection" << std::endl;
        }
        else if(currentBoard.isFree(row-1, column-1)){
            currentBoard.insert(row-1, column-1, 'O');
            turnSuccess = true;
        }

    }
        }
        else {
            playMinimaxO(currentBoard);
        }
    };
    /**
     * @brief Minimax algorithm to find the best score for a move. The algorithm goes through all possible moves and returns a score for the best move possible
     * from the current game state.
     * @param currentBoard GameBoard. The current game board.
     * @param depth int. The depth of the algorithm. Similar to the depth of a tree.
     * @param isMax bool. True if the computer is maximizing, false if the computer is minimizing. Common in the minimax algorithm.
     * @param c char. The value of the computer. To allow for the algorithm to be player 1 and player 2
     * @param other char. The value of the other player. To allow for the algorithm to be player 1 and player 2
     * @return int The score of the best move.
     * 
     */
    int minimax(GameBoard& currentBoard, int depth, bool isMax, char c, char other){
        int score = 0;
       
        if (currentBoard.isWinner(other)){
            score = score -10;
        }
        else if(currentBoard.isWinner(c)){
            score= score + 10;
        }
        if(score == 10 || score == -10){
            return score;
        }
        if(currentBoard.isDraw()){
            return 0;
        }
        if(isMax){
            int best = -1000;
            for (int i = 0; i<3 ; i++){
                for (int j = 0; j<3; j++){
                    if(currentBoard.isFree(i,j)){
                        currentBoard.insert(i,j,c);
                        best = std::max(best, minimax(currentBoard, depth+1, !isMax,c,other));
                        currentBoard.refree(i,j);
                    }
                }
            }
            return best;
        }
        else {
            int best = 1000;
            for (int i = 0; i<3 ; i++){
                for (int j = 0; j<3; j++){
                    if(currentBoard.isFree(i,j)){
                        currentBoard.insert(i,j,other);
                        best = std::min(best, minimax(currentBoard, depth+1, !isMax,c,other));
                        currentBoard.refree(i,j);
                    }
                }
            }
            return best;
        }
    };
    /**
     * @brief Function to find the best move for the computer using the minimax algorithm.
     * @param currentBoard GameBoard. The current game board.
     * @param c char. The value of the computer. To allow for the algorithm to be player 1 and player 2
     * @param other char. The value of the other player. To allow for the algorithm to be player 1 and player 2
     * @return Move. The best move for the computer.
     * The function goes through all possible moves and uses minimax to find the best possible move after the current move was made. 
     * After simulating all possible moves for a single move, the function updates the best move if a better move is found. This is repeated for all possible moves.
     * The best move is then returned.
     */
    Move findBestMove(GameBoard& currentBoard,char c,char other){
        int bestVal = -1000;
        Move bestMove;
        bestMove.row = -1;
        bestMove.column = -1;
        for (int i = 0; i<3 ; i++){
            for (int j = 0; j<3; j++){
                if(currentBoard.isFree(i,j)){
                    currentBoard.insert(i,j,c);
                    int moveVal = minimax(currentBoard, 0, false,c,other);
                    currentBoard.refree(i,j);
                    if (moveVal > bestVal){
                        bestMove.row = i;
                        bestMove.column = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    };
    /**
     * @brief Function to play a turn in the game. The computer selects the best move using the minimax algorithm.
     * @param currentBoard GameBoard. The current game board.
     * @return void
     * The computer selects the best move using the findBestMove method.
     */
    void playMinimaxO(GameBoard& currentBoard){
        bool turnSuccess = false;
        Move bestMove = findBestMove(currentBoard,'O','X');
        while(!turnSuccess){
        if(currentBoard.isFree(bestMove.row, bestMove.column)){
            currentBoard.insert(bestMove.row, bestMove.column, 'O');
            turnSuccess = true;
        }

    }
    };
    void playMinimaxX(GameBoard& currentBoard){
        bool turnSuccess = false;
        Move bestMove = findBestMove(currentBoard,'X','O');
        while(!turnSuccess){
        if(currentBoard.isFree(bestMove.row, bestMove.column)){
            currentBoard.insert(bestMove.row, bestMove.column, 'X');
            turnSuccess = true;
        }
        }
    };  
};
/**
 * @brief Class to handle a running game.
 * @class Game
 */
class Game {
    public:
    /**
     * @brief Starting a Human vs Human game.
     * @param player1 HumanPlayer*. The first player.
     * @param player2 HumanPlayer*. The second player.
     * @return void
     */
    void startHvH(HumanPlayer* player1, HumanPlayer* player2){
        GameBoard game = GameBoard();

        game.printBoard();
        std::cout << "Player 1: X" << std::endl;
        std::cout << "Player 2: O" << std::endl;
        bool running = true;
        while (running){
            std::cout << "Player 1's turn" << std::endl;
            player1->play(game);
            game.printBoard();
            if (game.isWinner('X')){
                std::cout << "Winner is: Player 1" << std::endl;
                running = false;
                break;
            }
            if(game.isDraw()){
                std::cout << "A draw!" << std::endl;
                running = false;
                break;
            }
            std::cout << "Player 2's turn" << std::endl;
            player2->playO(game);
            game.printBoard();
            if (game.isWinner('O')){
                std::cout << "Winner is: Player 2" << std::endl;
                running = false;
                break;
            }
            
        }
    };
    /**
     * @brief Starting a Human vs Computer game.
     * @param player1 HumanPlayer*. The first player.
     * @param player2 ComputerPlayer*. The second player.
     * @return void
     */
    void startHvC(HumanPlayer* player1, ComputerPlayer* player2){
        GameBoard game = GameBoard();

        game.printBoard();
        std::cout << "Player 1: X" << std::endl;
        std::cout << "Player 2: O" << std::endl;
        bool running = true;
        while (running){
            std::cout << "Player 1's turn" << std::endl;
            player1->play(game);
            game.printBoard();
            if (game.isWinner('X')){
                std::cout << "Winner is: Player 1" << std::endl;
                running = false;
                break;
            }
            if(game.isDraw()){
                std::cout << "A draw!" << std::endl;
                running = false;
                break;
            }
            std::cout << "Player 2's turn" << std::endl;
            player2->play(game);
            game.printBoard();
            if (game.isWinner('O')){
                std::cout << "Winner is: Player 2" << std::endl;
                running = false;
                break;
            }
            
        }
    };
    /**
     * @brief Starting a Computer vs Computer game.
     * @param player1 ComputerPlayer*. The first player.
     * @param player2 ComputerPlayer*. The second player.
     * @return void
     */
    void startCvC(ComputerPlayer* player1, ComputerPlayer* player2){
        GameBoard game = GameBoard();
        game.printBoard();
        std::cout << "Player 1: X" << std::endl;
        std::cout << "Player 2: O" << std::endl;
        bool running = true;
        while (running){
            std::cout << "Player 1's turn" << std::endl;
            player1->playMinimaxX(game);
            game.printBoard();
            if (game.isWinner('X')){
                std::cout << "Winner is: Player 1" << std::endl;
                running = false;
                break;
            }
            if(game.isDraw()){
                std::cout << "A draw!" << std::endl;
                running = false;
                break;
            }
            std::cout << "Player 2's turn" << std::endl;
            player2->play(game);
            game.printBoard();
            if (game.isWinner('O')){
                std::cout << "Winner is: Player 2" << std::endl;
                running = false;
                break;
            }
            
        }
    };
};
/**
 * @brief Main function to run the program.
 * @return int. 0 if the program runs successfully, 1 if the program fails.
 * This method is always running in a loop. The user is asked to choose what game mode they want to play. 
 * Once a game finishes the loop is started over again.
 */
int main() {
    bool programRunning = true;
    while(programRunning){
    std::cout << "Choose your game mode." << std::endl;
    std::cout << "(1) Human vs Human" << std::endl;
    std::cout << "(2) Human vs Computer (Minimax)" << std::endl;
    std::cout << "(3) Human vs Computer (Random)" << std::endl;
    std::cout << "(4) Computer (Minimax) vs Computer (Minimax)" << std::endl;
    std::cout << "(5) Exit Program" << std::endl;
    int choice;
    std::cin >> choice;
    if(std::cin.fail()){
        std::cout << "Invalid input. Exiting program." << std::endl;
        return 1;
    }
    switch (choice){
        case 1:
        {
            Game CurrentGame = Game();
            HumanPlayer player1 = HumanPlayer();
            HumanPlayer player2 = HumanPlayer();
            CurrentGame.startHvH(&player1, &player2);
            break;
        }
        case 2:
        {
            Game CurrentGame = Game();
            HumanPlayer player1 = HumanPlayer();
            ComputerPlayer player2 = ComputerPlayer(false);
            CurrentGame.startHvC(&player1, &player2);
            break;
            }
        case 3:
        {
            Game CurrentGame = Game();
            HumanPlayer player1 = HumanPlayer();
            ComputerPlayer player2 = ComputerPlayer(true);
            CurrentGame.startHvC(&player1, &player2);
            break;
            }
        case 4:
        {
            Game CurrentGame = Game();
            ComputerPlayer player1 = ComputerPlayer(false);
            ComputerPlayer player2 = ComputerPlayer(false);
            CurrentGame.startCvC(&player1, &player2);
            break;
            }
        case 5:
        {
            std::cout << "Exiting program." << std::endl;
            return 0;
            }
        default:
        {
            std::cout << "Invalid input. Exiting program." << std::endl;
            return 1;
            }
    }

    }
    return 0;
};