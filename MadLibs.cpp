#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

void IntroduceGame();
void GetPlayerInput(string &adverb, string &adjective, string &noun, string &verb);
void ExecuteMadLibs(string &adverb, string &adjective, string &noun, string &verb);

int main() {
    string adverb, adjective, noun, verb;

    IntroduceGame();
    GetPlayerInput(adverb,adjective,noun,verb);
    ExecuteMadLibs(adverb,adjective,noun,verb);

    return 0;
}

void IntroduceGame() {
    cout << "\nWELCOME TO MADLIBS! YOU WILL PROVIDE US WITH WORDS AS INSTRUCTED, AND SEE THE MAGIC THAT YOU CREATE :-)" << endl;
}

void GetPlayerInput(string &adverb, string &adjective, string &noun, string &verb) {
    cout << "\nPLEASE PROVIDE US WITH EACH OF THE FOLLOWING: " << endl;
    cout << "ADVERB: ";
    cin >> adverb;
    cout << "ADJECTIVE: ";
    cin >> adjective;
    cout << "NOUN: ";
    cin >> noun;
    cout << "VERB: ";
    cin >> verb;
}

void ExecuteMadLibs(string &adverb, string &adjective, string &noun, string &verb) {
   cout << "\nTHE " << noun << " WAS QUITE " << adjective << ", COMPLETELY INTENDING TO " << verb << " OUT OF THE WINDOW " << adverb << ".\n" << endl;
}