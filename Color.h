
#ifndef DUNGEON_COLOR_H
#define DUNGEON_COLOR_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include "enum.h"

using namespace std;
class Color{
private:
    bool mingw;
    void setDefault();
    unordered_map<string,string> linux_gcc;
public:
    unordered_map<string,string> colors;
    bool showDetail;
    unordered_map<Output,string>set;
    static void listAll();
    void init();
    void change(const Output&);

};
#endif //DUNGEON_COLOR_H
