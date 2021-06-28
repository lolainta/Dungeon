#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;
class Monster:public GameCharacter{
private:
public:
    int value{};
    Monster(string,Tag,int,int,int,int,string);
    Monster(ifstream&,Color&);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*,Color&) override;
    bool getInfo(Color&) override;
};
#endif // ENEMY_H_INCLUDED
