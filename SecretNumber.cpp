#include <iostream>
#include <string>
#include <time.h>

using namespace std;

int main() {
    //random seed
    srand(time(NULL));

    //random number between 1 and 100
    int randomNumber = rand() % 100 + 1;

    int tries = 0, playerGuess = 0;
    const int MAX_TRIES = 3;
    bool answerObtained = false;

    cout << "I, THE MIGHTY COMPUTER, HAVE SELECTED A RANDOM NUMBER BETWEEN 1 AND 100. YOU HAVE PRECISELY 3 TRIES TO GUESS THE NUMBER. GOOD LUCK....YOU'LL NEED IT!" << endl;

    //get player input and see if it matches
    do {
        cout << "ENTER YOUR GUESS (INTEGER BETWEEN 1 AND 100, INCLUSIVE):  ";
        cin >> playerGuess;

        if(playerGuess == randomNumber) {
            answerObtained = true;
        } else {
            tries++;
            if(playerGuess > randomNumber) {
                cout << "TOO HIGH!" << endl;
            } else {
                cout << "TOO LOW!" << endl;
            }
            cout << "YOU HAVE " << MAX_TRIES - tries << " TRIES LEFT." << endl;
        }

    } while(tries < MAX_TRIES || answerObtained);

    if(answerObtained) {
        cout << "YOU WON...BY LUCK. NEXT TIME, VICTORY SHALL DEFINITELY BE MINE!" << endl;
    } else {
        cout << "OUT OF PITY, I SHALL TELL YOU WHAT THE NUMBER WAS: " << randomNumber << endl;
        cout << "ANYWAY, SEEMS LIKE YOU NEED MORE THAN JUST LUCK. COME BACK IF YOU WANT TO TASTE DEFEAT AGAIN...HAHAHA!" << endl;
    }

    return 0;
}
