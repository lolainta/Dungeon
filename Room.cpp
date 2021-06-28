#include "Room.h"
#include <utility>

Room::Room():isExit(false),upRoom(nullptr),downRoom(nullptr),leftRoom(nullptr),rightRoom(nullptr){}
Room::Room(bool e,int i,vector<Object*> o):isExit(e),index(i),objects(std::move(o)){}
Room::Room(bool e,int i,const vector<Object*>&o,Room*u,Room*d,Room*l,Room*r):
    isExit(e),index(i),objects(o),upRoom(u),downRoom(d),leftRoom(l),rightRoom(r){}
bool Room::popObject(Object*o){
    for(int i=0;i<this->objects.size();++i){
        if(this->objects[i]==o){
            this->objects.erase(this->objects.begin()+i);
//            delete o;
            break;
        }
    }
    return false;
}