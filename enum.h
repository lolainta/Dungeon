#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED
enum class Tag{
    NONE,PLAYER,NPC,MONSTER,ITEM
};
enum class Status{
    MENU,OPTIONS,GAMING,OUTPUT
};
//MENU
enum class Menu{
    goGAME,goOPTIONS,SAVE,LOAD,QUIT
};
//OPTIONS
enum class Options{
    CONFIG,goMENU,goOUTPUT
};
//GAMING
enum class Direction{
    UP,DOWN,LEFT,RIGHT,BACK
};
enum class Event{
    showCUR,goMENU,triggerEvent
};
enum class Output{
    system,bar,alert,interaction,option,name,none,goOPTIONS
};
#endif // ENUM_H_INCLUDED
