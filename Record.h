#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Item.h"
#include "Monster.h"
#include "IceMonster.h"
#include "FireMonster.h"
#include "NPC.h"
#include "Player.h"

using namespace std;

/* This is the record system. Get the information of the  */
/* player and rooms then save them to (a) file(s). Notice */
/* that using pass by reference can prevent sending the   */
/* whole vector to the function.                          */

class Record{
public:
    static void saveRooms(vector<Room>&,ofstream&,Color&);
    static void savePlayer(Player*,ofstream&,Color&);
    static void saveToFile(Player*,vector<Room>&,Color&);
    static void loadRooms(vector<Room>&,ifstream&,Color&);
    static void loadPlayer(Player*,vector<Room>&,ifstream&,Color&);
    static void loadFromFile(Player*,vector<Room>&,const string&,Color&);
};
#endif // RECORD_H_INCLUDED
