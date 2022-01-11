#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

class Player {
    friend void GetRole(const Player& aPlayer);
    friend void GetLevel(const Player& aPlayer);
    friend ostream& operator<<(ostream& os, const Player& aPlayer);

    public:
        Player(const string& name = "unnamed", const string& role = "unassigned", const int& level = 1);
        string GetJustName() const;
        string GetName() const;
        string GetRole() const;
        string GetLevel() const;

    private:
        string m_Name;
        string m_Role;
        int m_Level;
};

Player::Player(const string& name, const string& role, const int& level):m_Name(name),m_Role(role),m_Level(level) { }

string Player::GetJustName() const{
    return m_Name;
}

string Player::GetName() const {
    return "Player: " + m_Name;
}

string Player::GetRole() const {
    return "Role: " + m_Role;
}

string Player::GetLevel() const {
    return "Level: " + to_string(m_Level);
}

void GetRole(const Player& aPlayer);
void GetLevel(const Player& aPlayer);
ostream& operator<<(ostream& os, const Player& aPlayer);

class Lobby {
    friend void ModifyPlayersVector(vector<Player>& m_Players);

    public:
        Lobby(int spots = 1);
        void AddToLobby(const Player& aPlayer);
        void RollCall() const;
        int LobbyCount();
        vector<Player>& GetPlayers();

    private:
        vector<Player> m_Players;
};

Lobby::Lobby(int spots) {
    m_Players.reserve(spots);
}

int Lobby::LobbyCount() {
    return m_Players.size();
}

vector<Player>& Lobby::GetPlayers() {
    return m_Players;
}

void Lobby::AddToLobby(const Player& aPlayer) {
    m_Players.push_back(aPlayer);
}

void Lobby::RollCall() const {
    for(vector<Player>::const_iterator iter = m_Players.begin(); iter != m_Players.end(); iter++) {
        cout << iter->GetName() << "; " << iter->GetRole() << "; " << iter->GetLevel() << endl;
    }
}

void ModifyPlayersVector(vector<Player>& m_Players);

void AddNewPlayer(Lobby& gameLobby, string& newName, string& newRole);
void RemovePlayer(Lobby& gameLobby, string& playerToRemove);
void InvestigatePlayer(Lobby& gameLobby,string& playerToInvestigate);
void ClearLobby(Lobby& gameLobby);
void QuitLobby();

bool quitGame = false;
int choice = 0, newLevel = 0;
string newRole, newName, playerToRemove, playerToInvestigate;

int main() {
    Lobby gameLobby(5);
    gameLobby.AddToLobby(Player("Jim","Troll",10));
    gameLobby.AddToLobby(Player("Jake","Dragon",20));
    gameLobby.AddToLobby(Player("Jessy","Guard",30));

    cout << "\nTHERE ARE CURRENTLY THE FOLLOWING PLAYERS IN THE LOBBY:\n";
    gameLobby.RollCall();

    while(!quitGame) {
        cout << "\nWHAT WOULD YOU LIKE TO DO? THERE ARE FIVE OPTIONS:\n";
        cout << "1. ADD NEW PLAYER TO QUEUE\n";
        cout << "2. REMOVE A PLAYER\n";
        cout << "3. INVESTIGATE PLAYER INFO\n";
        cout << "4. CLEAR LOBBY\n";
        cout << "5. QUIT LOBBY\n";

        cout << "\nENTER THE NUMBER ASSOCIATED WITH YOUR CHOICE (EX. 1,2,3,4,5): ";
        cin >> choice;
        while(std::cin.fail() || choice > 5 || choice < 1) {
            std::cout << "ERROR: NOT AN VALID RESPONSE" << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            cout << "ENTER THE NUMBER ASSOCIATED WITH YOUR CHOICE (EX. 1,2,3,4,5): ";
            cin >> choice;
        }  

        switch(choice) {
            newLevel = 0;
            case 1:
                AddNewPlayer(gameLobby,newName,newRole);
                break;
            case 2:
                RemovePlayer(gameLobby,playerToRemove);
                break;
            case 3:
                InvestigatePlayer(gameLobby,playerToInvestigate);
                break;
            case 4:
                ClearLobby(gameLobby);
                break;
            case 5:
                QuitLobby();
                break;
            default:
                cout << "HELLO THERE! WHAT DID YOU DO???" << endl;
                break;
        }
    }

    return 0;
}

void QuitLobby() {
    cout << "\nSEE YOU AGAIN SOON!\n\n";
    quitGame = true;
    exit(0);
}

void ClearLobby(Lobby& gameLobby) {
    //erase all elements in vector
    vector<Player>& playerList = gameLobby.GetPlayers();
    ModifyPlayersVector(playerList);
    cout << "\nCLEARED! AS YOU CAN SEE, THERE ARE NO PLAYERS IN THE LOBBY: \n";
    gameLobby.RollCall();
}

void RemovePlayer(Lobby& gameLobby, string& playerToRemove) {
    playerToRemove.clear();
    cout << "\nFROM PLEASE ENTER THE NAME OF THE PLAYER YOU WOULD LIKE TO REMOVE: ";
    std::cin >> std::ws;   // <--- drop whitespaces
    getline(cin,playerToRemove);

    int lobbyCount = gameLobby.LobbyCount();
    int playerToRemovePosition = lobbyCount;
    vector<Player>& playerList = gameLobby.GetPlayers();

    //see if player is in our lobby
    for(int i = 0; i < lobbyCount; i++) {
        if(playerList[i].GetJustName() == playerToRemove) {
            playerToRemovePosition = i;
        }
    }

    if(playerToRemovePosition != lobbyCount) {
        playerList.erase(playerList.begin() + playerToRemovePosition);
        cout << "\nPLAYER REMOVED! HERE ARE THE PLAYERS CURRENTLY IN THE LOBBY:\n";
        gameLobby.RollCall();
    } else {
        cout << "PLAYER NOT FOUND IN LOBBY!" << endl;
    }
}

void ModifyPlayersVector(vector<Player>& playerList) {
    playerList.erase(playerList.begin(),playerList.begin() + playerList.size());
}

void AddNewPlayer(Lobby& gameLobby, string& newName, string& newRole) {
    newName.clear();
    newRole.clear();
    while(newName.empty()) {
        cout << "\nYOU HAVE DECIDED TO ADD A NEW PLAYER TO THE QUEUE! PLEASE ENTER A NAME FOR THE PLAYER: ";
        std::cin >> std::ws;   // <--- drop whitespaces
        getline(cin,newName); 
    }

    while(newRole.empty()) {
        cout << "\nPLEASE ENTER A ROLE FOR THE PLAYER (EX. TROLL, DRAGON, HERO): ";
        std::cin >> std::ws;   // <--- drop whitespaces
        getline(cin,newRole); 
    }
    
    cout << "\nPLEASE ENTER THE PLAYER'S LEVEL: ";
    cin >> newLevel;
    while(std::cin.fail() || newLevel == 0) {
        std::cout << "ERROR: NOT AN VALID RESPONSE" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        cout << "\nPLEASE ENTER THE PLAYER'S LEVEL: ";
        cin >> newLevel;
    }
    gameLobby.AddToLobby(Player(newName,newRole,newLevel));
    cout << "\nNEW PLAYER HAS BEEN ADDED! HERE ARE THE CURRENT PLAYERS IN THE LOBBY:\n";
    gameLobby.RollCall();
}

void InvestigatePlayer(Lobby& gameLobby,string& playerToInvestigate) {
    playerToInvestigate.clear();
    cout << "\nFROM PLEASE ENTER THE NAME OF THE PLAYER YOU WOULD LIKE TO INVESTIGATE: ";
    std::cin >> std::ws;   // <--- drop whitespaces
    getline(cin,playerToInvestigate);

    int lobbyCount = gameLobby.LobbyCount();
    int playerToInvestigatePosition = lobbyCount;
    vector<Player>& playerList = gameLobby.GetPlayers();

    //see if player is in our lobby
    for(int i = 0; i < lobbyCount; i++) {
        if(playerList[i].GetJustName() == playerToInvestigate) {
            playerToInvestigatePosition = i;
        }
    }

    if(playerToInvestigatePosition != lobbyCount) {
        cout << "HERE IS SOME INFO ON THAT PLAYER: \n";
        GetRole(playerList[playerToInvestigatePosition]);
        GetLevel(playerList[playerToInvestigatePosition]);
    } else {
        cout << "PLAYER NOT FOUND IN LOBBY!" << endl;
    }
}

void GetRole(const Player& aPlayer) {
    cout << "THEIR ROLE IS: " << aPlayer.m_Role << endl;
}

void GetLevel(const Player& aPlayer) {
    cout << "THEIR LEVEL IS: " << aPlayer.m_Level << endl;
}

ostream& operator<<(ostream& os, const Player& aPlayer) {
    os << "Player Object - ";
    os << "m_Name: " << aPlayer.m_Name;
    os << "m_Role: " << aPlayer.m_Role;
    os << "m_Level: " << aPlayer.m_Level; 
    return os;
}
