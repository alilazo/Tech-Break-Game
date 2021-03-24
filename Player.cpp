#include <iostream>

using namespace std;

class Player {
    public:
        string name;
        int man;
        int stam;
        int maxMan;
        int maxStam;
        int health;
        void buildPlayer();
};

void Player::buildPlayer() {
	int choice;
	do {
		cout << "Enter Username For " << name << ": ";
		cin >> name;
		cout << name << ": 3 points in Mana or Stamina?";
		cout << "\n1. Magic \n2. Stamina \n";
		cin >> choice;
		cout << endl;
	} while (choice != 1 && choice != 2);
	if (choice == 1) {
		man = 3;
		maxMan = 3;
	}
	else {
		stam = 3;
		maxStam = 3;
	}
}
