#include <iostream>
#include <string>
#include <unistd.h>
#include "Player.h"

using namespace std;


Player::Player(string givenName) {
	name = givenName;
	man = 0;
	stam = 0;
	maxMan = 0;
	maxStam = 0;
	health = 100;
}

string Player::getName() {
	return name;
}
int Player::getMan() {
	return man;
}
int Player::getStam() {
	return stam;
}
int Player::getHealth() {
	return health;
}


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

//Lets player put more points into Mana or Stamina
void Player::levelUp() {
	int choice;
	if (maxMan >= 10 && maxStam >= 10) {
		cout << "You can't level up any more" << endl;
	}
	else if (maxMan >= 10 && maxStam < 10) {
		cout << "You can only level up your Stamina" << endl;
		maxStam++;
	}
	else if (maxStam >= 10 && maxMan < 10) {
		cout << "You can only level up your Mana" << endl;
		maxMan++;
	}
	else {
		cout << "Would you like to level up 1:Mana or 2:Stamina: ";
		cin >> choice;
		while (choice != 1 && choice != 2) {
			cout << "Invalid Try Again: ";
			cin >> choice;
		}
		if (choice == 1) {
			maxMan++;
		}
		else {
			maxStam++;
		}
	}
}

void Player::displayHurt(Player pf, Player pd){

	// Fighting Player Display
	cout << "\033[1m\033[32m" << pf.name << "\033[0m" << endl
		<< "Mana Points: " << pf.man << "/" << pf.maxMan << endl
		<< "Stamina Points: " << pf.stam << "/" << pf.maxStam << endl
		<< "Health: " << pf.health << "/" << 100;
	cout << "|";
	//Displays Health bar
	for (int i = 0; i < 10; i++) {
		if (i < pf.health / 10) {
			cout << (char)219u; //full bar
		}
		else if (i < (pf.health / 10) + 1 && pf.health % 10 > 0) {
			if (pf.health % 10 >= 7) {
				cout << (char)178u; //highly dotted
			}
			else if (pf.health % 10 >= 4) {
				cout << (char)177u; //medium dotted
			}
			else {
				cout << (char)176u; //low dotted
			}
		}
		else {
			cout << " ";
		}

	}
	cout << "|" << endl;

	cout << "---------------------------------------------------" << endl;

	//Defending PLayer Display
	cout << "\t\t\t" << "\033[35m" << pd.name << "\033[0m" << endl
		<< "\t\t\tMana Points: " << pd.man << "/" << pd.maxMan << endl
		<< "\t\t\tStamina Points: " << pd.stam << "/" << pd.maxStam << endl
		<< "\t\t\tHealth: " << pd.health << "/" << 100;

        cout << "|\033[31m";

	//Displays Health bar
	for (int i = 0; i < 10; i++) {
		if (i < pd.health / 10) {
			cout << (char)219u;
		}
		else if (i < (pd.health / 10) + 1 && pd.health % 10 > 0) {
			if (pd.health % 10 >= 7) {
				cout << (char)178u;
			}
			else if (pd.health >= 4) {
				cout << (char)177u;
			}
			else {
				cout << (char)176u;
			}
		}
		else {
			cout << " ";
		}

	}
        cout << "\033[0m|" << endl << endl;
}

// Everything Under Displays Info For Players on screen
void Player::displayPVP(Player pf, Player pd) {
    pf.hurt = false;
	// Fighting Player Display
	cout << "\033[1m\033[32m" << pf.name << "\033[0m" << endl
		<< "Mana Points: " << pf.man << "/" << pf.maxMan << endl
		<< "Stamina Points: " << pf.stam << "/" << pf.maxStam << endl
		<< "Health: " << pf.health << "/" << 100;
	cout << "|";
	//Displays Health bar
	for (int i = 0; i < 10; i++) {
		if (i < pf.health / 10) {
			cout << (char)219u; //full bar
		}
		else if (i < (pf.health / 10) + 1 && pf.health % 10 > 0) {
			if (pf.health % 10 >= 7) {
				cout << (char)178u; //highly dotted
			}
			else if (pf.health % 10 >= 4) {
				cout << (char)177u; //medium dotted
			}
			else {
				cout << (char)176u; //low dotted
			}
		}
		else {
			cout << " ";
		}

	}
	cout << "|" << endl;

	cout << "---------------------------------------------------" << endl;

	//Defending PLayer Display
	cout << "\t\t\t" << "\033[35m" << pd.name << "\033[0m" << endl
		<< "\t\t\tMana Points: " << pd.man << "/" << pd.maxMan << endl
		<< "\t\t\tStamina Points: " << pd.stam << "/" << pd.maxStam << endl
		<< "\t\t\tHealth: " << pd.health << "/" << 100;

        cout << "|";

	//Displays Health bar
	for (int i = 0; i < 10; i++) {
		if (i < pd.health / 10) {
			cout << (char)219u;
		}
		else if (i < (pd.health / 10) + 1 && pd.health % 10 > 0) {
			if (pd.health % 10 >= 7) {
				cout << (char)178u;
			}
			else if (pd.health >= 4) {
				cout << (char)177u;
			}
			else {
				cout << (char)176u;
			}
		}
		else {
			cout << " ";
		}

	}
        cout << "|" << endl << endl;
}

void Player::reset() {
	stam = maxStam;
	man = maxMan;
}

void Player::playerCalcA(int aMan, int aStam, int aHealth) {
	man -= aMan;
	stam -= aStam;
	health -= aHealth;
	toLow();
}

void Player::playerCalcD(int dMan, int dStam, int dHealth) {
	man -= dMan;
	stam -= dStam;
	health -= dHealth;
	toLow();
}

void Player::toLow() {
	if (health > 100) {
		health = 100;
	}

	if (man < 0) {
		man = 0;
	}

	if (stam < 0) {
		stam = 0;
	}
}

//calculates where the game will take points from for the player
bool Player::calcCost(int cost) {
	int spend = cost;
	if (man + stam >= cost) {
		if (man > stam) {
			if (man >= cost) {
				man -= spend;
			}
			else {
				spend -= man;
				man = 0;
				stam -= spend;
			}
		}
		else {
			if (stam >= cost) {
				stam -= spend;
			}
			else {
				spend -= stam;
				stam = 0;
				man -= spend;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

//caluclates taking ponints from just Stamina or Mana
bool Player::calcCostOne(char type, int cost) {
	if (type == 'M') {
		if (man >= cost) {
			man -= cost;
			return true;
		}
		return false;
	}
	else if(type == 'S'){
		if (stam >= cost) {
			stam -= cost;
			return true;
		}
		return false;

	}
	return false;
}
