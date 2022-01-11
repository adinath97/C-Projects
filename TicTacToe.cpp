#include <iostream>
#include <algorithm>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

vector< vector<int> > IntroductionToTicTacToe(vector< vector<int> > boardDemo);
bool DetermineWhoGoesFirst(char* const playerChar,char* const computerChar);
void PlayGame(vector< vector<char> > gameBoard,bool* playerChoice,char* const playerChar, char* const computerChar);
void CheckIfGameOver(vector< vector<char> > &gameBoard,char &winningChar, char &playerChar,char &computerChar, bool &gameOver, int &turns);
void GetPlayerInput(vector< vector<char> > &gameBoard);
void PlayComputerMove(vector< vector<char> > &gameBoard, int &tripletCount,int &nextSpotRow,int &nextSpotColumn, bool &gameOver,bool &spotFound, bool &spotTaken,char &winningChar,char &playerChar, bool &playerFirst,int &turns,char &computerChar);
void CurrentBoardSetUp(vector< vector<char> > &gameBoard);

vector< vector<int> > boardDemo(3, vector<int> (3,1));
vector< vector<char> > gameBoard(3, vector<char> (3,'E'));
bool spotTaken = false, spotFound = false, playerFirst = false, gameOver = false, validInput = false, tripletFound = false;
char playerChar, computerChar, winningChar;

int main() {
    boardDemo = IntroductionToTicTacToe(boardDemo);
    playerFirst = DetermineWhoGoesFirst(&playerChar,&computerChar);
    PlayGame(gameBoard,&playerFirst,&playerChar,&computerChar);
    return 0;
}

vector< vector<int> > IntroductionToTicTacToe(vector< vector<int> > boardDemo) {
    int counter = 1;
    cout << "\nWELCOME TO TIC TAC TOE -- A TIMELESS CLASSIC!\n" << endl;
    cout << "YOUR GOAL IS TO COMPLETE 3 CONNECTED X'S OR O'S; THE FIRST TO DO SO WILL WIN THE GAME. X GOES FIRST, FOLLOWED BY O\n" << endl;
    cout << "TO GO FOR THE APPROPRIATE SPOT IN ON THE BOARD, ENTER THE APPROPRIATE NUMBER AS SHOWN IN THE GRID BELOW (FOR INSTANCE, TO GO FOR THE UPPER LEFT CORNER, ENTER 1):" << endl;
    cout << "\n---------------" << endl;
    for(int i = 0; i < 3; i++) {
        cout << " | ";
        for(int j = 0; j < 3; j++) {
            boardDemo[i][j] = counter;
            cout << boardDemo[i][j] << " | ";
            counter++;
        }
        cout << "\n---------------" << endl;
    }
    cout << endl;
    return boardDemo;
}

bool DetermineWhoGoesFirst(char* const playerChar,char* const computerChar) {
    char playerChoice;
    cout << "WE SHALL FLIP A COIN TO DETERMINE WHO GOES FIRST. ENTER 'H' FOR HEADS OR 'T' FOR TAILS: ";
    cin >> playerChoice;
    cout << endl;
    if(playerChoice == 'H') {
        *playerChar = 'X';
        *computerChar = 'O';
        return true;
    } else {
        *playerChar = 'O';
        *computerChar = 'X';
        return false;
    }
}

void CurrentBoardSetUp(vector< vector<char> > &gameBoard) {
    //display current board set up
    cout << "\nTHIS IS THE CURRENT BOARD SET UP:\n";
    cout << "\n---------------" << endl;
    for(int i = 0; i < 3; i++) {
        cout << " | ";
        for(int j = 0; j < 3; j++) {
            if(gameBoard[i][j] != 'E') {
                cout << gameBoard[i][j] << " | ";
            }
            else {
                cout << "  | ";
            }
        }
        cout << "\n---------------" << endl;
    }
    cout << endl;
}

void GetPlayerInput(vector< vector<char> > &gameBoard) {
    bool validInput = false;
    int counter = 1, playerInput = 0;
    //player makes a move
    //get valid player input
    do {
        counter = 1;
        cout << "ENTER A SPOT TO OCCUPY (1-9): ";
        cin >> playerInput;

        //update board with playerInput
        //loop through board and check if desired spot is open, and if so, update with player's character
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(counter == playerInput) {
                    if(gameBoard[i][j] != playerChar && gameBoard[i][j] != computerChar) {
                        validInput = true;
                        gameBoard[i][j] = playerChar;
                    }
                }
                counter++;
                if(i == 2 && j == 2 && !validInput) {
                    cout << "\nTHE SPOT IS TAKEN OR IS INVALID. PLEASE CHOOSE A DIFFERENT SPOT";
                }
            }
        }
    } while(!validInput);
}

void CheckIfGameOver(vector< vector<char> > &gameBoard,char &winningChar, char &playerChar,char &computerChar, bool &gameOver, int &turns) {
    //check for completed triplets (ie if game is over!)
    for(int i = 0; i < 3; i++) {
        if(gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][2] != 'E') {
            tripletFound = true;
            winningChar = gameBoard[i][0];
        }
    }

    for(int i = 0; i < 3; i++) {
        //check columns for triplets
        if(gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i] && gameBoard[2][i] != 'E') {
            tripletFound = true;
            winningChar = gameBoard[0][i];
        }
    }

    //check diagonals
    if(!tripletFound) {
        //cout << "HERE 7" << endl;
        if(gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2] && gameBoard[2][2] != 'E') {
            tripletFound = true;
            winningChar = gameBoard[0][0];
        }
    }
    if(!tripletFound) {
        //cout << "HERE 8" << endl;
        if(gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[2][0] != 'E') {
            tripletFound = true;
            winningChar = gameBoard[0][2];
        }
    }

    turns++;
    if(turns >= 9) {
        gameOver = true;
        cout << "IT'S A TIE!" << endl << endl;
    }

    if(tripletFound) {
        gameOver = true;
        if(winningChar == playerChar) {
            cout << "GAME OVER! YOU HAVE WON THE GAME!\n" << endl;
        } else if(winningChar == computerChar) {
            cout << "GAME OVER! THE COMPUTER HAS TRIUMPED!\n" << endl;
        }
    }
}

void PlayComputerMove(vector< vector<char> > &gameBoard, int &tripletCount,int &nextSpotRow,int &nextSpotColumn, bool &gameOver,bool &spotFound, bool &spotTaken,char &winningChar,char &playerChar, bool &playerFirst,int &turns,char &computerChar) {
    if(!gameOver) {
        //computer makes a move
            cout << "\nTHE COMPUTER HAS MADE ITS MOVE, AND THIS IS THE CURRENT BOARD SET UP:\n";

            //register computer move
            //for each turn, check if computer is close to completing a triplet, and if so, go for it
            for(int i = 0; i < 3; i++) {
                //cout << "HERE 1" << endl;
                //check rows for triplets
                if(i == 0) {
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[i][j] == computerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[i][j] == 'E') {
                            spotTaken = true;
                            nextSpotRow = i;
                            nextSpotColumn = j;
                        }
                        if(tripletCount == 2) {
                            if(spotTaken) {
                                //cout << "HERE 1" << endl;
                                spotFound = true;
                            }
                        }
                    }
                }
                if(i == 1 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[i][j] == computerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[i][j] == 'E') {
                            spotTaken = true;
                            nextSpotRow = i;
                            nextSpotColumn = j;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                //cout << "HERE 2" << endl;
                                spotFound = true;
                            }
                        }
                    }
                }
                if(i == 2 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[i][j] == computerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[i][j] == 'E') {
                            spotTaken = true;
                            nextSpotRow = i;
                            nextSpotColumn = j;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                //cout << "HERE 3" << endl;
                                spotFound = true;
                            }
                        }
                    }
                }
            }

            for(int i = 0; i < 3; i++) {
                //cout << "HERE 2" << endl;
                //check columns for triplets
                if(i == 0 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        //cout << gameBoard[j][i] << endl;
                        if(gameBoard[j][i] == computerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[j][i] == 'E') {
                            spotTaken = true;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                //cout << "HERE 4" << endl;
                                spotFound = true;
                            }
                        }
                    }
                }
                if(i == 1 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        //cout << gameBoard[j][i] << endl;
                        if(gameBoard[j][i] == computerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[j][i] == 'E') {
                            spotTaken = true;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                //cout << "HERE 5" << endl;
                                spotFound = true;
                            }
                        }
                    }
                }
                if(i == 2 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        //cout << gameBoard[j][i] << endl;
                        if(gameBoard[j][i] == computerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[j][i] == 'E') {
                            spotTaken = true;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                //cout << "HERE 6" << endl;
                                spotFound = true;
                            }
                        }
                    }
                }
            }

            //check diagonals
            if(!spotFound) {
                //cout << "HERE 3" << endl;
                tripletCount = 0;
                spotTaken = false;
                for(int i = 0; i < 3; i++) {
                    if(gameBoard[i][i] == computerChar) {
                        tripletCount++;
                    }
                    if(gameBoard[i][i] == 'E') {
                        spotTaken = true;
                        nextSpotRow = i;
                        nextSpotColumn = i;
                    }
                    if(tripletCount == 2) {
                        if(spotTaken) {
                            //cout << "HERE 7" << endl;
                            spotFound = true;
                        }
                    }
                }
            }
            if(!spotFound) {
                //cout << "HERE 4" << endl;
                tripletCount = 0;
                spotTaken = false;
                for(int i = 0; i < 3; i++) {
                    if(gameBoard[2 - i][i] == computerChar) {
                        tripletCount++;
                    }
                    if(gameBoard[2 - i][i] == 'E') {
                        spotTaken = true;
                        nextSpotRow = 2 - i;
                        nextSpotColumn = i;
                    }
                    if(tripletCount == 2) {
                        if(spotTaken) {
                            //cout << "HERE 8" << endl;
                            spotFound = true;
                        }
                    }
                }
            }

            if(spotFound) {
                if(gameBoard[nextSpotRow][nextSpotColumn] == 'E') {
                    gameBoard[nextSpotRow][nextSpotColumn] = computerChar;
                }
            }
                
            //for each turn, next check if player is close to completing a triplet, and if so, stop them
            if(!spotFound) {
                for(int i = 0; i < 3; i++) {
                //check rows for triplets
                    /* cout << "HERE 1" << endl;
                    if(spotFound) {
                        cout << "SPOT FOUND!" << endl;
                    } */
                    if(i == 0) {
                        tripletCount = 0;
                        spotTaken = false;
                        for(int j = 0; j < 3; j++) {
                        if(gameBoard[i][j] == playerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[i][j] == 'E') {
                            spotTaken = true;
                            nextSpotRow = i;
                            nextSpotColumn = j;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                spotFound = true;
                            }
                        }
                    }
                    }
                    if(i == 1 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[i][j] == playerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[i][j] == 'E') {
                            spotTaken = true;
                            nextSpotRow = i;
                            nextSpotColumn = j;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                spotFound = true;
                            }
                        }
                    }
                }
                    if(i == 2 && !spotFound) {
                        tripletCount = 0;
                        spotTaken = false;
                        for(int j = 0; j < 3; j++) {
                            if(gameBoard[i][j] == playerChar) {
                                tripletCount++;
                            }
                            if(gameBoard[i][j] == 'E') {
                                spotTaken = true;
                                nextSpotRow = i;
                                nextSpotColumn = j;
                            }
                            if(tripletCount == 2) {
                                //cout << "HERE 1" << endl;
                                if(spotTaken) {
                                    spotFound = true;
                                }
                            }
                        }
                }
                }

                for(int i = 0; i < 3; i++) {
                //check columns for triplets
                    /* cout << "HERE 2" << endl;
                    if(spotFound) {
                        cout << "SPOT FOUND!" << endl;
                    } */
                    if(i == 0 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        //cout << gameBoard[j][i] << endl;
                        if(gameBoard[j][i] == playerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[j][i] == 'E') {
                            spotTaken = true;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                spotFound = true;
                            }
                        }
                    }
                }
                    if(i == 1 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        //cout << gameBoard[j][i] << endl;
                        if(gameBoard[j][i] == playerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[j][i] == 'E') {
                            spotTaken = true;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                spotFound = true;
                            }
                        }
                    }
                }
                    if(i == 2 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        //cout << gameBoard[j][i] << endl;
                        if(gameBoard[j][i] == playerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[j][i] == 'E') {
                            spotTaken = true;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            if(spotTaken) {
                                spotFound = true;
                            }
                        }
                    }
                }
                }

                //check diagonals
                if(!spotFound) {
                    //cout << "HERE 3" << endl;
                    //cout << "HERE 7" << endl;
                    tripletCount = 0;
                    spotTaken = false;
                    for(int i = 0; i < 3; i++) {
                        if(gameBoard[i][i] == playerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[i][i] == 'E') {
                            spotTaken = true;
                            nextSpotRow = i;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            if(spotTaken) {
                                spotFound = true;
                            }
                        }
                    }
                }
                if(!spotFound) {
                    //cout << "HERE 4" << endl;
                    //cout << "HERE 8" << endl;
                    tripletCount = 0;
                    spotTaken = false;
                    for(int i = 0; i < 3; i++) {
                        if(gameBoard[2 - i][i] == playerChar) {
                            tripletCount++;
                        }
                        if(gameBoard[2 - i][i] == 'E') {
                            spotTaken = true;
                            nextSpotRow = 2 - i;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            if(spotTaken) {
                                spotFound = true;
                            }
                        }
                    }
                }

                if(spotFound) {
                    //cout << "SPOT FOUND!" << endl;
                if(gameBoard[nextSpotRow][nextSpotColumn] == 'E') {
                    gameBoard[nextSpotRow][nextSpotColumn] = computerChar;
                }
            }

            }

            //if neither the player nor the computer is capable of getting a triplet next turn, find the best possible open triplet
            if(!spotFound) {
                //check for potential triplet
                for(int i = 0; i < 3; i++) {
                //check rows for triplets
                    if(i == 0) {
                        tripletCount = 0;
                        spotTaken = false;
                        for(int j = 0; j < 3; j++) {
                            if(gameBoard[i][j] == 'E') {
                                //cout << i << "," << j << endl;
                                tripletCount++;
                                nextSpotRow = i;
                                nextSpotColumn = j;
                            }
                            if(tripletCount == 2) {
                                //cout << "HERE 1" << endl;
                                spotFound = true;
                            }
                        }
                    }
                    if(i == 1 && !spotFound) {
                        tripletCount = 0;
                        spotTaken = false;
                        for(int j = 0; j < 3; j++) {
                            if(gameBoard[i][j] == 'E') {
                                //cout << i << "," << j << endl;
                                tripletCount++;
                                nextSpotRow = i;
                                nextSpotColumn = j;
                            }
                            if(tripletCount == 2) {
                                //cout << "HERE 2" << endl;
                                spotFound = true;
                            }
                        }
                    }
                    if(i == 2 && !spotFound) {
                        tripletCount = 0;
                        spotTaken = false;
                        for(int j = 0; j < 3; j++) {
                            if(gameBoard[i][j] == 'E') {
                                //cout << i << "," << j << endl;
                                tripletCount++;
                                nextSpotRow = i;
                                nextSpotColumn = j;
                            }
                            if(tripletCount == 2) {
                                //cout << "HERE 3" << endl;
                                spotFound = true;
                            }
                        }
                    }
                }

                for(int i = 0; i < 3; i++) {
                //check columns for triplets
                    if(i == 0 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[j][i] == 'E') {
                            //cout << j << "," << i << endl;
                            tripletCount++;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 4" << endl;
                            spotFound = true;
                        }
                    }
                }
                    if(i == 1 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[j][i] == 'E') {
                            //cout << j << "," << i << endl;
                            tripletCount++;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 5" << endl;
                            spotFound = true;
                        }
                    }
                }
                    if(i == 2 && !spotFound) {
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[j][i] == 'E') {
                            //cout << j << "," << i << endl;
                            tripletCount++;
                            nextSpotRow = j;
                            nextSpotColumn = i;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 6" << endl;
                            spotFound = true;
                        }
                    }
                }
                }

                //check diagonals
                if(!spotFound) {
                //cout << "HERE 7" << endl;
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[j][j] == 'E') {
                            tripletCount++;
                            nextSpotRow = j;
                            nextSpotColumn = j;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            spotFound = true;
                        }
                    }
                }
                if(!spotFound) {
                //cout << "HERE 8" << endl;
                    tripletCount = 0;
                    spotTaken = false;
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[2 - j][j] == 'E') {
                            tripletCount++;
                            nextSpotRow = 2 - j;
                            nextSpotColumn = j;
                        }
                        if(tripletCount == 2) {
                            //cout << "HERE 1" << endl;
                            spotFound = true;
                        }
                    }
                }

                if(spotFound) {
                    if(gameBoard[nextSpotRow][nextSpotColumn] == 'E') {
                        gameBoard[nextSpotRow][nextSpotColumn] = computerChar;
                    }
                }
            }

            //if all else fails, find random spot!
            if(!spotFound) {
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        if(gameBoard[i][j] == 'E' && !spotFound) {
                            spotFound = true;
                            nextSpotRow = i;
                            nextSpotColumn = j;
                        }
                    }
                }

                if(spotFound) {
                    if(gameBoard[nextSpotRow][nextSpotColumn] == 'E') {
                        gameBoard[nextSpotRow][nextSpotColumn] = computerChar;
                    }
                }
            }
            
            //display current board set up
            cout << "\n---------------" << endl;
            for(int i = 0; i < 3; i++) {
                cout << " | ";
                for(int j = 0; j < 3; j++) {
                    if(gameBoard[i][j] != 'E') {
                        cout << gameBoard[i][j] << " | ";
                    }
                    else {
                        cout << "  | ";
                    }
                }
                cout << "\n---------------" << endl;
            }
            cout << endl;
        
            CheckIfGameOver(gameBoard,winningChar,playerChar,computerChar,gameOver,turns);
    }
}

void PlayGame(vector< vector<char> > gameBoard,bool* const playerChoice,char* const playerChar, char* const computerChar) {
    int tripletCount = 0, nextSpotRow = 100, nextSpotColumn = 100, turns = 0;

    CurrentBoardSetUp(gameBoard);

    do {
        spotFound = false;
        spotTaken = false;
        nextSpotColumn = 100;
        nextSpotRow = 100;
        tripletCount = 0;

        if(playerFirst) {
            GetPlayerInput(gameBoard);
            CurrentBoardSetUp(gameBoard);
            CheckIfGameOver(gameBoard,winningChar,*playerChar,*computerChar,gameOver,turns);
            PlayComputerMove(gameBoard,tripletCount,nextSpotRow,nextSpotColumn,gameOver,spotFound,spotTaken,winningChar,*playerChar,playerFirst,turns,*computerChar);
        } else {
            PlayComputerMove(gameBoard,tripletCount,nextSpotRow,nextSpotColumn,gameOver,spotFound,spotTaken,winningChar,*playerChar,playerFirst,turns,*computerChar);
            if(!gameOver) {
                GetPlayerInput(gameBoard);
                CurrentBoardSetUp(gameBoard);
                CheckIfGameOver(gameBoard,winningChar,*playerChar,*computerChar,gameOver,turns);
            }
        }

    } while(!gameOver);
}

//done!