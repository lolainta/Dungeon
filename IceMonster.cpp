#include "IceMonster.h"

bool IceMonster::triggerEvent(Object*p,Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Enter IceMonster's trigger Event\n":"");
    cout<<conf.set[Output::interaction];
    auto*player=dynamic_cast<Player*>(p);
    if(player==nullptr){
        cout<<conf.set[Output::alert];
        cout<<(conf.showDetail?"dynamic_cast error\n":"");
        return false;
    }
    printf("Player health : %d \tIceMonster health : %d\n",player->health,this->health);
    while(!player->checkIsDead(conf) || !this->checkIsDead(conf)){
        cout<<conf.set[Output::interaction];
        cout<<"Player attacked IceMonster.\n";
        if(this->takeDamage(max(0,player->attack-this->defense))<=0){
            cout<<conf.set[Output::interaction];
            printf("Player health : %d \tIceMonster health : %d\n",player->health,this->health);
            cout<<"IceMonster is dead.\n";
            cout<<conf.set[Output::none];
            assert(!this->health);
            player->coins+=this->value;
            cout<<conf.set[Output::interaction];
            printf("You win the fight, you got %d coins.\n",this->value);
            break;
        }
        cout<<conf.set[Output::interaction];
        printf("Player health : %d \tIceMonster health : %d\n",player->health,this->health);
        cout<<"IceMonster attacked player.\n";
        if(player->takeDamage(max(0,this->attack-player->defense))<=0){
            cout<<conf.set[Output::interaction];
            printf("Player health : %d \tIceMonster health : %d\n",player->health,this->health);
            cout<<"You are dead.\n";
            cout<<conf.set[Output::none];
            assert(!player->health);
            break;
        }
        printf("Player health : %d \tIceMonster health : %d\n",player->health,this->health);
    }
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Fight finished.\n":"");
    cout<<(conf.showDetail?"IceMonster triggerEvent finished.\n":"");
    cout<<conf.set[Output::none];
    return true;
}
IceMonster::IceMonster(ifstream&mFile,Color&conf):Monster(mFile,conf){}
bool IceMonster::getInfo(Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"\tIn IceMonster::getinfo.\n":"");
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::interaction];
    printf("\tThis is a IceMonster. It's name is %s%s%s\n",conf.set[Output::name].c_str(),this->name.c_str(),conf.set[Output::none].c_str());
    cout<<conf.set[Output::interaction];
    printf("\tHP: %d, ATK: %d, DEF: %d, $%d\n",this->health,this->attack,this->defense,this->value);
    return true;
}
