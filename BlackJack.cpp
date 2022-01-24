#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

//abstract base class
class BaseCardType { 
    public:
        BaseCardType(int label = 13, char type = 'k');
        virtual ~BaseCardType();
        virtual int GetCardLabel() const = 0;
        virtual char GetCardType() const = 0; 

    protected:
        char m_Label;
        char m_Type;

};

BaseCardType::BaseCardType(int label, char type):m_Label(label), m_Type(type) { }

BaseCardType::~BaseCardType() { }

//different card types
class Spades:public BaseCardType {
    public:
        Spades(int label = 13, char type = 's');
        ~Spades();
        int GetCardLabel() const;
        char GetCardType() const;

    protected:
        char m_Label;
        char m_Type;
};

Spades::Spades(int label, char type):m_Label(label), m_Type(type) {
    //cout << "This is card " << to_string(m_Label) << m_Type << endl;
}

Spades::~Spades() { }

int Spades::GetCardLabel() const {
    return m_Label;
}

char Spades::GetCardType() const {
    return m_Type;
}

class Clubs:public BaseCardType {
    public:
        Clubs(int label = 13, char type = 'c');
        ~Clubs();
        int GetCardLabel() const;
        char GetCardType() const;

    private:
        char m_Label;
        char m_Type;
};

Clubs::Clubs(int label, char type):m_Label(label), m_Type(type) {
    //cout << "This is card " << to_string(m_Label) << m_Type << endl;
}

Clubs::~Clubs() {}

int Clubs::GetCardLabel() const {
    return m_Label;
}

char Clubs::GetCardType() const {
    return m_Type;
}

class Hearts:public BaseCardType {
    public:
        Hearts(int label = 13, char type = 'h');
        ~Hearts();
        int GetCardLabel() const;
        char GetCardType() const;

    private:
        char m_Label;
        char m_Type;
};

Hearts::Hearts(int label, char type):m_Label(label), m_Type(type) {
    //cout << "This is card " << to_string(m_Label) << m_Type << endl;
}

Hearts::~Hearts() { }

int Hearts::GetCardLabel() const {
    return m_Label;
}

char Hearts::GetCardType() const {
    return m_Type;
}

class Diamonds:public BaseCardType {
    public:
        Diamonds(int label = 13, char type = 'd');
        ~Diamonds();
        int GetCardLabel() const;
        char GetCardType() const;

    private:
        char m_Label;
        char m_Type;
};

Diamonds::Diamonds(int label, char type):m_Label(label), m_Type(type) {
    //cout << "This is card " << to_string(m_Label) << m_Type << endl;
}

Diamonds::~Diamonds() { }

int Diamonds::GetCardLabel() const {
    return m_Label;
}

char Diamonds::GetCardType() const {
    return m_Type;
}

//player
class Player {
    public:
        Player(string name , BaseCardType* startingCard1, BaseCardType* startingCard2, int startingPoints);
        Player();
        ~Player();
        int GetPlayerTotal();
        string GetPlayerName();
        void DisplayHand();
        void AddToHand(BaseCardType* card);

    private:
        BaseCardType *m_PlayerHand[52];
        string m_Name;
        int m_CardCount;
        int m_TotalPoints;

};

Player::Player() { }

Player::Player(string name, BaseCardType* startingCard1, BaseCardType* startingCard2, int startingPoints):m_Name(name), m_TotalPoints(startingPoints) {
    //add 2 random cards to player's hands.
    cout << name << "'s HAND IS:";
    m_PlayerHand[0] = startingCard1;
    m_TotalPoints += startingCard1->GetCardLabel();
    m_PlayerHand[1] = startingCard2;
    m_TotalPoints += startingCard2->GetCardLabel();
    m_CardCount = 2;
    for(int i = 0; i < 2; i++) {
        cout << " " << m_PlayerHand[i]->GetCardLabel() << m_PlayerHand[i]->GetCardType();
    }
    cout << " <" << m_TotalPoints << "> " << endl;
}

Player::~Player() { }

string Player::GetPlayerName() {
    return m_Name;
}

void Player::DisplayHand() {
    cout << "\n" << m_Name << "'s HAND IS:";
    for(int i = 0; i < m_CardCount; i++) {
        cout << " " << m_PlayerHand[i]->GetCardLabel() << m_PlayerHand[i]->GetCardType();
    }
    cout << " <" << m_TotalPoints << "> ";
}

void Player::AddToHand(BaseCardType* card) {
    m_PlayerHand[m_CardCount] = card;
    m_TotalPoints += card->GetCardLabel();
    m_CardCount++;
}

int Player::GetPlayerTotal() {
    return m_TotalPoints;
}

class House:public Player {
    public:
        House(BaseCardType* startingCard1, BaseCardType* startingCard2);
        ~House();
        int GetHouseTotal();
        void DisplayHand();
        void AddToHand(BaseCardType* card);

    private:
        BaseCardType *m_HouseHand[52];
        int m_CardCount;
        int m_TotalPoints;
};

House::House(BaseCardType* startingCard1, BaseCardType* startingCard2) {
    cout << "HOUSE's HAND IS:";
    m_HouseHand[0] = startingCard1;
    m_TotalPoints += startingCard1->GetCardLabel();
    m_HouseHand[1] = startingCard2;
    m_TotalPoints += startingCard2->GetCardLabel();
    m_CardCount = 2;
    for(int i = 0; i < 2; i++) {
        if(i != 1) {
            cout << " " << m_HouseHand[i]->GetCardLabel() << m_HouseHand[i]->GetCardType();
        }
        else {
            cout << " XX\n\n";
        }
    }
}

House::~House() { }

int House::GetHouseTotal() {
    return m_TotalPoints;
}

void House::DisplayHand() {
    cout << "\nHOUSE's HAND IS:";
    for(int i = 0; i < m_CardCount; i++) {
        cout << " " << m_HouseHand[i]->GetCardLabel() << m_HouseHand[i]->GetCardType();
    }
    cout << " <" << m_TotalPoints << "> " << endl;
}

void House::AddToHand(BaseCardType* card) {
    m_HouseHand[m_CardCount] = card;
    m_TotalPoints += card->GetCardLabel();
    m_CardCount++;
}

int main() {
    cout << "\nTODAY WE WILL PLAY A WATERED DOWN VERSION OF BLACKJACK. THE CARDS RANGE FROM VALUES OF 0 - 12 FOR EACH SUITE (NO ACES, JACKS, QUEENS, AND KINGS)." << endl;

    const int TOTAL_DECK_SIZE = 52;
    int random1 = 0, random2 = 0, swapCounter = 0, position = 0, totalPlayers = 0;
    string playerName;

    //random seed
    srand(time(NULL));

    //create deck of cards
    vector<BaseCardType*> deck;

    for(int i = 0; i < 13; i++) {
        BaseCardType* spade = new Spades(i);
        deck.push_back(spade);
    }

    for(int i = 0; i < 13; i++) {
        BaseCardType* heart = new Hearts(i);
        deck.push_back(heart);
    }

    for(int i = 0; i < 13; i++) {
        BaseCardType* club = new Clubs(i);
        deck.push_back(club);
    }

    for(int i = 0; i < 13; i++) {
        BaseCardType* diamond = new Diamonds(i);
        deck.push_back(diamond);
    }

    vector<BaseCardType*>::const_iterator iter = deck.begin();

    //get players
    cout << "\nHOW MANY PLAYERS (1-7): ";
    cin >> totalPlayers;
    vector<Player> players;
    players.reserve(totalPlayers);

    for(int i = 0; i < totalPlayers; i++) {
        cout << "\nENTER PLAYER NAME: ";
        cin >> playerName;

        //assign random cards to each player to start off
        random1 = rand() % (deck.size() - swapCounter);
        swapCounter++;

        random2 = rand() % (deck.size() - swapCounter);

        while(random1 == random2) {
            random2 = rand() % (deck.size() - swapCounter);
        }
        swapCounter++;

        cout << endl;

        players.push_back(Player(playerName,deck[TOTAL_DECK_SIZE - random1],deck[TOTAL_DECK_SIZE - random2],0));

        swap(deck[position],deck[TOTAL_DECK_SIZE - random1]);
        position++;
        swap(deck[position],deck[TOTAL_DECK_SIZE - random2]);
        position++;

        if(players[i].GetPlayerTotal() == 21) {
            cout << "\n" << players[i].GetPlayerName() << " WINS!" << endl;
        } else if(players[i].GetPlayerTotal() > 21) {
            cout << "\n" << players[i].GetPlayerName() << " HAS LOST!" << endl;
        }

        cout << endl;
    }

    cout << endl;

    //allocate cards to house
    random1 = rand() % (deck.size() - swapCounter);
    swapCounter++;

    random2 = rand() % (deck.size() - swapCounter);

    while(random1 == random2) {
        random2 = rand() % (deck.size() - swapCounter);
    }
    swapCounter++;

    House House(deck[TOTAL_DECK_SIZE - random1],deck[TOTAL_DECK_SIZE - random2]);

    swap(deck[position],deck[TOTAL_DECK_SIZE - random1]);
    position++;
    swap(deck[position],deck[TOTAL_DECK_SIZE - random2]);
    position++;

    char playerInput;

    //go player by player and officially run game
    for(int i = 0; i < totalPlayers; i++) {
        if(players[i].GetPlayerTotal() < 21) {
            cout << "\n\nWOULD " << players[i].GetPlayerName() << " LIKE A HIT? ";
            cin >> playerInput;

            if(playerInput == 'n') {
                cout << "\nALRIGHTY THEN!" << endl;
            }

            while(playerInput == 'y' && players[i].GetPlayerTotal() < 21) {
                //draw random card
                random1 = rand() % (deck.size() - swapCounter);
                swapCounter++;

                //add card to player's hand
                players[i].AddToHand(deck[TOTAL_DECK_SIZE - random1]);

                //display hand + total
                players[i].DisplayHand();

                if(players[i].GetPlayerTotal() == 21) {
                    cout << "\n\n" << players[i].GetPlayerName() << " WINS!" << endl;
                } else if(players[i].GetPlayerTotal() > 21) {
                    cout << "\n\n" << players[i].GetPlayerName() << " HAS LOST!" << endl;
                } else {
                    cout << "\n\nWOULD " << players[i].GetPlayerName() << " LIKE A HIT? ";
                    cin >> playerInput;
                    
                    if(playerInput == 'n') {
                        cout << "\nALRIGHTY THEN!" << endl;
                    }
                }
            }
        }
        cout << endl;
    }
    
    //house
    if(House.GetHouseTotal() < 16) {
        if(House.GetHouseTotal() == 21) {
            cout << "\nHOUSE WINS!" << endl;
        } else {
            while(House.GetHouseTotal() < 16) {
                //draw random card
                random1 = rand() % (deck.size() - swapCounter);
                swapCounter++;

                //add card to house's hand
                House.AddToHand(deck[TOTAL_DECK_SIZE - random1]);

                //display hand + total
                House.DisplayHand();

                if(House.GetHouseTotal() == 21) {
                    cout << "\nHOUSE WINS!" << endl;
                } else if(House.GetHouseTotal() > 21) {
                    cout << "\nHOUSE HAS LOST!" << endl;
                }
            }
        }
    }
    
    cout << "\nAND NOW FOR THE FINAL RESULTS" << endl;

    //determine final results
    if(House.GetHouseTotal() > 21) {
        for(int i = 0; i < totalPlayers; i++) {
            if(players[i].GetPlayerTotal() < 21) {
                cout << "\n" << players[i].GetPlayerName() << " IS A WINNER!" << endl;
            }
        }
    } else if(House.GetHouseTotal() < 21) {
        for(int i = 0; i < totalPlayers; i++) {
            if(players[i].GetPlayerTotal() > House.GetHouseTotal() && players[i].GetPlayerTotal() <= 21) {
                cout << "\n" << players[i].GetPlayerName() << " IS A WINNER!" << endl;
            }
            if(players[i].GetPlayerTotal() == House.GetHouseTotal()) {
                cout << "\n" << players[i].GetPlayerName() << " IS TIED!" << endl;
            }
        }
    } else if(House.GetHouseTotal() == 21) {
        for(int i = 0; i < totalPlayers; i++) {
            if(players[i].GetPlayerTotal() == House.GetHouseTotal()) {
                cout << "\n" << players[i].GetPlayerName() << " IS TIED!" << endl;
            }
        }
    }

    cout << "\nTHAT'S ALL FOLKS!" << endl;
    //de-allocate memory and clear deck
    for(vector<BaseCardType*>::const_iterator iter = deck.begin(); iter != deck.end(); iter++) {
        delete *iter;
    }
    deck.clear();

    cout << endl << endl;

    return 0;
}