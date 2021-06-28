#include "Player.h"

Player::Player(string n,Tag t,int h,int a,int d,int c,string fp):GameCharacter(move(n),t,h,a,d,move(fp)),coins(c){}
void Player::changeRoom(Room*pNewRoom){
    this->previousRoom=this->currentRoom;
    if(!pNewRoom){
        cout<<"error??";
        cout<<"There isn't room here QAQ\n";
    }
    this->currentRoom=pNewRoom;
}
bool Player::triggerEvent(Object*,Color&conf){
    cout<<conf.set[Output::bar];
    cout<<">>>>>>>>>>>>>Your status<<<<<<<<<<<<<\n";
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::interaction];
    printf(R"(Your name is "%s%s%s".)""\n",conf.set[Output::name].c_str(),this->name.c_str(),conf.set[Output::interaction].c_str());
    cout<<"You're at room #"<<this->currentRoom->index<<endl;
    cout<<conf.set[Output::none];
    printf("Max health \t: %d\n",maxHealth);
    float ratio=(float)health/(float)maxHealth;
    if(ratio>=0.7)
        cout<<conf.colors["GREEN"];
    else if(ratio>=0.3)
        cout<<conf.colors["YELLOW"];
    else
        cout<<conf.colors["RED"];
    printf("health \t\t: %d\n",health);
    cout<<conf.colors["RED"];
    printf("attack \t\t: %d\n",attack);
    cout<<conf.colors["BLUE"];
    printf("defence \t: %d\n",defense);
    cout<<conf.colors["YELLOW"];
    printf("coins \t\t: %d\n",coins);
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Status printed\n":"");
    cout<<conf.set[Output::none];
    cout<<conf.colors["RESET"];
    cout<<conf.set[Output::interaction];
    cout<<"Enter anything to continue."<<endl;
    string pause;
    getline(cin,pause);
    return false;
}
void Player::addItem(const Item&itm,Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Enter Player::addItem.\n":"");
    cout<<conf.set[Output::none];
    this->inventory.push_back(itm);
    this->increaseStates(itm.health,itm.attack,itm.defense,conf);
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Player::addItem finished.\n":"");
    cout<<conf.set[Output::none];
}
void Player::increaseStates(int h,int a,int d,Color&conf){
    this->health+=h;
    this->attack+=a;
    this->defense+=d;
}
bool Player::getInfo(Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Error! In Player::getinfo.\n":"");
    cout<<conf.set[Output::none];
    return false;
}
bool Player::buyItem(const Item&itm,Color&conf){
    if(this->coins>=itm.value){
        cout<<conf.set[Output::system];
        cout<<(conf.showDetail?"Have enough money to buy.\n":"");
        cout<<conf.set[Output::none];
        this->addItem(itm,conf);
        this->coins-=itm.value;
        return true;
    }else{
        cout<<conf.set[Output::system];
        cout<<(conf.showDetail?"Don't have enough money to buy.\n":"");
        cout<<conf.set[Output::none];
        cout<<conf.set[Output::alert];
        cout<<"You cannot afford this item. QAQ\n";
        cout<<conf.set[Output::none];
        return false;
    }
}
