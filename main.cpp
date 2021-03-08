#include <iostream>
#include <iomanip>
#include<string>
#include <cstdlib>   // rand and srand
#include <ctime>     // For the time function

using namespace std;

void playPVP();
void buildPlayer(string &, int&, int&);
void displayPVPActive(string name, int mag, int maxMag, int stam, int maxStam, int health);
void displayPVPInactive(string name, int mag, int maxMag, int stam, int maxStam, int health);
void fillMoveList(string moveList[][2]);
void fillMoveChoice(string moveList[][2], string moveChoice[]);
int movePick(string moveList[][2], string moveChoice[], int size);
void calcMove(int pick, int& healthP, int& magP, int& stamP, int& healthE, int& magE, int& stamE);
bool calcCost(int& mag, int& stam, int cost);
bool calcCostOne(int& point, int cost);
void levelUp(int& magM, int & stamM);

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
			else if(choice == 2){
				cout << "Not Implemented Yet";
			}
			return 0;
		case 2:
			cout << "--Credits--\n"
				<< "Name1\nName2\nName3\nName4\n";
			cout << endl << "Hit enter to go back to the main menu...\n";
				getline(cin,throwAway);
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
void buildPlayer(string &name, int& mag, int& stam) {
	int choice;
	do {
		cout << "Enter Username For " << name << ": ";
		cin >> name;
		cout << name << ": 3 points in Mana or Stamina?";
		cout << "\n1. Magic \n2. Stamina \n";
		cin >> choice;
		cout << endl;
	}while (choice != 1 && choice != 2);
	if (choice == 1) {
		mag = 3;
		stam = 0;
	}
	else {
		stam = 3;
		mag = 0;
	}

}

void playPVP(){
	//Making Var's
	system("cls");
	string name1 = "Player 1";
	string name2 = "Player 2";
	int mag1, mag2, stam1, stam2;
	int mag1M, mag2M, stam1M, stam2M;
	int health1 = 100, health2 = 100;
	int turn = 1;
	int pick = 0;
	int size = 5;
	string moveChoice[5];
	string moveList[61][2];

	//Bulding PLayer
	buildPlayer(name1, mag1, stam1);
	mag1M = mag1;
	stam1M = stam1;
	buildPlayer(name2, mag2, stam2);
	mag2M = mag2;
	stam2M = stam2;
	cout << "Hit Enter To continue:";
	cin.ignore();
	cin.get();

	//Filling Move List
	system("cls");
	cout << "Loading..." << endl;
	fillMoveList(moveList);

	//Playing Game
	while (health1 > 0 && health2 > 0) {
		fillMoveChoice(moveList, moveChoice);
		system("cls");
		if (turn == 1) {
			while ((mag1 > 0 || stam1 > 0) && pick != -1) {
				displayPVPActive(name1, mag1, mag1M, stam1, stam1M, health1);
				cout << "---------------------------------------------------" << endl;
				displayPVPInactive(name2, mag2, mag2M, stam2, stam2M, health2);
				pick = movePick(moveList, moveChoice, size);
				system("cls");
				if (pick != -1) {
					calcMove(pick, health1, mag1, stam1, health2, mag2, stam2);
					cout << endl;
				}
				size--;
			}

			displayPVPActive(name1, mag1, mag1M, stam1, stam1M, health1);
			cout << "---------------------------------------------------" << endl;
			displayPVPInactive(name2, mag2, mag2M, stam2, stam2M, health2);
			levelUp(mag1M, stam1M);

			cout << "Hit enter to end turn" << endl;
			cin.ignore();
			cin.get();

			//resets everything for next turn
			size = 5;
			pick = 0;
			mag1 = mag1M;
			stam1 = stam1M;

			//Lets player 2 go
			turn = 2;

		}
		else if (turn == 2) {
			while ((mag2 > 0 || stam2 > 0) && pick != -1) {
				displayPVPActive(name2, mag2, mag2M, stam2, stam2M, health2);
				cout << "---------------------------------------------------" << endl;
				displayPVPInactive(name1, mag1, mag1M, stam1, stam1M, health1);
				pick = movePick(moveList, moveChoice, size);
				system("cls");
				if (pick != -1) {
					calcMove(pick, health2, mag2, stam2, health1, mag1, stam1);
					cout << endl;
				}
				size--;
			}

			displayPVPActive(name2, mag2, mag2M, stam2, stam2M, health2);
			cout << "---------------------------------------------------" << endl;
			displayPVPInactive(name1, mag1, mag1M, stam1, stam1M, health1);
			levelUp(mag2M, stam2M);

			cout << "Hit enter to end turn" << endl;
			cin.ignore();
			cin.get();

			//resets everything for next turn
			size = 5;
			pick = 0;
			mag2 = mag2M;
			stam2 = stam2M;

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
	if(health1 > 0){
		cout << name1 << " Wins!";

	}
	else if(health2 > 0){
		cout << name2 << " Wins!";
	}
	else {
		cout << "Draw!";
	}
}

//Fills moveList with all moves in the game and there info;
void fillMoveList(string moveList[][2]) {
	for (int i = 0; i < 61; i++) {
		moveList[i][0] = to_string(i);
	}
	//a list of "Normal" moves for everyone
	moveList[0][1] = "Kick |3pts| Causes 5 Damage";
	moveList[1][1] = "Flick |1pt| Causes 2 Damage";
	moveList[2][1] = "Slap |2pts| Causes 3 Damage";
	moveList[3][1] = "Punch |5pts| Causes 8 Damage";
	moveList[4][1] = "Health Potion |4pts| Heals Player 10 HP";
	moveList[5][1] = "Flee |3pts| Opponent Losses 3 Stamina";
	moveList[6][1] = "Struggle |1pt| Cause 3 Damage & Causes 1 Damage To Yourself";
	moveList[7][1] = "Gauze |2pt| Heals Player 5 HP";
	moveList[8][1] = "Strength |1pt| Gain 5 Stamina For This Turn";
	moveList[9][1] = "Wisdom |1pt| Gain 5 Mana For This Turn";
	moveList[10][1] = "Throw Weapon |ALLpts| Throw Your Weapon, Cause 10 Damage And End Turn";
	moveList[11][1] = "Posion Bomb |8pts| Throw a Bomb That Causes 15 Damage";
	moveList[12][1] = "Joker |1Pts| Throw Card At Opponent, Causes 2 Damage";
	moveList[13][1] = "Iocaine powder |3pts| A Colorless, Odorless, And Deadly Poison From Australia, Cause 5 Damage";
	moveList[14][1] = "My Mango |2pts| Throw a Mango, It Blows Up, Cause 4 Damage";
	moveList[15][1] = "Bite |2pts| Causes 4 Damage";
	moveList[16][1] = "Cave Man |4pts| Throw A Torch, Causes 6 Damage";
	moveList[17][1] = "Leg Sweep |3pts| Trip Opponent, Causes 4 Damage";
	moveList[18][1] = "Throw Rock |1pts| Causes 3 Damage";
	moveList[19][1] = "Hot Hot |2pts| Hey, We Got It, Cause 3 Damage";
	moveList[20][1] = "Power Of Zeus |20pts| With All Your Power You Strike, Cause 50 Damage";
	//A list of moves for Wizards
	moveList[21][1] = "Leach Spell |5pts Mana| Causes 5 Damage & Heals Player 5 HP";
	moveList[22][1] = "Call of the Lizard King |10pts Mana| Zuckerberg Takes All Of The Opponent's Resources For 1 Round";
	moveList[23][1] = "Lightning Bolt |3pts Mana| A simple Yet Effective Spell, Causes 6 Damage";
	moveList[24][1] = "Fire Ball |2pts Mana| A Simple Yet Effective Spell, Causes 4 Damage";
	moveList[25][1] = "Awaken The Dead |5pts Mana| Summon The Undead, Causes 10 Damage";
	moveList[26][1] = "Regeneration Spell |6pts Mana| Heals PLayer 25 HP";
	moveList[27][1] = "Gods Blessing |5pts Mana| An Answered Prayer, Heals Player 50 HP";
	moveList[28][1] = "Body Swap |8pts Mana| Switch Health With Other Player";
	moveList[29][1] = "Magic Missile |1pts Mana| Causes 3 Damage";
	moveList[30][1] = "Health Steal |8pts Mana| Causes 10 Damage & Heals Player 15 HP";
	moveList[31][1] = "Summon Meteor |4pts Mana| Causes 8 Damage";
	moveList[32][1] = "Mimicry |3pts Mana| Use Opponets Stats For 1 Round";
	moveList[33][1] = "Conjure Familiar |5pts Mana| Conjures a Familiar That Causes 7 Damage And Heals 3HP";
	moveList[34][1] = "Magic Armor |5pts Mana| Heals Player 20 HP";
	moveList[35][1] = "Voodoo |2pts Mana| Brings Oppnents Health To Same Level";
	moveList[36][1] = "The Call Of Gaia |3pts Mana| Causes 3 Damage And Heals 7HP";
	moveList[37][1] = "Mana Drain |7pts Mana| Drain Opponets Mana & Gives It To You";
	moveList[38][1] = "Power Drain |7pts Mana| Drain Opponents Stamina & Gives it to you";
	moveList[39][1] = "Punxsutawney Phil |3pts Mana| 6 more Weeks of Winter, Causes 6 Damage";
	moveList[40][1] = "Blood Thirst |10pts Mana| Halves Opponents Health & Doubles Player Health";
	//A list of attack for Warriors
	moveList[41][1] = "Slash |1pt Stamina| Causes 4 Damage";
	moveList[42][1] = "Stab |2pts Stamina| Causes 5 Damage";
	moveList[43][1] = "Arrow To the Knee |5pts Stamina| Causes 5 Damage & Causes Opponent To Lose All Stamina";
	moveList[44][1] = "Headbutt |6pts Stamina| Causes 20 Damage & Take 10 Damage";
	moveList[45][1] = "Charge |3pts Stamina| Charge The Enemy and Cause 8 Damage";
	moveList[46][1] = "Shield Bash |3pts Stamina| Causes 6 Damage";
	moveList[47][1] = "Armor Up |8pts Stamina| Heals Player 5 HP";
	moveList[48][1] = "Thrust Kick |5pts Stamina| Cause 15 Damage";
	moveList[49][1] = "Bear Trap |7pts Stamina| Causes 20 Damage";
	moveList[50][1] = "Dog Call |4pts Stamina| Call A Pack of Wolves, Causes 10 Damage";
	moveList[51][1] = "Shoot Arrow |1pt Stamina| Causes 3 Damage";
	moveList[52][1] = "Fog Horn |10pts Stamina| Call For Backup, Causes 30 Damage";
	moveList[53][1] = "Strangle |4pts Stamina| Cause 20% Damage From Remaining Health";
	moveList[54][1] = "Fog Of War |8pts Stamina| Throw Smoke Bomb, Opponent Loses 50% of there Resources";
	moveList[55][1] = "Ninja Star |2pts Stamina| Causes 5 Damage";
	moveList[56][1] = "Throw Javelin |5pts Stamina| Pierce Chest With Javelin, Cause 18 Damage";
	moveList[57][1] = "Throw Opponent |8pts Stamina| Pick Up And Throw Opponent, Causes 25 Damage";
	moveList[58][1] = "Head Smash |7pts Stamina| Smash The Head Of Your Enemy With Your Bear Hands, Causes 15 Damage";
	moveList[59][1] = "Break Magic|6pts Stamina| Break Opponents Staff In Half, They Lose All Mana For 1 Round";
	moveList[60][1] = "Tackle |10pts Stamina| Cause 25 Damage And Opponent Loses 50% Of There Resources";


}

//Calculates Moves and There posibility
void calcMove(int pick, int& healthP, int& magP, int& stamP, int& healthE, int& magE, int& stamE) {
	switch (pick) {
	case 0: //Kick | 3pts | Causes 5 Damage
		if (calcCost(magP, stamP, 3)) {
			cout << "You use Kick!" << endl;
			healthE -= 5;
		}
		else {
			cout << "You can't use Kick" << endl;
		}
		break;

	case 1: //Flick |1pts| Causes 2 Damage
		if (calcCost(magP, stamP, 1)) {
			cout << "You use Flick!" << endl;
			healthE -= 2;
		}
		else {
			cout << "You can't use Flick" << endl;
		}
		break;

	case 2: //Slap |2pts| Causes 3 Damage
		if (calcCost(magP, stamP, 2)) {
			cout << "You use Slap!" << endl;
			healthE -= 3;
		}
		else {
			cout << "You can't use Slap" << endl;
		}
		break;

	case 3: //Punch |5pts| Causes 8 Damage
		if (calcCost(magP, stamP, 5)) {
			cout << "You use Punch!" << endl;
			healthE -= 8;
		}
		else {
			cout << "You can't use Punch" << endl;
		}
		break;

	case 4: //Health Potion | 4pts | Heals Player 10 HP
		if (calcCost(magP, stamP, 4)) {
			cout << "You use a Health Potion!" << endl;
			healthP += 10;
		}
		else {
			cout << "You can't use a Health Potion" << endl;
		}
		break;

	case 5: //Flee |3pts| Opponent Losses 3 Stamina
		if (calcCost(magP, stamP, 3)) {

			cout << "You Flee" << endl;
			stamE -= 3;
		}
		else {
			cout << "You Can't Flee" << endl;
		}
		break;

	case 6: //Struggle |1pts| Cause 3 Damage & Causes 1 Damage to Yourself
		if (calcCost(magP, stamP, 1)) {
			cout << "You Struggle With Your Opponent!" << endl;
			healthE -= 3;
			healthP -= 1;
		}
		else {
			cout << "You Dont Have The Energy To Struggle" << endl;
		}
		break;

	case 7: //Gauze |2pts| Heals Player 5 HP
		if (calcCost(magP, stamP, 2)) {
			cout << "You Apply Gauze" << endl;
			healthP += 5;
		}
		else {
			cout << "You Don't Have Any Gauze" << endl;
		}
		break;

	case 8: //Strength |1pts| Gain 5 Stamina For This Turn
		if (calcCost(magP, stamP, 1)) {
			cout << "You Become More Powerfull" << endl;
			stamP += 5;
		}
		else {
			cout << "You Are Too Weak..." << endl;
		}
		break;

	case 9: //Wisdom |1pts| Gain 5 Mana For This Turn
		if (calcCost(magP, stamP, 1)) {
			cout << "You Overflow with Knowledge" << endl;
			magP += 5;
		}
		else {
			cout << "You Are Too Ignorant..." << endl;
		}
		break;

	case 10: //Throw Weapon |ALLpts| Throw Your Weapon, Cause 10 Damage And End Turn
		if (calcCost(magP, stamP, 1)) {
			cout << "You Throw Your Weppon As A Last Resort" << endl;
			magP = 0;
			stamP = 0;
			healthE -= 10;
		}
		else {
			cout << "You Have Nothing Left To Give" << endl;
		}
		break;

	case 11: //Posion Bomb |8pts| Throw A Bomb That Causes 15 Damage
		if (calcCost(magP, stamP, 8)) {
			cout << "You Throw A Posion Bomb" << endl;
			healthE -= 15;
		}
		else {
			cout << "You Have No More Posion" << endl;
		}
		break;

	case 12: //Joker |1Pts| Throw Card At Opponent, Causes 2 Damage
		if (calcCost(magP, stamP, 1)) {
			cout << "Card Cuts Opponents Skin" << endl;
			healthE -= 2;
		}
		else {
			cout << "The Joke Is On You" << endl;
		}
		break;

	case 13: //Iocain Powder |3pts| A Colorless, Odorless, And Deadly Poison From Australia, Causes 5 Damage
		if (calcCost(magP, stamP, 3)) {
			cout << "Lets Drink, Me From My Glass & You From Yours" << endl;
			healthE -= 5;
		}
		else {
			cout << "You Don't Have Any Iocain Powder" << endl;
		}
		break;

	case 14: //My Mango |2pts| Throw A Mango, It Blows Up, Cause 4 Damage
		if (calcCost(magP, stamP, 2)) {
			cout << "My Mango Is To Blow Up" << endl;
			healthE -= 4;
		}
		else {
			cout << "You're Mango Did Not Blow Up" << endl;
		}
		break;

	case 15: //Bite |2pts| Causes 4 Damage
		if (calcCost(magP, stamP, 2)) {
			cout << "Chomp Chomp" << endl;
			healthE -= 4;
		}
		else {
			cout << "You Have No Teeth" << endl;
		}
		break;

	case 16: //Cave Man |4pts| Throw A Torch, Causes 6 Damage
		if (calcCost(magP, stamP, 4)) {
			cout << "Your Enemy Catches Fire" << endl;
			healthE -= 6;
		}
		else {
			cout << "You Don't Have Any Fire" << endl;
		}
		break;

	case 17: //Leg Sweep |3pts| Trip Opponent, Causes 4 Damage
		if (calcCost(magP, stamP, 3)) {
			cout << "Bigger They Are, The Harder They Fall" << endl;
			healthE -= 4;
		}
		else {
			cout << "You Can't Trip" << endl;
		}
		break;

	case 18: //Throw Rock |1pts| Causes 3 Damage
		if (calcCost(magP, stamP, 1)) {
			cout << "The Rock Hits Your Opponent In The Face" << endl;
			healthE -= 3;
		}
		else {
			cout << "You Miss" << endl;
		}
		break;

	case 19: //Hot Hot |2pts| Hey, We Got It, Cause 3 Damage
		if (calcCost(magP, stamP, 2)) {
			cout << "It Was Just To Hot Hot" << endl;
			healthE -= 3;
		}
		else {
			cout << "Hey, You Don't Got It..." << endl;
		}
		break;

	case 20: //Power Of Zeus |20pts| With ALL Your Power You Strike, Cause 50 Damage
		if (calcCost(magP, stamP, 20)) {
			cout << "That Is Going To Hurt..." << endl;
			healthE -= 50;
		}
		else {
			cout << "Yeah... Nice Try..." << endl;
		}
		break;

	case 21: //Leach Spell |5pts Mana| Causes 5 Damage & Heals Player 5 HP
		if (calcCostOne(magP, 5)) {
			cout << "You Consume Some Of Your Opponets Power" << endl;
			healthE -= 5;
			healthP -= 5;
		}
		else {
			cout << "You're Not That Thirsty" << endl;
		}
		break;

	case 22: //Call of the Lizard King |10pts Mana| Zuckerberg Takes All Of The Opponet's Resources For 1 Round
		if (calcCostOne(magP, 10)) {
			cout << "You Know A Little To Much Information" << endl;
			magE = 0;
			stamE = 0;
		}
		else {
			cout << "The Lizard King Ignores" << endl;
		}
		break;

	case 23: //Lightning Bolt |3pts Mana| A Simple Yet Effective Spell, Causes 6 Damage
		if (calcCostOne(magP, 3)) {
			cout << "You Strike!" << endl;
			healthE -= 6;
		}
		else {
			cout << "The Gods Are Not With You Today" << endl;
		}
		break;

	case 24: //Fire Ball |2pts Mana| A Simple Yet Effective Spell, Causes 4
		if (calcCostOne(magP, 2)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 25: //Awaken The Dead |5pts Mana| Summon The Undead, Cause 10 Damage
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 26: //Regeneration Spell |6pts Mana| Heals Player 25 HP
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 27: //Gods Blessing |5pts Mana| An Answered Prayer, Heals Player 50 HP;
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 28: //Body Swap |8pts Mana| Switch Health With Other Player;
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 29: //Magic Missile |1pts Mana| Causes 3 Damage
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 30: //Health Steal |8pts Mana| Causes 10 Damage & Heals 15 HP
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 31: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 32: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 33: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 34: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 35: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 36: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 37: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 38: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 39: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	case 40: // |pts Mana|
		if (calcCostOne(magP, 5)) {
			cout << "" << endl;
		}
		else {
			cout << "" << endl;
		}
		break;

	default:
		cout << "Somthing went wrong calculating move" << endl;
		cin.ignore();
		cin.get();
	}

	if (healthP > 100)
		healthP = 100;

	if (magE < 0)
		magE = 0;

	if (stamE < 0)
		stamE = 0;
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
void fillMoveChoice(string moveList[][2], string moveChoice[]) {
	unsigned seed = time(0);
	srand(seed);
	for (int i = 0; i < 5; i++) {
		int random = (rand() % (0 - 21 + 1));
		moveChoice[i] = moveList[random][0];
	}
}

//Lets active player pick move form MoveChoice
int movePick(string moveList[][2], string moveChoice[], int size) {
	int pick;
	int holdPick;
	string hold;
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ". " << moveList[stoi(moveChoice[i])][1] << endl;
	}
	cout << "\nPick a move or enter -1 if finished: ";
	cin >> pick;
	while ((pick > size || pick < 1) && pick != -1) {
		cout << "Not a valid move, try again: ";
		cin >> pick;

	}
	holdPick = pick - 1;
	if (pick != -1) {
		pick = stoi(moveChoice[pick - 1]);
		hold = moveChoice[holdPick];
		moveChoice[holdPick] = moveChoice[size - 1];
	}

	return pick;
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
void displayPVPActive(string name, int mag, int maxMag, int stam, int maxStam, int health){
	cout << "\033[1m\033[32m" << name << "\033[0m" << endl
		<< "Mana Points: " << mag << "/" << maxMag << endl
		<< "Stamina Points: " << stam << "/" << maxStam << endl
		<< "Health: " << health << "/" << 100;
	cout << "|";
	//Displays Health bar
	for (int i = 0; i < 10; i++) {
		if (i < health / 10) {
			cout << (char)219u;
		}
		else if (i < (health / 10) + 1 && health%10 > 0){
			if (health % 10 >= 7) {
				cout << (char)178u;
			}
			else if (health % 10 >= 4){
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
}
void displayPVPInactive(string name, int mag, int maxMag, int stam, int maxStam, int health) {

	cout << "\t\t\t" << "\033[35m" << name << "\033[0m" << endl
		<< "\t\t\tMana Points: " << mag << "/" << maxMag << endl
		<< "\t\t\tStamina Points: " << stam << "/" << maxStam << endl
		<< "\t\t\tHealth: " << health << "/" << 100;
	cout << "|";

	//Displays Health bar
	for (int i = 0; i < 10; i++) {
		if (i < health / 10) {
			cout << (char)219u;
		}
		else if (i < (health / 10) + 1 && health % 10 > 0) {
			if (health % 10 >= 7) {
				cout << (char)178u;
			}
			else if (health >= 4) {
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
