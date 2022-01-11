#include <iostream>
#include <string>
#include <time.h>

using namespace std;

int main() {
    //random seed
    srand(time(NULL));

    //get secret word and scramble it up
    string secretWords[5] = {"catatonic", "bazinga", "type", "dramatic", "touchdown"};
    string hints[5] = {"relating to or characterized by catatonia", "Sheldon Cooper...'nuff said", "we can classify objects by their...", "the type of entrance each team makes in the superbowl", "7 points in a game of football!"};

    const int maxLength = 10;

    const int MAX_POINTS = 30;

    string usedWords[5] = {"unused"};

    //create an array of int of length of the secret word, then another one to arrange those numbers from least to greatest
    int orderingNumbers[maxLength] = {0};
    int orderingNumbersOrdered[maxLength] = {0};

    //create array of characters to store the scrambled letters (which, when concatenated, give the scrambled form of the word)
    char scrambledLetters[maxLength] = {0};

    const int ARRAY_LENGTH = sizeof(secretWords) / sizeof(secretWords[0]);

    string guess, scrambledWord, word, response;

    const int TOTAL_TRIES = 3, TOTAL_QUESTIONS = 3;
    int numberCorrect = 0, totalQuestionsCompleted = 0, randomNumber = 0, randomNumber2 = 0, arrayIndex = 0, swapIndex = 0, tempMinIndex = 0, attempts = 0, tempMin = 100, resetIndex = 100, totalPoints = 0;

    bool foundValidWord = false;

    cout << "\nWELCOME TO WORD JUMBLE!\n" << endl;

    cout << "YOU WILL HAVE THREE WORDS PRESENTED TO YOU IN A JUMBLED FORMAT, AND YOU WILL HAVE 3 TRIES TO GUESS THE CORRECT SPELLING FOR EACH WORD. YOU GET 0 POINTS FOR A GIVEN SCRAMBLED WORD FOR GUESSING INCORRECTLY ON ALL 3 ATTEMPTS. KEEP IN MIND THAT GUESSING CORRECTLY ON THE FIRST TRY NETS THE MOST POINTS; LATER TRIES NET LESS WITH GUESSING CORRECTLY ON THE FINAL TRY NETS THE LEAST. PRESS 'H' ANYTIME YOU NEED A HINT. GOOD LUCK! \n\n";

    do {
        if(totalQuestionsCompleted > 0) {
            cout << "TIME FOR YOUR NEXT SCRAMBLED WORD!" << endl;
        }
        
        //pick random word that is new
        do {
            foundValidWord = false;
            //random number between 0 and secretWords.Length
            randomNumber = rand() % ARRAY_LENGTH;
            word = secretWords[randomNumber];
            
            for(int i = 0; i < ARRAY_LENGTH; i++) {
                if(usedWords[i] == word) {
                    break;
                } else if(usedWords[i] != word && i == ARRAY_LENGTH - 1) {
                    //cout << word << endl;
                    foundValidWord = true;
                    usedWords[arrayIndex] = word;
                    arrayIndex++;
                }
            }
        } while(!foundValidWord);

        //cout << "FOUND VALID WORD!" << endl;

        //scramble the word

        //cout << "ARRAYS ARE ALL SET UP!" << endl;

        //get n random numbers, where n is the length of the secret word
        for(int i = 0; i < word.length(); i++) {
            randomNumber2 = rand() % 100 + 1;
            orderingNumbers[i] = randomNumber2;
            orderingNumbersOrdered[i] = randomNumber2;
        }

        //cout << "ARRAYS ARE ALL SET UP 1!" << endl;
        //order from least to greatest using selection sort
        for(int i = 0; i < word.length(); i++) {
            tempMinIndex = word.length();
            for(int j = i; j < word.length(); j++) {
                if(orderingNumbersOrdered[j] < orderingNumbersOrdered[i]) {
                    tempMinIndex = j;
                }
                if(j == word.length() - 1 && tempMinIndex != word.length()) { //if done combing through array and there is a viable swap, then swap
                    swap(orderingNumbersOrdered[i],orderingNumbersOrdered[tempMinIndex]);
                }
            }
        }

        //cout << "SORT SELECTION IS COMPLETE!" << endl;

        //for each element in the word, add to scrambled array at the position of nth min element. ex: 1st char goes in spot of min, ... , final char goes in spot of max
        for(int i = 0; i < word.length(); i++) {
            //find tempMin and index
            tempMin = orderingNumbersOrdered[i];
            resetIndex = 100;
            for(int j = 0; j < word.length(); j++) {
                //cout << "SCRAMBLEDLETTERS[" << j << "] IS " << scrambledLetters[j] << endl;
                if(orderingNumbers[j] == tempMin && scrambledLetters[j] == 0 && resetIndex == 100) {
                    resetIndex = j;
                    scrambledLetters[resetIndex] = word[i];
                }
            }
        }

        //cout << "\nSCRAMBLING IS COMPLETE!" << endl;

        for(int i = 0; i < word.length(); i++) {
            scrambledWord = scrambledWord + scrambledLetters[i];
        }

        //see if player guesses
        do {
            cout << "HERE IS THE JUMBLED WORD: " + scrambledWord << endl;
            cout << "WHAT WORD DO YOU THINK IT IS? (ENTER 'H' or 'h' IF YOU NEED A HINT): ";
            cin >> response;
            if(response != "H" && response != "h") {
                guess = response;
                attempts++;
                if(guess != word && attempts < TOTAL_TRIES) {
                    cout << "INCORRECT. TRY AGAIN!\n" << endl;
                }
            } 
            else {
                cout << "HINT: " << hints[randomNumber] << endl << endl;
                do {
                    cout << "HERE IS THE JUMBLED WORD: " + scrambledWord << endl;
                    cout << "WHAT WORD DO YOU THINK IT IS? (ENTER 'H' or 'h' IF YOU NEED A HINT): ";
                    cin >> response;
                    if(response != "H" && response != "h") {
                        guess = response;
                        attempts++;
                        if(guess != word && attempts < TOTAL_TRIES) {
                            cout << "INCORRECT. TRY AGAIN!\n" << endl;
                        }
                    }
                    else {
                        cout << "HINT: " << hints[randomNumber] << endl << endl;
                    } 
                } while(guess == "");
            }
        } while(attempts < TOTAL_TRIES && guess != word);

        //reset
        memset(&scrambledLetters[0], 0, sizeof(scrambledLetters));
        memset(&orderingNumbers[0], 0, sizeof(orderingNumbers));
        memset(&orderingNumbersOrdered[0], 0, sizeof(orderingNumbersOrdered));

        if(attempts == 3 && guess != word) {
            //missed the word
            cout << "INCORRECT AGAIN! THE SECRET WORD IS IS INDEED: " << word << endl << endl;
        }
        if(guess == word) {
            //got it right
            cout << "SPLENDID! YOU GOT IT!" << endl;

            int pointsGained = MAX_POINTS - (attempts - 1) * 10;
            totalPoints += pointsGained;
            numberCorrect++;

            cout << "YOU'VE GAINED " << pointsGained << " POINTS, AND CURRENTLY POSSESS A GRAND TOTAL OF " << totalPoints << " POINTS\n" << endl;
        }

        totalQuestionsCompleted++;
        attempts = 0;
        scrambledWord = "";
        guess = "";
        
    } while(totalQuestionsCompleted < TOTAL_QUESTIONS);

    cout << "CONGRATULATIONS ON COMPLETING THE GAME! YOU HAVE CORRECTLY ANSWERED " << numberCorrect << " OUT OF " << TOTAL_QUESTIONS << " FOR A GRAND TOTAL OF " << totalPoints << " POINTS\n";

    return 0;
}