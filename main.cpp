#include <iostream>
#include <iomanip>
#include <string>    //stoi
#include <cstdlib>   // rand and srand
#include <ctime>     // For the time function
#include <fstream>   //reading attack files
#include <vector>    //file Attack array
using namespace std;

struct Player {
	string name;
	int man;
	int stam;
	int maxMan;
	int maxStam;
	int health;

};

// Use This When Adding Attack Codes For The Cards
struct Card {
	string des; //Describes the move, shows up on player screen
	// When using negitive Symble for anything bellow will add to the stats, no negitive will subract;
	int dMan; 
	int dStam;
	int dHealth;
	int aMan;
	int aStam;
	int aHealth;
	int cost;
	char type;
};

void playPVP();
void buildPlayer(Player & p);
void displayPVP(Player pf, Player pd);
void fillMoveList(Card deck[]);
void fillHand(Card deck[], Card hand[]);
Card cardPick(Card hand[], int size);
void calcMove(Card pick, Player& pa, Player& pd);
bool calcCost(int& mag, int& stam, int cost);
bool calcCostOne(int& point, int cost);
void levelUp(int& magM, int& stamM);
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
void buildPlayer(Player & p) {
	int choice;
	do {
		cout << "Enter Username For " << p.name << ": ";
		cin >> p.name;
		cout << p.name << ": 3 points in Mana or Stamina?";
		cout << "\n1. Magic \n2. Stamina \n";
		cin >> choice;
		cout << endl;
	} while (choice != 1 && choice != 2);
	if (choice == 1) {
		p.man = 3;
		p.maxMan = 3;
	}
	else {
		p.stam = 3;
		p.maxStam = 3;
	}

}

void playPVP() {
	//Making Var's
	system("cls");
	Player p1 = { "Player 1", 0, 0, 0, 0, 100 };
	Player p2 = { "Player 2", 0, 0, 0, 0, 100 };
	int turn = 1;
	int handSize = 5;
	Card pick;
	Card hand[5];
	Card deck[61];

	//Bulding Player 1 & 2
	buildPlayer(p1);
	buildPlayer(p2);
	cout << "Hit Enter To continue:";
	cin.ignore();
	cin.get();

	//Filling Move List
	system("cls");
	cout << "Loading..." << endl;
	fillMoveList(deck);

	//Playing Game
	while (p1.health > 0 && p2.health > 0) {
		fillHand(deck, hand);
		system("cls");
		if (turn == 1) {
			while ((p1.man > 0 || p1.stam > 0) && pick.des != "-1") {
				displayPVP(p1, p2);
				pick = cardPick(hand, handSize);
				system("cls");
				if (pick.des != "-1") {
					calcMove(pick, p1, p2);
					cout << endl;
				}
				handSize--;
			}

			displayPVP(p1, p2);

			levelUp(p1.maxMan, p1.maxStam);

			cout << "Hit enter to end turn" << endl;
			cin.ignore();
			cin.get();

			//resets everything for next turn
			handSize = 5;
			pick.des = "0";
			p1.man = p1.maxMan;
			p1.stam = p1.maxStam;

			//Lets player 2 go
			turn = 2;

		}
		else if (turn == 2) {
			while ((p2.man > 0 || p2.stam > 0) && pick.des != "-1") {
				displayPVP(p2, p1);
				pick = cardPick(hand, handSize);
				system("cls");
				if (pick.des != "-1") {
					calcMove(pick, p2, p1);
					cout << endl;
				}
				handSize--;
			}

			displayPVP(p2, p1);
			levelUp(p2.maxMan, p2.maxStam);

			cout << "Hit enter to end turn" << endl;
			cin.ignore();
			cin.get();

			//resets everything for next turn
			handSize = 5;
			pick.des = "0";
			p2.man = p2.maxMan;
			p2.stam = p2.maxStam;

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
	if (p1.health > 0) {
		cout << p1.name << " Wins!";

	}
	else if (p2.health > 0) {
		cout << p2.name << " Wins!";
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
		cout << deck[movecounter].des << deck[movecounter].dMan << deck[movecounter].dStam << deck[movecounter].dHealth << deck[movecounter].aMan << deck[movecounter].aStam << deck[movecounter].aHealth << deck[movecounter].cost << endl << movecounter;
		cin.ignore();
		cin.get();
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
		cout << deck[movecounter].des << deck[movecounter].dMan << deck[movecounter].dStam << deck[movecounter].dHealth << deck[movecounter].aMan << deck[movecounter].aStam << deck[movecounter].aHealth << deck[movecounter].cost << endl << movecounter;
		cin.ignore();
		cin.get();
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
		cout << deck[movecounter].des << deck[movecounter].dMan << deck[movecounter].dStam << deck[movecounter].dHealth << deck[movecounter].aMan << deck[movecounter].aStam << deck[movecounter].aHealth << deck[movecounter].cost << endl << movecounter;
		cin.ignore();
		cin.get();
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
		if (calcCost(pa.man, pa.stam, pick.cost)) {
			cout << "You used " << cardName << "successfully" << endl;

			pa.man -= pick.aMan;
			pa.stam -= pick.aStam;
			pa.health -= pick.aHealth;
			pd.man -= pick.dMan;
			pd.stam -= pick.dStam;
			pd.health -= pick.dHealth;
		}
		else {
			cout << "You can't use " << cardName << endl;

		}
	}
	else if (pick.type == 'S') {
		if (calcCostOne(pa.stam, pick.cost)) {
			cout << "You used " << cardName << "successfully for " << pick.cost << " stamina points" << endl;

			pa.man -= pick.aMan;
			pa.stam -= pick.aStam;
			pa.health -= pick.aHealth;
			pd.man -= pick.dMan;
			pd.stam -= pick.dStam;
			pd.health -= pick.dHealth;
		}else {
			cout << "You can't use " << cardName << endl;

		}
	}
	else if (pick.type == 'M') {
		if (calcCostOne(pa.man, pick.cost)) {
			cout << "You used " << cardName << "successfully for " << pick.cost << " mana points" << endl;

			pa.man -= pick.aMan;
			pa.stam -= pick.aStam;
			pa.health -= pick.aHealth;
			pd.man -= pick.dMan;
			pd.stam -= pick.dStam;
			pd.health -= pick.dHealth;
		}
		else {
			cout << "You can't use " << cardName << endl;

		}
	}
	


	if (pa.health > 100) {
		pa.health = 100;
	}

	if (pd.man < 0) {
		pd.man = 0;
	}

	if (pd.stam < 0) {
		pd.stam = 0;
	}
		
}

//calculates where the game will take points from for the player
bool calcCost(int& mag, int& stam, int cost) {
	int spend = cost;
	if (mag + stam >= cost) {
		if (mag > stam) {
			if (mag >= cost) {
				mag -= spend;
			}
			else {
				spend -= mag;
				mag = 0;
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
				mag -= spend;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

//caluclates taking ponints from just Stamina or Mana
bool calcCostOne(int& point, int cost) {
	if (point >= cost) {
		point -= cost;
		return true;
	}
	return false;
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

//Lets player put more points into Mana or Stamina
void levelUp(int& magM, int& stamM) {
	int choice;
	if (magM >= 10 && stamM >= 10) {
		cout << "You can't level up any more" << endl;
	}
	else if (magM >= 10 && stamM < 10) {
		cout << "You can only level up your Stamina" << endl;
		stamM++;
	}
	else if (stamM >= 10 && magM < 10) {
		cout << "You can only level up your Mana" << endl;
		magM++;
	}
	else {
		cout << "Would you like to level up 1:Mana or 2:Stamina: ";
		cin >> choice;
		while (choice != 1 && choice != 2) {
			cout << "Invalid Try Again: ";
			cin >> choice;
		}
		if (choice == 1) {
			magM++;
		}
		else {
			stamM++;
		}
	}
}

// Everything Under Displays Info For Players on screen
void displayPVP(Player pf, Player pd) {
	// Fighting Player Display
	cout << "\033[1m\033[32m" << pf.name << "\033[0m" << endl
		<< "Mana Points: " << pf.man << "/" << pf.maxMan << endl
		<< "Stamina Points: " << pf.stam << "/" << pf.maxStam << endl
		<< "Health: " << pf.health << "/" << 100;
	cout << "|";
	//Displays Health bar
	for (int i = 0; i < 10; i++) {
		if (i < pf.health / 10) {
			cout << (char)219u;
		}
		else if (i < (pf.health / 10) + 1 && pf.health % 10 > 0) {
			if (pf.health % 10 >= 7) {
				cout << (char)178u;
			}
			else if (pf.health % 10 >= 4) {
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
	cout << "|" << endl;

	cout << "---------------------------------------------------" << endl;

	//Deffending PLayer Display
	cout << "\t\t\t" << "\033[35m" << pd.name << "\033[0m" << endl
		<< "\t\t\tMana Points: " <<pd.man << "/" << pd.maxMan << endl
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
