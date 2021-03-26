#include <iostream>
#include <iomanip>
#include <string>    //stoi
#include <cstdlib>   // rand and srand
#include <ctime>     // For the time function
#include <fstream>   //reading attack files
#include <vector>    //file Attack array

#include "Player.h"

using namespace std;

// Use This When Adding Attack Codes For The Cards
struct Card {
	string des = {}; //Describes the move, shows up on player screen
	// When using negitive Symble for anything bellow will add to the stats, no negitive will subract;
	int dMan = 0;
	int dStam = 0;
	int dHealth = 0;
	int aMan = 0;
	int aStam = 0;
	int aHealth = 0;
	int cost = 0;
	char type = 0;
};

void playPVP();
void fillMoveList(Card deck[]);
void fillHand(Card deck[], Card hand[]);
Card cardPick(Card hand[], int size);
void calcMove(Card pick, Player & pa, Player & pd);
void readAttackFile(vector<string>& attacksArray, string fileName);




int main() {
	int choice;
	string throwAway;
	while (true) {
		do {
			system("cls");
			cout << "Hello & Welcome to 'Name Of the Game'" << endl
				<< "--Menu--" << endl
				<< "1. Play Game \n2. Credits \n3. Leader Board \n4. Quit Game \n";
			cin >> choice;
			system("cls");
			cin.ignore();
		} while (choice < 1 && choice > 4);

		switch (choice) {
		case 1:
			do {
				system("cls");
				choice = 0;
				cout << "--Menu--" << endl
					<< "1. PVP \n2. PVE(Not Implemented) \n";
				cin >> choice;
			} while (choice != 1 && choice != 2);
			if (choice == 1) {
				playPVP();
			}
			else if (choice == 2) {
				cout << "Not Implemented Yet";
			}
			return 0;
		case 2:
			cout << "--Credits--\n"
				<< "Name1\nName2\nName3\nName4\n";
			cout << endl << "Hit enter to go back to the main menu...\n";
			getline(cin, throwAway);
			break;
		case 3:
			cout << "--Leader Board--\n"
				<< "Put 3,5,or10 people here\n";
			cout << endl << "Hit enter to go back to the main menu...\n";
			getline(cin, throwAway);
			break;
		case 4:
			cout << "Teleporting Away... Hopfully not forever!";
			return 0;
		}
	}
}

//Lets player put in username and pick starting class

void playPVP() {
	//Making Var's
	system("cls");
	Player p1("Player 1");
	Player p2("Player 2");
	int turn = 1;
	int handSize = 5;
	Card pick;
	Card hand[5];
	Card deck[61];

	//Bulding Player 1 & 2
	p1.buildPlayer();
	p2.buildPlayer();
	cout << "Hit Enter To continue:";
	cin.ignore();
	cin.get();

	//Filling Move List
	system("cls");
	cout << "Loading..." << endl;
	fillMoveList(deck);

	//Playing Game
	while (p1.getHealth() > 0 && p2.getHealth() > 0) {
		fillHand(deck, hand);
		system("cls");
		if (turn == 1) {
			while ((p1.getMan() > 0 || p1.getStam() > 0) && pick.des != "-1") {
				p1.displayPVP(p1, p2);
				pick = cardPick(hand, handSize);
				system("cls");
				if (pick.des != "-1") {
					calcMove(pick, p1, p2);
					cout << endl;
				}
				handSize--;
			}

			p1.displayPVP(p1, p2);

			p1.levelUp();

			cout << "Hit enter to end turn" << endl;
			cin.ignore();
			cin.get();

			//resets everything for next turn
			handSize = 5;
			pick.des = "0";
			p1.reset();

			//Lets player 2 go
			turn = 2;

		}
		else if (turn == 2) {
			while ((p2.getMan() > 0 || p2.getStam() > 0) && pick.des != "-1") {
				p2.displayPVP(p2, p1);
				pick = cardPick(hand, handSize);
				system("cls");
				if (pick.des != "-1") {
					calcMove(pick, p2, p1);
					cout << endl;
				}
				handSize--;
			}

			p2.displayPVP(p2, p1);
			p2.levelUp();

			cout << "Hit enter to end turn" << endl;
			cin.ignore();
			cin.get();

			//resets everything for next turn
			handSize = 5;
			pick.des = "0";
			p2.reset();

			//Lets player 1 go
			turn = 1;
		}
		else {
			cout << "Turn Error Check Code and Fix!";
			cin.ignore();
			cin.get();
		}
	}

	//Winner Screen
	system("cls");
	if (p1.getHealth() > 0) {
		cout << p1.getName() << " Wins!";

	}
	else if (p2.getHealth() > 0) {
		cout << p2.getName() << " Wins!";
	}
	else {
		cout << "Draw!";
	}
}

//Fills moveList with all moves in the game and there info;
void fillMoveList(Card deck[]) {

	vector<string> normal_Attacks;
	vector<string> wizard_Attacks;
	vector<string> warrior_Attacks;
	readAttackFile(normal_Attacks, "./Attacks/Normal_Attacks.dat");
	readAttackFile(wizard_Attacks, "./Attacks/Wizard_Attacks.dat");
	readAttackFile(warrior_Attacks, "./Attacks/Warrior_Attacks.dat");

	int movecounter = 0;

	//Filling deck with normal cards
	ifstream normalDeck;
	normalDeck.open("./Attacks/Normal_Attacks.dat");
	for (int i = 0; i < normal_Attacks.size()/2; i++) {
		getline(normalDeck, deck[movecounter].des);
		normalDeck >> deck[movecounter].dMan >> deck[movecounter].dStam >> deck[movecounter].dHealth >> deck[movecounter].aMan >> deck[movecounter].aStam >> deck[movecounter].aHealth >> deck[movecounter].cost;
		deck[movecounter].type = 'N';
		
		normalDeck.get();
		movecounter++;
	}
	normalDeck.close();

	//Filling deck with wizard cards
	ifstream wizardDeck;
	wizardDeck.open("./Attacks/Wizard_Attacks.dat");
	for (int i = 0; i < wizard_Attacks.size() / 2; i++) {
		getline(wizardDeck, deck[movecounter].des);
		wizardDeck >> deck[movecounter].dMan >> deck[movecounter].dStam >> deck[movecounter].dHealth >> deck[movecounter].aMan >> deck[movecounter].aStam >> deck[movecounter].aHealth >> deck[movecounter].cost;
		deck[movecounter].type = 'M';
		
		wizardDeck.get();
		movecounter++;
	}
	wizardDeck.close();

	//Filling deck with warrior cards
	ifstream warriorDeck;
	warriorDeck.open("./Attacks/Warrior_Attacks.dat");
	for (int i = 0; i < warrior_Attacks.size() / 2; i++) {
		string extra;
		getline(warriorDeck, deck[movecounter].des);
		warriorDeck >> deck[movecounter].dMan >> deck[movecounter].dStam >> deck[movecounter].dHealth >> deck[movecounter].aMan >> deck[movecounter].aStam >> deck[movecounter].aHealth >> deck[movecounter].cost;
		deck[movecounter].type = 'S';
		
		warriorDeck.get();
		movecounter++;
	}
	warriorDeck.close();



}

//File system for generating attacks
void readAttackFile(vector<string>& attacksArray, string fileName) {
	ifstream cardFile;
	cardFile.open(fileName);
	if (!cardFile.is_open()) {
		cout << endl << "An error occurred opening " << fileName << endl;
		exit(EXIT_FAILURE);
	}
	string line;
	while (getline(cardFile, line)) {
		attacksArray.push_back(line);
	}
	cardFile.close();
}

//Calculates Moves and There posibility
void calcMove(Card pick, Player & pa, Player & pd) {
	int stringBreak = pick.des.find('|');
	string cardName;
	cardName.append(pick.des, 0, stringBreak);
	if (pick.type == 'N') {
		if (pa.calcCost(pick.cost)) {
			cout << pick.des << endl;
			cout << "You used " << cardName << "successfully for " << pick.cost << " points" << endl;
			cout << pick.aMan << pick.aStam << pick.aHealth;
			cout << pick.dMan << pick.dStam << pick.dHealth;

			pa.playerCalcA(pick.aMan, pick.aStam, pick.aHealth);
			pd.playerCalcD(pick.dMan, pick.dStam, pick.dHealth);
		}
		else {
			cout << "You can't use " << cardName << endl;

		}
	}
	else if (pick.type == 'S') {
		if (pa.calcCostOne('S', pick.cost)) {
			cout << "You used " << cardName << "successfully for " << pick.cost << " stamina points" << endl;

			pa.playerCalcA(pick.aMan, pick.aStam, pick.aHealth);
			pd.playerCalcD(pick.dMan, pick.dStam, pick.dHealth);

		}else {
			cout << "You can't use " << cardName << endl;

		}
	}
	else if (pick.type == 'M') {
		if (pa.calcCostOne('M', pick.cost)) {
			cout << "You used " << cardName << "successfully for " << pick.cost << " mana points" << endl;

			pa.playerCalcA(pick.aMan, pick.aStam, pick.aHealth);
			pd.playerCalcD(pick.dMan, pick.dStam, pick.dHealth);

		}
		else {
			cout << "You can't use " << cardName << endl;

		}
	}

}



// randomly fills 5 moves into a list for the player to choose from
void fillHand(Card deck[], Card hand[]) {
	unsigned seed = time(0);
	srand(seed);
	for (int i = 0; i < 5; i++) {
		int random = (rand() % (0 - 62 + 3));
		hand[i] = deck[random];
	}
}

//Lets active player pick move form MoveChoice
Card cardPick(Card hand[], int size) {
	int pick;
	Card cardSwitch;
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ". " << hand[i].des << endl;
	}
	cout << "\nPick a move or enter -1 if finished: ";
	cin >> pick;
	while ((pick > size || pick < 1) && pick != -1) {
		cout << "Not a valid move, try again: ";
		cin >> pick;

	}
	if (pick != -1) {
		cardSwitch = hand[pick - 1];
		hand[pick - 1] = hand[size - 1];
		hand[size - 1] = cardSwitch;
	}
	else {
		cardSwitch.des = "-1";
	}

	return cardSwitch;
}

