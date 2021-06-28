#include "NPC.h"
NPC::NPC(string n,Tag t,string s,vector<Item>&vi,string fp):GameCharacter(move(n),t,0,0,0,move(fp)),script(move(s)),commodity(vi){}
NPC::NPC(ifstream&npcFile,Color&conf){
    vector<string> valid={"name","script","filePath","commodity"};
    unordered_map<string,string> input;
    string line;
    for(int cnt=0;npcFile>>line;++cnt){
        if(valid[cnt]!=line){
            cout<<conf.set[Output::alert];
            printf("NPC file %d line format invalid!",cnt+1);
            exit(0);
        }
        cout<<conf.set[Output::system];
        if(conf.showDetail)
            printf("NPC file %d line format valid!\n",cnt+1);
        cout<<conf.set[Output::none];
        getline(npcFile,line);
        vector<string> lineList=split(line);
        if(cnt!=valid.size()-1){
            line="";
            for(string&s:lineList)
                line+=s+" ";
            line.pop_back();
            input[valid[cnt]]=line;
        }else{
            //last
            vector<Item> com;
            for(const auto&s:lineList){
                ifstream itmFile;
                itmFile.open(s,ios::in);
                com.emplace_back(itmFile,conf);
                itmFile.close();
            }
            *this=NPC(input["name"],Tag::NPC,input["script"],com,input["filePath"]);
            return;
        }
    }
}
unordered_set<string> NPC::listCommodity(Player*player,Color&conf){
    unordered_set<string> ret;
    cout<<conf.set[Output::name];
    cout<<this->name;
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::interaction];
    cout<<": "<<"Hello, my name is "<<conf.set[Output::name]<<this->name<<conf.set[Output::interaction]<<endl;
    cout<<conf.set[Output::name];
    cout<<this->name;
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::interaction];
    cout<<": "<<script<<endl;
    cout<<conf.set[Output::name];
    cout<<this->name;
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::interaction];
    cout<<": "<<"You're welcome! I have "<<commodity.size()<<" item(s) for you to choose.\n";
    for(Item&i:commodity){
        cout<<conf.set[Output::name];
        cout<<'\t'<<i.name<<'\n';
        i.getInfo(conf);
        ret.insert(i.name);
    }
    cout<<conf.set[Output::interaction];
    printf("\tYou have %s$%d%s dollars.\n",conf.colors["YELLOW"].c_str(),player->coins,conf.set[Output::interaction].c_str());
    cout<<"Enter item name to buy or enter 'Q' to quit.\n";
    return ret;
}
bool NPC::triggerEvent(Object*p,Color&conf){
    auto*player=dynamic_cast<Player*>(p);
    if(player==nullptr){
        cout<<conf.set[Output::alert];
        cout<<(conf.showDetail?"dynamic_cast error\n":"");
        return false;
    }
    unordered_set<string> valid=this->listCommodity(player,conf);
    string input;
    while(getline(cin,input)){
        transform(input.begin(),input.end(),input.begin(),[](char c){
              return tolower(c);
        });
        if(input.front()=='q'){
            return false;
        }
        if(valid.count(input)){
            cout<<conf.set[Output::system];
            cout<<(conf.showDetail?"Valid! It is a valid input.\n":"");
            cout<<conf.set[Output::none];
            break;
        }else{
            cout<<conf.set[Output::system];
            cout<<(conf.showDetail?"Invalid! It is an invalid input.\n":"");
            cout<<conf.set[Output::none];
        }
        cout<<conf.set[Output::alert]<<"Your input need to be chosen in the following list.\n"<<conf.set[Output::none];
        this->listCommodity(player,conf);
    }
    vector<Item> tmp;
    assert(tmp.empty());
    for(Item&i:commodity){
        if(i.name!=input){
            tmp.push_back(i);
            continue;
        }
        assert(i.name==input);
        if(!player->buyItem(i,conf)){
            tmp.push_back(i);
        }
    }
    this->commodity=tmp;
    if(this->commodity.empty())
        return true;
    return false;
}
bool NPC::getInfo(Color&conf){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"\tIn NPC::getinfo.\n":"");
    cout<<conf.set[Output::none];
    return true;
}
