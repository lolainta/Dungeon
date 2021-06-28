#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;
class NPC:public GameCharacter{
private:
    string script;
    vector<Item> commodity;
public:
    NPC() = default;
    NPC(string,Tag,string,vector<Item>&,string);
    NPC(ifstream&,Color&);
    unordered_set<string> listCommodity(Player*,Color&); /*print all the Item in this NPC*/

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*,Color&) final;
    bool getInfo(Color&) override;
};
#endif // NPC_H_INCLUDED
