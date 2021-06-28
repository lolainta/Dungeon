#include "Item.h"

Item::Item(string name,Tag t,int h,int a,int d,int v,string fp)
        :Object(move(name),t,move(fp)),health(h),attack(a),defense(d),value(v){}
Item::Item(ifstream&itmFile,Color&conf){
    vector<string> valid={"name","health","attack","defense","value","filePath"};
    unordered_map<string,string> input;
    string line;
    for(int cnt=0;itmFile>>line;++cnt){
        if(valid[cnt]!=line){
            cout<<conf.set[Output::alert];
            printf("Item file %d line format invalid!",cnt+1);
            exit(0);
        }
        cout<<conf.set[Output::system];
        if(conf.showDetail){
            printf("Item file %d line format valid!\n",cnt+1);
        }
        cout<<conf.set[Output::none];
        getline(itmFile,line);
        vector<string> lineList=split(line);
        line="";
        for(string&s:lineList)
            line+=s+" ";
        line.pop_back();
        input[valid[cnt]]=line;
    }
    *this=Item(input["name"],Tag::ITEM,stoi(input["health"]),stoi(input["attack"]),stoi(input["defense"]),stoi(input["value"]),input["filePath"]);
}
bool Item::triggerEvent(Object*p,Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Enter Item's trigger Event\n":"");
    cout<<conf.set[Output::interaction];
    auto*player=dynamic_cast<Player*>(p);
    if(player==nullptr){
        cout<<conf.set[Output::alert];
        cout<<(conf.showDetail?"dynamic_cast error\n":"");
        return false;
    }
    if(player->buyItem(*this,conf)){
        cout<<conf.set[Output::system];
        cout<<(conf.showDetail?"Adding item into inventory.\n":"");
        cout<<conf.set[Output::none];
        cout<<conf.set[Output::interaction];
        printf("You got a %s%s.\n",conf.set[Output::name].c_str(),this->name.c_str());
        cout<<conf.set[Output::system];
        cout<<(conf.showDetail?"Item triggerEvent finished.\n":"");
        cout<<conf.set[Output::none];
        return true;
    }else{
        cout<<conf.set[Output::system];
        cout<<(conf.showDetail?"Not enough money to pick up Item\n":"");
        cout<<conf.set[Output::none];
        return false;
    }
}
bool Item::getInfo(Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"\tIn Item::getinfo.\n":"");
    cout<<conf.set[Output::none];
    cout<<conf.colors["YELLOW"];
    cout<<"\t\t$"<<value<<'\n';
    cout<<conf.set[Output::option];
    if(!health && !attack && !defense)
        cout<<"\t\tThis thing is useless XDD.\n";
    if(health)
        cout<<"\t\t+HP: "<<health<<'\n';
    if(attack)
        cout<<"\t\t+ATK: "<<attack<<'\n';
    if(defense)
        cout<<"\t\t+DEF: "<<defense<<'\n';
    return true;
}
