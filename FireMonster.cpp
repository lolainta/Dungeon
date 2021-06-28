#include "FireMonster.h"

bool FireMonster::triggerEvent(Object*p,Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Enter FireMonster's trigger Event\n":"");
    cout<<conf.set[Output::interaction];
    auto*player=dynamic_cast<Player*>(p);
    if(player==nullptr){
        cout<<conf.set[Output::alert];
        cout<<(conf.showDetail?"dynamic_cast error\n":"");
        return false;
    }
    printf("Player health : %d \tFireMonster health : %d\n",player->health,this->health);
    while(!player->checkIsDead(conf) || !this->checkIsDead(conf)){
        cout<<conf.set[Output::interaction];
        cout<<"Player attacked FireMonster.\n";
        if(this->takeDamage(max(0,player->attack-this->defense))<=0){
            cout<<conf.set[Output::interaction];
            printf("Player health : %d \tFireMonster health : %d\n",player->health,this->health);
            cout<<"FireMonster is dead.\n";
            cout<<conf.set[Output::none];
            assert(!this->health);
            player->coins+=this->value;
            cout<<conf.set[Output::interaction];
            printf("You win the fight, you got %d coins.\n",this->value);
            break;
        }
        cout<<conf.set[Output::interaction];
        printf("Player health : %d \tFireMonster health : %d\n",player->health,this->health);
        cout<<"FireMonster attacked player.\n";
        if(player->takeDamage(max(0,this->attack-player->defense))<=0){
            cout<<conf.set[Output::interaction];
            printf("Player health : %d \tFireMonster health : %d\n",player->health,this->health);
            cout<<"You are dead.\n";
            cout<<conf.set[Output::none];
            assert(!player->health);
            break;
        }
        printf("Player health : %d \tFireMonster health : %d\n",player->health,this->health);
    }
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Fight finished.\n":"");
    cout<<(conf.showDetail?"FireMonster triggerEvent finished.\n":"");
    cout<<conf.set[Output::none];
    return true;
}
FireMonster::FireMonster(ifstream&mFile,Color&conf):Monster(mFile,conf){}
bool FireMonster::getInfo(Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"\tIn FireMonster::getinfo.\n":"");
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::interaction];
    printf("\tThis is a FireMonster. It's name is %s%s%s\n",conf.set[Output::name].c_str(),this->name.c_str(),conf.set[Output::none].c_str());
    cout<<conf.set[Output::interaction];
    printf("\tHP: %d, ATK: %d, DEF: %d, $%d\n",this->health,this->attack,this->defense,this->value);
    return true;
}
