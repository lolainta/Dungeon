#ifndef DUNGEON_FIREMONSTER_H
#define DUNGEON_FIREMONSTER_H
#include "Monster.h"
class FireMonster:public Monster{
public:
    FireMonster(ifstream&,Color&);
    bool triggerEvent(Object*,Color&) final;
    bool getInfo(Color&) final;
};
#endif //DUNGEON_FIREMONSTER_H
