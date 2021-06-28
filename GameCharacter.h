#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED
#include "Object.h"

using namespace std;
class GameCharacter:public Object{
public:
    int maxHealth{};
    int health{};
    int attack{};
    int defense{};
    GameCharacter()=default;
    GameCharacter(string,Tag,int,int,int,string);
    bool checkIsDead(Color&) const;
    int takeDamage(int);
};
#endif // GAMECHARACTER_H_INCLUDED
