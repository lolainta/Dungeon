#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include "enum.h"
#include "Color.h"
#include "moon.h"

using namespace std;
class Object{
public:
    string name;
    Tag tag;
    string filePath;
    Object();
    Object(string,Tag,string);
    virtual bool triggerEvent(Object*,Color&) = 0;
    virtual bool getInfo(Color&) = 0;
};
#endif // OBJECT_H_INCLUDED
