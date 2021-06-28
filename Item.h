#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <unordered_set>
#include <sstream>
#include "Object.h"
#include "Player.h"

using namespace std;
class Player;
class Item:public Object{
public:
//    Item();
    Item(string,Tag,int,int,int,int,string);
    Item(ifstream&,Color&);
    int health{},attack{},defense{},value{};
    bool getInfo(Color&);
    bool triggerEvent(Object*,Color&);
};
#endif // ITEM_H_INCLUDED
