#include "GameCharacter.h"

#include <utility>
//GameCharacter::GameCharacter()=default;
GameCharacter::GameCharacter(string n,Tag t,int h,int a,int d,string fp):
    Object(move(n),t,move(fp)),maxHealth(h),health(h),attack(a),defense(d){}
bool GameCharacter::checkIsDead(Color&conf) const{
    if(health<=0){
        if(conf.showDetail){
            cout<<conf.set[Output::system];
            cout<<"Current health is a non-positive number."<<endl;
            cout<<"\tBy dead theorem, this character is dead."<<endl;
            cout<<conf.set[Output::none];
        }
        return true;
    }else{
        if(conf.showDetail){
            cout<<conf.set[Output::system];
            cout<<"Current health is a positive number."<<endl;
            cout<<"\tBy dead theorem, this character is not dead."<<endl;
            cout<<conf.set[Output::none];
        }
        return false;
    }
}
int GameCharacter::takeDamage(int damage){
    return this->health=max(0,this->health-damage);
}
