#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;
class Item;
class Player:public GameCharacter{
public:
    Room*currentRoom{};
    Room*previousRoom{};
    int coins;
    vector<Item> inventory;
    Player()=default;
    Player(string,Tag,int,int,int,int,string);
    void addItem(const Item&,Color&);
    bool buyItem(const Item&,Color&);
    void increaseStates(int,int,int,Color&);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*,Color&);
    bool getInfo(Color&);
};
#endif // PLAYER_H_INCLUDED
