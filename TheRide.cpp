#include <iostream>
#include <string>

using namespace std;

int main() {
    const int TOTAL_RIDES = 22;
    int passengers, cars, transformed;
    string rideName;

    //get info
    cout << "WELCOME TO NOWHEREVILLE PARK" << endl;
    cout << "FOR ENTRY, PLEASE PROVIDE THE FOLLOWING INFO: " << endl;

    cout << "WHAT IS THE CRAZIEST NAME YOU CAN GIVE TO A NONEXISTENT PET (1 WORD ONLY): ";
    cin >> rideName;

    cout << "WHAT'S YOUR FAVORITE NUMBER??? :";
    cin >> passengers;

    cout << "HOW MANY DOLLARS DO YOU HAVE IN YOUR ACCOUNT RIGHT NOW? :";
    cin >> cars;

    transformed = passengers + cars;

    cout << "FANTASTIC! YOU MAY NOW ENTER THE PARK..." << endl;
    cout << "KEEP IN MIND THE NUMBER " << transformed << endl;

    //story time!
    cout << "IN THIS FABLED THEME PARK, THERE ARE MANY ICONIC RIDES -- EXACTLY " << TOTAL_RIDES << " -- BUT NONE AS MUCH SO AS THE GREAT " << rideName << endl;

    cout << "BE WARNED BEFORE ENTERING IT, AS OVER " << transformed << " HAVE ENTERED, BUT ONLY " << cars << " HAVE LEFT ALIVE. THE REST, IT IS SAID, ARE TRAPPED IN THE " << passengers << "TH DIMENSION!" << endl;

    return 0;
}