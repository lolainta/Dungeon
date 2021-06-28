#include "Monster.h"

Monster::Monster(string n,Tag t,int h,int a,int d,int v,string fp):value(v),GameCharacter(move(n),t,h,a,d,move(fp)){}
Monster::Monster(ifstream&mtFile,Color&conf){
    vector<string> valid={"name","health","attack","defense","value","filePath"};
    unordered_map<string,string> input;
    string line;
    for(int cnt=0;mtFile>>line;++cnt){
        if(valid[cnt]!=line){
            cout<<conf.set[Output::alert];
            printf("Monster file %d line format invalid!",cnt+1);
            exit(0);
        }
        cout<<conf.set[Output::system];
        if(conf.showDetail)
            printf("Monster file %d line format valid!\n",cnt+1);
        cout<<conf.set[Output::none];
        getline(mtFile,line);
        vector<string> lineList=split(line);
        line="";
        for(string&s:lineList)
            line+=s+" ";
        line.pop_back();
        input[valid[cnt]]=line;
    }
    *this=Monster(input["name"],Tag::MONSTER,stoi(input["health"]),stoi(input["attack"]),stoi(input["defense"]),stoi(input["value"]),input["filePath"]);
}
bool Monster::triggerEvent(Object*,Color&){
    return false;
}
bool Monster::getInfo(Color&){
    return false;
}
