#ifndef DUNGEON_ICEMONSTER_H
#define DUNGEON_ICEMONSTER_H
#include "Monster.h"

class IceMonster:public Monster{
public:
//    IceMonster();
//    IceMonster(string,Tag,int,int,int);
    IceMonster(ifstream&,Color&);
    bool triggerEvent(Object*,Color&) final;
    bool getInfo(Color&) final;
};
#endif //DUNGEON_ICEMONSTER_H
