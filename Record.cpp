#include "Record.h"
#include "moon.h"

void Record::saveRooms(vector<Room>&rooms,ofstream&recFile,Color&conf){
    recFile<<rooms.size()<<endl;
    for(const Room&room:rooms){
        if(room.isExit)
            recFile<<'T';
        else
            recFile<<'F';
        recFile<<' ';
        if(room.upRoom)
            recFile<<room.upRoom->index;
        else
            recFile<<-1;
        recFile<<' ';
        if(room.downRoom)
            recFile<<room.downRoom->index;
        else
            recFile<<-1;
        recFile<<' ';
        if(room.leftRoom)
            recFile<<room.leftRoom->index;
        else
            recFile<<-1;
        recFile<<' ';
        if(room.rightRoom)
            recFile<<room.rightRoom->index;
        else
            recFile<<-1;
        recFile<<' ';
        for(Object*obj:room.objects){
            cout<<conf.set[Output::system];
            switch(obj->tag){
                case Tag::NONE:
                    cout<<(conf.showDetail?"Invalid! Find an object with Tag::NONE.\n":"");
                    exit(0);
                case Tag::PLAYER:
                    cout<<(conf.showDetail?"Invalid! Find an object with Tag::PLAYER.\n":"");
                    exit(0);
                case Tag::NPC:
                    assert(dynamic_cast<NPC*>(obj));
                    cout<<(conf.showDetail?"Find an object with Tag::NPC.\n":"");
                    recFile<<"n "<<obj->filePath;
                    break;
                case Tag::MONSTER:
                    cout<<(conf.showDetail?"Find an object with Tag::MONSTER.\n":"");
                    if(dynamic_cast<IceMonster*>(obj)){
                        recFile<<"i "<<obj->filePath;
                    }else{
                        assert(dynamic_cast<FireMonster*>(obj));
                        recFile<<"f "<<obj->filePath;
                    }
                    break;
                case Tag::ITEM:
                    cout<<(conf.showDetail?"Find an object with Tag::ITEM.\n":"");
                    assert(dynamic_cast<Item*>(obj));
                    recFile<<"t "<<obj->filePath;
                    break;
            }
            cout<<conf.set[Output::none];
        }
        recFile<<endl;
    }
}
void Record::savePlayer(Player*player,ofstream&recFile,Color&conf){
    cout<<conf.set[Output::system];
    recFile<<"player->currentRoom->index "<<player->currentRoom->index<<endl;
    cout<<(conf.showDetail?"player->currentRoom->index saved.\n":"");
    recFile<<"player->previousRoom->index "<<(player->previousRoom?player->previousRoom->index:-1)<<endl;
    cout<<(conf.showDetail?"player->previousRoom->index saved.\n":"");
    recFile<<"player->inventory.size() "<<player->inventory.size()<<endl;
    cout<<(conf.showDetail?"player->inventory.size() saved.\n":"");
    for(const Item&itm:player->inventory)
        recFile<<itm.name+".itm ";
    recFile<<endl;
    cout<<(conf.showDetail?"All inventories saved.\n":"");
    recFile<<"player->maxHealth "<<player->maxHealth<<endl;
    cout<<(conf.showDetail?"player->maxHealth saved.\n":"");
    recFile<<"player->health "<<player->health<<endl;
    cout<<(conf.showDetail?"player->health  saved.\n":"");
    recFile<<"player->attack "<<player->attack<<endl;
    cout<<(conf.showDetail?"player->attack saved.\n":"");
    recFile<<"player->defense "<<player->defense<<endl;
    cout<<(conf.showDetail?"player->defense saved.\n":"");
    recFile<<"player->coins "<<player->coins<<endl;
    cout<<(conf.showDetail?"player->coins saved.\n":"");
    recFile<<"player->name "<<player->name<<endl;
    cout<<(conf.showDetail?"player->name saved.\n":"");
}
void Record::saveToFile(Player*p,vector<Room>&r,Color&conf){
    cout<<conf.set[Output::system];
    ofstream recFile;
    recFile.open("record.rec",ios::out);
    if(!recFile){
        cout<<(conf.showDetail?R"(recFile open failed. Please find the file (maybe in "cmake-build.debug" folder).)""\n":"");
    }else{
        cout<<(conf.showDetail?R"(recFile open succeed.)""\n":"");
    }
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Saving rooms.\n":"");
    cout<<conf.set[Output::none];
    saveRooms(r,recFile,conf);
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Room saved.\n":"");
    cout<<(conf.showDetail?"Saving player.\n":"");
    cout<<conf.set[Output::none];
    savePlayer(p,recFile,conf);
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Player saved.\n":"");
    cout<<conf.set[Output::none];
    recFile.close();
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"recFile closed,\n":"");
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::interaction];
    cout<<"File saved success.\n";
    cout<<conf.set[Output::none];
}
void Record::loadRooms(vector<Room>&rooms,ifstream&recFile,Color&conf){
    int n;
    recFile>>n;
    rooms.assign(n,Room());
    for(int i=0;i<n;++i){
        char c;
        recFile>>c;
        unordered_map<char,bool> tf{{'T',true},
                                    {'F',false}};
        int u,d,l,r;//index of other rooms
        string objects;
        recFile>>u>>d>>l>>r;
        getline(recFile,objects);
        rooms[i]=Room(tf[c],i,vector<Object*>(),u==-1?nullptr:&rooms[u],d==-1?nullptr:&rooms[d],l==-1?nullptr:&rooms[l],r==-1?nullptr:&rooms[r]);
        vector<string> obj=split(objects);
        for(int j=0;j<obj.size();++j){
            const string&o=obj[j];
            if(o=="e"){
                break;
            }else if(o=="i"){
                const string&filename=obj[++j];
                ifstream mtFile;
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"Trying to open ":"")<<(conf.showDetail?filename:"")<<endl;
                cout<<conf.set[Output::none];
                mtFile.open(filename,ios::in);
                if(!mtFile){
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?R"(mtFile open failed. Please find the file (maybe in "cmake-build.debug" folder).)""\n":"");
                    exit(0);
                }else{
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?R"(mtFile open succeed.)""\n":"");
                    cout<<conf.set[Output::none];
                }
                rooms[i].objects.push_back(new IceMonster(mtFile,conf));
                mtFile.close();
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"mtFile closed,\n":"");
                cout<<conf.set[Output::none];
            }else if(o=="f"){
                const string&filename=obj[++j];
                ifstream mtFile;
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"Trying to open ":"")<<(conf.showDetail?filename:"")<<endl;
                cout<<conf.set[Output::none];
                mtFile.open(filename,ios::in);
                if(!mtFile){
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?R"(mtFile open failed. Please find the file (maybe in "cmake-build.debug" folder).)""\n":"");
                    exit(0);
                }else{
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?R"(mtFile open succeed.)""\n":"");
                    cout<<conf.set[Output::none];
                }
                rooms[i].objects.push_back(new FireMonster(mtFile,conf));
                mtFile.close();
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"mtFile closed,\n":"");
                cout<<conf.set[Output::none];
            }else if(o=="t"){
                const string&filename=obj[++j];
                ifstream itmFile;
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"Trying to open ":"")<<(conf.showDetail?filename:"")<<endl;
                cout<<conf.set[Output::none];
                itmFile.open(filename,ios::in);
                if(!itmFile){
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?R"(itmFile open failed. Please find the file (maybe in "cmake-build.debug" folder).)""\n":"");
                    exit(0);
                }else{
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?R"(itmFile open succeed.)""\n":"");
                    cout<<conf.set[Output::none];
                }
                rooms[i].objects.push_back(new Item(itmFile,conf));
                itmFile.close();
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"itmFile closed,\n":"");
                cout<<conf.set[Output::none];
            }else if(o=="n"){
                const string&filename=obj[++j];
                ifstream npcFile;
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"Trying to open ":"")<<(conf.showDetail?filename:"")<<endl;
                cout<<conf.set[Output::none];
                npcFile.open(filename,ios::in);
                if(!npcFile){
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?R"(npcFile open failed. Please find the file (maybe in "cmake-build.debug" folder).)""\n":"");
                    exit(0);
                }else{
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?R"(npcFile open succeed.)""\n":"");
                    cout<<conf.set[Output::none];
                }
                rooms[i].objects.push_back(new NPC(npcFile,conf));
                npcFile.close();
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"npcFile closed,\n":"");
                cout<<conf.set[Output::none];
            }else{
                cout<<o<<", a new type of object not known in Record::loadRooms yet."<<endl;
                exit(0);
            }
        }
    }
}
void Record::loadPlayer(Player*player,vector<Room>&rooms,ifstream&recFile,Color&conf){
    string name;
    int num;
    recFile>>name>>num;
    player->currentRoom=&rooms[num];
    recFile>>name>>num;
    player->previousRoom=(num==-1?nullptr:&rooms[num]);
    recFile>>name>>num;
    for(int i=0;i<num;++i){
        recFile>>name;
        ifstream itmFile;
        itmFile.open(name,ios::in);
        player->addItem(Item(itmFile,conf),conf);
        itmFile.close();
    }
    recFile>>name>>num;
    player->maxHealth=num;
    recFile>>name>>num;
    player->health=num;
    recFile>>name>>num;
    player->attack=num;
    recFile>>name>>num;
    player->defense=num;
    recFile>>name>>num;
    player->coins=num;
    recFile>>name;
    getline(recFile,name);
    player->name=name;
    player->tag=Tag::PLAYER;
}
void Record::loadFromFile(Player*player,vector<Room>&rooms,const string&fileName,Color&conf){
    ifstream recFile;
    recFile.open(fileName,ios::in);
    cout<<conf.set[Output::system];
    if(!recFile){
        cout<<(conf.showDetail?R"(recFile open failed. Please find the file (maybe in "cmake-build.debug" folder).)""\n":"");
    }else{
        cout<<(conf.showDetail?R"(recFile open succeed.)""\n":"");
    }
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Loading rooms.\n":"");
    cout<<conf.set[Output::none];
    loadRooms(rooms,recFile,conf);
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Room saved.\n":"");
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Loading player.\n":"");
    cout<<conf.set[Output::none];
    loadPlayer(player,rooms,recFile,conf);
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Player saved.\n":"");
    cout<<conf.set[Output::none];
    recFile.close();
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"recFile closed,\n":"");
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::interaction];
    cout<<"Load file success.\n";
    cout<<conf.set[Output::none];
}
