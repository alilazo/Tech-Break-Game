#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
private:
    string name;
    int man;
    int stam;
    int maxMan;
    int maxStam;
    int health;
    int points;
    void toLow();
public:
    bool hurt = false;
    Player(string);
    void buildPlayer();
    void levelUp();
    void displayHurt(Player, Player);
    void displayPVP(Player, Player);
    void reset();
    void playerCalcA(int, int, int, int);
    void playerCalcD(int, int, int);
    bool calcCost(int);
    bool calcCostOne(char, int);

    string getName();
    int getMan();
    int getStam();
    int getHealth();
    int getPoints();
};
#endif // !PLAYER_H
