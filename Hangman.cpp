#include <iostream>
#include <string>
#include <time.h>

using namespace std;

int main() {
    //seed random number generator
    srand(time(NULL));

    string secretWords[5] = {"catatonic", "bazinga", "type", "dramatic", "touchdown"};

    string usedWords[5] = {"unused"};

    char playerGuessChar[10] = {0};

    char usedLetters[26] = {0};

    char charLetter;

    string secretWord, playerGuess, word;

    const int ARRAY_LENGTH = sizeof(secretWords) / sizeof(secretWords[0]);

    const int TOTAL_TRIES = 5, TOTAL_QUESTIONS = 3, POINTS_PER_QUESTION = 50;

    int numberCorrect = 0, totalQuestionsCompleted = 0, swapIndex = 0, tempMinIndex = 0, attempts = 0, totalPoints = 0, randomNumber = 0, lengthOfSecretWord = 0, arrayIndex = 0, nextIndex = 100, pointsGained = 0;

    bool foundValidWord = false, foundAMatch = false, inUsedLetters = false, lettersUsed = false;

    cout << "\nWELCOME TO HANGMAN! IN THIS REMAKE OF AN AGE-OLD CLASSIC, YOU WILL HAVE TO GUESS THE WORD LETTER BY LETTER. YOU CAN MAKE UP TO 5 MISTAKES BEFORE MISSING THE QUESTION; FOR EACH MISTAKE, YOU WILL EARN 10 POINTS LESS THAN THE MAX (50). ";

    //core game loop
    do {
        pointsGained = 0;

        if(totalQuestionsCompleted == 0) {
            cout << "TIME FOR YOUR FIRST UNKNOWN WORD! \n";
        } else {
            cout << "TIME FOR YOUR NEXT UNKNOWN WORD! \n";
        }

        //find a (new) random word
        do {
            foundValidWord = false;
            randomNumber = rand() % ARRAY_LENGTH;
            word = secretWords[randomNumber];
            
            for(int i = 0; i < ARRAY_LENGTH; i++) {
                if(usedWords[i] == word) {
                    break;
                } else if(usedWords[i] != word && i == ARRAY_LENGTH - 1) {
                    foundValidWord = true;
                    usedWords[arrayIndex] = word;
                    arrayIndex++;
                }
            }
        } while(!foundValidWord);

        //play hangman with that word
        do {
            playerGuess = "";
            inUsedLetters = false;
            nextIndex = 100;
            cout << "\nHERE IS THE UNKNOWN WORD THUS FAR: ";
            for(int i = 0; i < word.length(); i++) {
                if(playerGuessChar[i] == 0) {
                    cout << " _ ";
                } else {
                    cout << playerGuessChar[i];
                }
            }

            if(lettersUsed) {
                cout << "\nLETTERS USED THUS FAR ARE THE FOLLOWING: ";
                for(int i = 0; i < 26; i++) {
                    if(usedLetters[i] != 0) {
                        cout << usedLetters[i];
                    }
                }
            } else {
                cout << "\nNO LETTERS USED THUS FAR!";
            }

            cout << "\nENTER A LETTER: ";
            cin >> charLetter;

            //update letters used array based on what player provided
            for(int i = 0; i < 26; i++) {
                if(usedLetters[i] == 0 && i < nextIndex) {
                    nextIndex = i;
                }
                if(usedLetters[i] == charLetter) {
                    inUsedLetters = true;
                }
                if(usedLetters[i] != charLetter && !inUsedLetters && i == 25) {
                    //add letter to next available spot
                    usedLetters[nextIndex] = charLetter;
                    lettersUsed = true;
                }
            }

            //check if letter is in the word
            for(int i = 0; i < word.length(); i++) {
                if(word[i] == charLetter) {
                    foundAMatch = true;
                    playerGuessChar[i] = charLetter;
                    for(int j = 0; j < word.length(); j++) {
                        playerGuess += playerGuessChar[j];
                    }
                }
                else if(i == word.length() - 1 && !foundAMatch) {
                    attempts++;
                    if(attempts < TOTAL_TRIES) {
                        cout << "POOR CHOICE! YOU HAVE " << TOTAL_TRIES - attempts << " LEFT TO GUESS THE WORDS CORRECTLY" << endl;
                    }
                    else {
                        cout << "YOU HAVE USED ALL YOUR ATTEMPTS, ALBEIT UNSUCCESSFULLY :-( . THE WORD IS INDEED: " << word << endl;
                    }
                }
            }

            if(foundAMatch) {
                foundAMatch = false;
                if(inUsedLetters) {
                    cout << "YOU'VE ALREADY TRIED THAT LETTER!" << endl;
                } else {
                    cout << "GREAT GUESS!" << endl;
                }
            }

            if(playerGuess == word) {
                numberCorrect++;
                pointsGained = POINTS_PER_QUESTION - attempts * 10;
                totalPoints += pointsGained;
                cout << "\nAWESOME JOB! YOU'VE GOT IT :-) . THE WORD IS INDEED: " << playerGuess << endl;
            }

        } while(attempts < TOTAL_TRIES && playerGuess != word);

        //reset for next loop
        totalQuestionsCompleted++;
        attempts = 0;
        memset(&playerGuessChar[0], 0, sizeof(playerGuessChar));
        memset(&usedLetters[0], 0, sizeof(usedLetters));
        lettersUsed = false;

        if(totalQuestionsCompleted == TOTAL_QUESTIONS) {
            cout << "\nCONGRATS ON FINISHING THE GAME! YOU HAVE CORRECTLY GUESSED " << numberCorrect << " OUT OF " << TOTAL_QUESTIONS << " WORDS. THIS YIELDS A TOTAL OF " << totalPoints << " POINTS. NOW GO BE HAPPY :-D " << endl;

        } else {
            cout << "\nYOU HAVE GAINED " << pointsGained << " POINTS FOR A GRAND TOTAL OF " << totalPoints << " POINTS. KEEP UP THE GOOD WORK!\n" << endl;
        }

    } while(totalQuestionsCompleted < TOTAL_QUESTIONS);

    return 0;
}