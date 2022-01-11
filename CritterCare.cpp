#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Critter {
    public:
        Critter(int hunger = 0, string name = "Unnamed");
        static int s_TotalCritters;
        static int GetTotal();
        string GetName();
        void CurrentMood();
        void CurrentHungerLevel();
        void Engage(int feed,int play);
    
    private:
        int m_Hunger;
        int m_Mood;
        string m_Mood_S;
        string m_Name;
};

int Critter::s_TotalCritters = 0;

string Critter::GetName() {
    return m_Name;
}

Critter::Critter(int hunger,string name):m_Hunger(hunger),m_Name(name) {
    s_TotalCritters++;
    cout << "HELLO THERE! I AM CRITTER NUMBER " << s_TotalCritters << ". MY NAME IS " << name  << "."<< endl;
}

int Critter::GetTotal() {
    return s_TotalCritters;
}

void Critter::CurrentMood() {
    if(m_Mood < 3) {
        m_Mood_S = "ANGRY";
    } else if(m_Mood < 7) {
        m_Mood_S = "SAD";
    } else {
        m_Mood_S = "HAPPY";
    }
    cout << "CURRENTLY, " << m_Name << " IS " << m_Mood_S << endl;
}

void Critter::CurrentHungerLevel() {
    if(m_Hunger < 3) {
        cout << "CURRENTLY, " << m_Name << " IS EXTREMELY HUNGRY!"  << endl;
    } else if(m_Hunger < 7) {
        cout << "CURRENTLY, " << m_Name << " IS A LITTLE HUNGRY!"  << endl;
    } else {
        cout << "CURRENTLY, " << m_Name << " IS QUITE HAPPY!"  << endl;
    }
}

void Critter::Engage(int feed, int play) {
    if(feed > 0) {
        m_Hunger += feed;
        if(m_Hunger > 10) {
            m_Hunger = 10;
        }
        cout << m_Name << " IS THRILLED TO HAVE SOME FOOD :-)" << endl;
    } else if(feed <= 0) {
        cout << "THAT'S NO FOOD AT ALL!" << endl;
    }

    if(play > 0) {
        m_Mood += round(.5*play);
        if(m_Mood > 10) {
            m_Mood = 10;
        }
        cout << m_Name << " IS SUPER STOKED THAT THEY'LL GET SOME PLAY TIME!" << endl;
    } else if(play <= 0) {
        cout << "THAT'S NO PLAY AT ALL!" << endl;
    }
}

void Introduction();

void CareForCritter(Critter &myCritter, int &play_Hours, int &food_Units);

void FinalResults(vector<Critter> &allCritters, int &play_Hours, int &food_Units);

int main() {
    int play_Hours = 20, food_Units = 40;
    vector<Critter> allCritters;

    Introduction();

    Critter Mike(1,"Mike"), Jim(2,"Jim"), Kale(3,"Kale");
    allCritters.push_back(Mike);
    allCritters.push_back(Jim);
    allCritters.push_back(Kale);

    CareForCritter(allCritters[0],play_Hours,food_Units);

    if(play_Hours < 0 || food_Units < 0) {
        cout << "\nYOU'RE OUT OF RESOURCES! :-( YOU'VE FAILED AT KEEPING ALL THE PETS HAPPY" << endl;
        return 0;
    }

    CareForCritter(allCritters[1],play_Hours,food_Units);

    if(play_Hours < 0 || food_Units < 0) {
        cout << "\nYOU'RE OUT OF RESOURCES! :-( YOU'VE FAILED AT KEEPING ALL THE PETS HAPPY" << endl;
        return 0;
    }

    CareForCritter(allCritters[2],play_Hours,food_Units);
    FinalResults(allCritters,play_Hours,food_Units);

    return 0;
}

void Introduction() {
    cout << "\nTHANKS FOR VOLUNTEERING TO PET SIT THE MAYOR'S PETS. THE THREE PETS NEED TO BE FED AND PLAYED WITH TO OBTAIN THEIR OPTIMAL MOOD (HAPPY). YOU CURRENTLY HAVE 20 UNITS OF FOOD AND 15 HOURS OF PLAY TIME TO DISTRIBUTE EVENLY AND ENSURE ALL CREATURES ARE HAPPY.\n" << endl;
}

void CareForCritter(Critter &myCritter, int &play_Hours, int &food_Units) {
    int playHoursTemp = 0, foodUnitsTemp = 0;
    cout << "\nLETS DEAL WITH " << myCritter.GetName() << endl;
    myCritter.CurrentHungerLevel();
    myCritter.CurrentMood();
    cout << "YOU CURRENTLY HAVE " << play_Hours << " HOURS OF PLAY AND " << food_Units << " UNITS OF FOOD LEFT TO ALLOCATE" << endl;
    cout << "\nHOW MANY HOURS OF PLAY WOULD YOU LIKE TO ALLOCATE TO " << myCritter.GetName() << "?";
    cin >> playHoursTemp;
    while(std::cin.fail()) {
        std::cout << "ERROR: NOT AN INTEGER" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        cout << "\nHOW MANY HOURS OF PLAY WOULD YOU LIKE TO ALLOCATE TO " << myCritter.GetName() << "?";
        cin >> playHoursTemp;
    }
    cout << "\nHOW MAN UNITS OF FOOD WOULD YOU LIKE TO ALLOCATE TO " << myCritter.GetName() << "?";
    cin >> foodUnitsTemp;
    while(std::cin.fail()) {
        std::cout << "ERROR: NOT AN INTEGER" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        cout << "\nHOW MAN UNITS OF FOOD WOULD YOU LIKE TO ALLOCATE TO " << myCritter.GetName() << "?";
        cin >> foodUnitsTemp;
    }
    myCritter.Engage(playHoursTemp,foodUnitsTemp);

    play_Hours -= playHoursTemp;
    food_Units -= foodUnitsTemp;
}

void FinalResults(vector<Critter> &allCritters, int &play_Hours, int &food_Units) {
    if(play_Hours < 0 || food_Units < 0) {
        cout << "\nYOU'RE OUT OF RESOURCES! :-( YOU'VE FAILED AT KEEPING ALL THE PETS HAPPY" << endl;
    }
    else {
        cout << "\nLET'S SEE HOW WELL YOU'VE TAKEN CARE OF THESE PETS:" << endl;
        for(int i = 0; i < allCritters.size(); i++) {
            allCritters[i].CurrentHungerLevel();
            allCritters[i].CurrentMood();
        }
    }
    cout << endl;
}