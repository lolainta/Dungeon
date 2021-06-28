#include "Object.h"

Object::Object():tag(Tag::NONE){}
Object::Object(string n,Tag t,string fp):name(std::move(n)),tag(t),filePath(std::move(fp)){}
