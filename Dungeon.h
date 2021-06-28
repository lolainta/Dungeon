#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include "Record.h"

using namespace std;
class Dungeon{
private:
    Color conf;
    Player player;
    vector<Room> rooms;
    Status status=Status::MENU;
    vector<pair<char,string>> cmdMENU{{'g',"Start Game"},
                                      {'o',"Options"},
                                      {'z',"Save file"},
                                      {'l',"Load from record"},
                                      {'q',"Quit without saving"}};
    vector<pair<char,string>> cmdOPTIONS{{'c',"Details showing"},
                                         {'p',"Change colors"},
                                         {'q',"Back to menu"},};
    vector<pair<char,string>> cmdPREFERENCE{{'q',"Back to options"},
                                            {'0',"system color\t\t(You can only test when you turn on showing all details in configuration)"},
                                            {'1',"bar color\t\t\t(You may see it immediately)"},
                                            {'2',"alert color\t\t\t(You can test it by entering anything not in this list.)"},
                                            {'3',"interaction color\t(You may see it immediately)"},
                                            {'4',"option color\t\t(You may see it immediately)"},
                                            {'9',"Reset to default\t(Every thing you changed will be discard)"}};//in the output order (KEYS CANNOT BE REPEATED)
    vector<pair<char,string>> cmdGAMING{{'b',"Back to previous room\n"},
                                        {'w',"Move Up\n"},
                                        {'a',"Move Left\n"},
                                        {'s',"Move Down\n"},
                                        {'d',"Move Right\n"},
                                        {'1',"Fight with monster"},
                                        {'2',"Fight with monster"},
                                        {'3',"Fight with monster"},
                                        {'4',"Pick up item"},
                                        {'5',"Pick up item"},
                                        {'6',"Pick up item"},
                                        {'7',"Talk with NPC"},
                                        {'8',"Talk with NPC"},
                                        {'9',"Talk with NPC"},
                                        {'e',"Show status\n"},
                                        {'q',"Back to menu\n"}};
    void handleMENU(const Menu&);
    void handleOPTIONS(const Options&);
    void handleOUTPUT(const Output&);
    void find_neighbor_rooms(unordered_set<char>&) const;
    unordered_map<char,int> find_room_objects(Room*,unordered_set<char>&);
    void ls(const unordered_set<char>&,unordered_map<char,int>&);
    /* Create a new player, and give him/her basic status */
    void createPlayer();
    /* Create a map, which include several different rooms */
    void createMap();
    /* Deal with player's moveing action */
    void handleMovement(const Direction&);
    /* Deal with player's iteraction with objects in that room */
    void handleEvent(const Event&,Object*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
    void chooseAction(Room*);

    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();
    void config();
public:
    Dungeon();
    /* Deal with the whole game process */
    void runDungeon();
};
#endif // DUNGEON_H_INCLUDED
