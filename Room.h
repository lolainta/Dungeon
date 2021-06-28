#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
#include "Object.h"

using namespace std;
class Room{
public:
    Room*upRoom{};
    Room*downRoom{};
    Room*leftRoom{};
    Room*rightRoom{};
    bool isExit;
    int index{};
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
    Room();
    Room(bool,int,vector<Object*>);
    Room(bool,int,const vector<Object*>&,Room*,Room*,Room*,Room*);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/
};
#endif // ROOM_H_INCLUDED
