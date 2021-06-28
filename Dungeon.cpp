#include "Dungeon.h"

Dungeon::Dungeon(){
    conf.init();
    this->status=Status::MENU;
    conf.showDetail=true;
}
void Dungeon::runDungeon(){
    this->config();
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Start run dungeon\n":"");
    cout<<conf.set[Output::none];
    this->startGame();
    while(this->checkGameLogic())
        chooseAction(player.currentRoom);
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"GameLogic==false, input ended.\n":"");
    cout<<conf.set[Output::none];
    if(player.health==0){
        cout<<conf.set[Output::alert];
        cout<<R"(***********************************************************)"<<endl;
        cout<<R"(*   ____    _    __  __ _____    _____     _______ ____   *)"<<endl;
        cout<<R"(*  / ___|  / \  |  \/  | ____|  / _ \ \   / / ____|  _ \  *)"<<endl;
        cout<<R"(* | |  _  / _ \ | |\/| |  _|   | | | \ \ / /|  _| | |_) | *)"<<endl;
        cout<<R"(* | |_| |/ ___ \| |  | | |___  | |_| |\ V / | |___|  _ <  *)"<<endl;
        cout<<R"(*  \____/_/   \_\_|  |_|_____|  \___/  \_/  |_____|_| \_\ *)"<<endl;
        cout<<R"(***********************************************************)"<<endl;
        cout<<conf.set[Output::none];
    }else{
        cout<<conf.set[Output::alert];
        cout<<"Congratulation! You found the exit!!\n";
        cout<<conf.set[Output::alert];
        cout<<R"(***************************************************************************************)"<<endl;
        cout<<R"(*   ____ ___  _   _  ____ ____      _  _____ _   _ _        _  _____ ___ ___   _   _  *)"<<endl;
        cout<<R"(*  / ___/ _ \| \ | |/ ___|  _ \    / \|_   _| | | | |      / \|_   _|_ _/ _ \ | \ | | *)"<<endl;
        cout<<R"(* | |  | | | |  \| | |  _| |_) |  / _ \ | | | | | | |     / _ \ | |  | | | | ||  \| | *)"<<endl;
        cout<<R"(* | |__| |_| | |\  | |_| |  _ <  / ___ \| | | |_| | |___ / ___ \| |  | | |_| || |\  | *)"<<endl;
        cout<<R"(*  \____\___/|_| \_|\____|_| \_\/_/   \_\_|  \___/|_____/_/   \_\_| |___\___/ |_| \_| *)"<<endl;
        cout<<R"(***************************************************************************************)"<<endl;
        cout<<conf.set[Output::none];
    }
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"runDungeon finished\n":"");
    cout<<conf.set[Output::none];
}
void Dungeon::startGame(){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Creating a new map...\n":"");
    cout<<conf.set[Output::none];
    this->createMap();
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"New map created\n":"");
    cout<<conf.set[Output::none];
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Creating a new player...\n":"");
    cout<<conf.set[Output::none];
    this->createPlayer();
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"New player created\n":"");
}
void Dungeon::createMap(){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Creating map from room.init\n":"");
    ifstream initFile;
    initFile.open("room.init",ios::in);
    if(!initFile){
        cout<<(conf.showDetail?R"(initFile open failed. Please find the file (maybe in "cmake-build.debug" folder).)""\n":"");
    }else{
        cout<<(conf.showDetail?R"(initFile open succeed.)""\n":"");
    }
    Record::loadRooms(rooms,initFile,conf);
    initFile.close();
}
void Dungeon::createPlayer(){
    cout<<conf.set[Output::interaction]<<"Please enter your name : "<<conf.set[Output::none];
    string name;
    getline(cin,name);
    cout<<conf.set[Output::interaction]<<"Hello, "<<conf.set[Output::name]<<name<<conf.set[Output::interaction]<<"!\n"<<conf.set[Output::none];
    ifstream initFile;
    initFile.open("player.init",ios::in);
    cout<<conf.set[Output::system];
    if(!initFile){
        cout<<(conf.showDetail?R"(initFile open failed. Please find the file (maybe in "cmake-build.debug" folder).)""\n":"");
    }else{
        cout<<(conf.showDetail?R"(initFile open succeed.)""\n":"");
    }
    Record::loadPlayer(&player,rooms,initFile,conf);
    player.name=name;
}
bool Dungeon::checkGameLogic(){
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Checking game logic.\n":"");
    cout<<conf.set[Output::none];
    if(player.currentRoom->isExit || !player.health){
        cout<<conf.set[Output::system];
        cout<<(conf.showDetail?"Game logic checked false.\n":"");
        cout<<conf.set[Output::none];
        return false;
    }
    return true;
}
void Dungeon::chooseAction(Room*room){
    unordered_set<char> valid;
    unordered_map<char,int> eventIndex;
    switch(status){
        case Status::MENU:
            valid={'g','z','l','q','o'};
            break;
        case Status::OPTIONS:
            valid={'c','p','q'};
            break;
        case Status::GAMING:
            valid={'e','q'};
            find_neighbor_rooms(valid);
            eventIndex=find_room_objects(room,valid);
            break;
        case Status::OUTPUT:
            valid={'0','1','2','3','4','9','q'};
            break;
    }
    cout<<conf.set[Output::interaction]<<"Choose one of the following actions.\n"<<conf.set[Output::none];
    this->ls(valid,eventIndex);
    string input;
    while(getline(cin,input)){
        transform(input.begin(),input.end(),input.begin(),[](char c){
              return tolower(c);
        });
        bool size=false,vd=false;
        if(input.size()==1){
            cout<<conf.set[Output::system];
            cout<<(conf.showDetail?"Valid! Input one character only.\n":"");
            cout<<conf.set[Output::none];
            size=true;
        }
        if(valid.count(input.front())){
            cout<<conf.set[Output::system];
            cout<<(conf.showDetail?"Valid! It is a valid input.\n":"");
            cout<<conf.set[Output::none];
            vd=true;
        }
        if(size&vd)
            break;
        if(!size){
            cout<<conf.set[Output::system];
            if(conf.showDetail)
                cout<<"Invalid! Inputted "<<input.size()<<" characters.\n";
            cout<<conf.set[Output::none];
            cout<<conf.set[Output::alert]<<"Please input a character only!\n";
        }
        if(!vd){
            cout<<conf.set[Output::system];
            cout<<(conf.showDetail?"Invalid! It is an invalid input.\n":"");
            cout<<conf.set[Output::none];
            cout<<conf.set[Output::alert]<<"Please input the following output only!\n";
        }
        cout<<conf.set[Output::interaction]<<"Choose one of the following actions.\n";
        this->ls(valid,eventIndex);
    }
    switch(status){
        case Status::MENU:{
            unordered_map<char,Menu> mean{{'g',Menu::goGAME},
                                          {'o',Menu::goOPTIONS},
                                          {'z',Menu::SAVE},
                                          {'l',Menu::LOAD},
                                          {'q',Menu::QUIT}};
            if(valid.size()==mean.size()){
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"map<>mean.size()==set<>valid.size()\n":"");
                cout<<conf.set[Output::none];
            }else{
                cout<<conf.set[Output::system]<<"Here is a bug. Come and find me\n"<<conf.set[Output::none];
            }
            this->handleMENU(mean[input.front()]);
            break;
        }
        case Status::OPTIONS:{
            unordered_map<char,Options> mean{{'t',Options::CONFIG},
                                             {'p',Options::goOUTPUT},
                                             {'q',Options::goMENU}};
            if(valid.size()==mean.size()){
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"map<>mean.size()==set<>valid.size()\n":"");
                cout<<conf.set[Output::none];
            }else{
                cout<<conf.set[Output::system]<<"Here is a bug. Come and find me\n"<<conf.set[Output::none];
            }
            this->handleOPTIONS(mean[input.front()]);
            break;
        }
        case Status::GAMING:{
            unordered_map<char,Direction> move{{'w',Direction::UP},
                                               {'s',Direction::DOWN},
                                               {'a',Direction::LEFT},
                                               {'d',Direction::RIGHT},
                                               {'b',Direction::BACK}};
            unordered_map<char,Event> event{{'e',Event::showCUR},
                                            {'q',Event::goMENU},
                                            {'1',Event::triggerEvent},
                                            {'2',Event::triggerEvent},
                                            {'3',Event::triggerEvent},
                                            {'4',Event::triggerEvent},
                                            {'5',Event::triggerEvent},
                                            {'6',Event::triggerEvent},
                                            {'7',Event::triggerEvent},
                                            {'8',Event::triggerEvent},
                                            {'9',Event::triggerEvent}};
            if(valid.size()==move.size()+event.size()){
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"move.size()+event.size()==valid.size()\n":"");
                cout<<conf.set[Output::none];
            }else{
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"move.size()+event.size()!=valid.size()\n":"");
                cout<<conf.set[Output::none];
            }
            if(move.count(input.front()))
                this->handleMovement(move[input.front()]);
            else if(event.count(input.front()))
                this->handleEvent(event[input.front()],(event[input.front()]==Event::triggerEvent?room->objects[eventIndex[input.front()]]:nullptr));
            break;
        }
        case Status::OUTPUT:{
            unordered_map<char,Output> mean{{'0',Output::system},
                                            {'1',Output::bar},
                                            {'2',Output::alert},
                                            {'3',Output::interaction},
                                            {'4',Output::option},
                                            {'9',Output::none},//Output::none is used to set default
                                            {'q',Output::goOPTIONS}};
            if(valid.size()==mean.size()){
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"map<>mean.size()==set<>valid.size()\n":"");
                cout<<conf.set[Output::none];
            }else{
                cout<<conf.set[Output::system]<<"Here is a bug. Come and find me\n"<<conf.set[Output::none];
            }
            this->handleOUTPUT(mean[input.front()]);
            break;
        }
    }
}
void Dungeon::find_neighbor_rooms(unordered_set<char>&valid) const{
    if(player.previousRoom)
        valid.insert('b');
    if(any_of(player.currentRoom->objects.begin(),player.currentRoom->objects.end(),[](Object*o){return o->tag==Tag::MONSTER;}))
        return;
    if(player.currentRoom->upRoom)
        valid.insert('w');
    if(player.currentRoom->downRoom)
        valid.insert('s');
    if(player.currentRoom->leftRoom)
        valid.insert('a');
    if(player.currentRoom->rightRoom)
        valid.insert('d');
}
unordered_map<char,int> Dungeon::find_room_objects(Room*room,unordered_set<char>&valid){
    unordered_map<char,int> ret;
    cout<<conf.set[Output::system];
    cout<<(conf.showDetail?"Checking if there is anything in the room.\n":"");
    conf.set[Output::none];
    if(!room->objects.empty()){
        cout<<conf.set[Output::system];
        cout<<(conf.showDetail?"There's something in the room.\n":"");
        cout<<conf.set[Output::none];
        char cntM='1';
        char cntI='4';
        char cntN='7';
        for(int i=0;i<room->objects.size();++i){
            const Object*o=room->objects[i];
            if(cntM>'3' || cntI>'6' || cntN>'9'){
                cout<<conf.set[Output::alert];
                cout<<"You can only put three same kind of things in a room. Because I'm weak. T_T\n";
                exit(0);
            }
            switch(o->tag){
                case Tag::NONE:
                    cout<<"Bug detected! This object don't have Tag!!\n";
                    break;
                case Tag::PLAYER:
                    cout<<"Bug detected! An object with Tag::PLAYER found in room#"<<room->index<<endl;
                    break;
                case Tag::NPC:
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?"A NPC detected in the room.\n":"");
                    cout<<conf.set[Output::none];
                    valid.insert(cntN);
                    ret[cntN++]=i;
                    break;
                case Tag::MONSTER:
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?"A monster detected in the room.\n":"");
                    cout<<conf.set[Output::none];
                    valid.insert(cntM);
                    ret[cntM++]=i;
                    break;
                case Tag::ITEM:
                    cout<<conf.set[Output::system];
                    cout<<(conf.showDetail?"An item detected in the room.\n":"");
                    cout<<conf.set[Output::none];
                    valid.insert(cntI);
                    ret[cntI++]=i;
                    break;
            }
        }
    }else{
        cout<<conf.set[Output::system];
        cout<<(conf.showDetail?"There's nothing in the room.\n":"");
        cout<<conf.set[Output::none];
    }
    return ret;
}
void Dungeon::config(){
    string input;
    cout<<conf.set[Output::interaction];
    cout<<"Do you want to show all details? [Y/n] ";
    cout<<conf.set[Output::none];
    while(getline(cin,input)){
        transform(input.begin(),input.end(),input.begin(),[](char c){
              return tolower(c);
        });
        unordered_set<string> valid{"yes","y","no","n"};
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
        cout<<conf.set[Output::alert]<<R"(Please input "yes" or "no" )""\n";
        cout<<conf.set[Output::interaction]<<"Do you want to show all details? [Y/n] ";
    }
    unordered_map<string,bool> mean{{"yes",true},
                                    {"y",  true},
                                    {"no", false},
                                    {"n",  false}};
    this->conf.showDetail=mean[input];
}
void Dungeon::ls(const unordered_set<char>&valid,unordered_map<char,int>&eventIndex){
    cout<<conf.set[Output::bar];
    cout<<"==============";
    switch(this->status){
        case Status::MENU:
            cout<<"===MENU===";
            cout<<"==============\n";
            cout<<conf.set[Output::none];
            cout<<conf.set[Output::option];
            for(const pair<char,string>&p:cmdMENU){
                if(valid.count(p.first)){
                    printf("(%c) %s\n",toupper(p.first),p.second.c_str());
                }
            }
            break;
        case Status::OPTIONS:
            cout<<"=OPTIONS==";
            cout<<"==============\n";
            cout<<conf.set[Output::none];
            cout<<conf.set[Output::option];
            for(const pair<char,string>&p:cmdOPTIONS){
                if(valid.count(p.first)){
                    printf("(%c) %s\n",toupper(p.first),p.second.c_str());
                }
            }
            break;
        case Status::GAMING:
            cout<<"==GAMING==";
            cout<<"==============\n";
            cout<<conf.set[Output::none];
            for(const pair<char,string>&p:cmdGAMING){
                if(valid.count(p.first)){
                    cout<<conf.set[Output::option];
                    printf("(%c) %s",toupper(p.first),p.second.c_str());
                    cout<<conf.set[Output::none];
                }
                if(eventIndex.count(p.first)){
                    printf(" %s%s\n",conf.set[Output::name].c_str(),this->player.currentRoom->objects[eventIndex[p.first]]->name.c_str());
                    if(this->player.currentRoom->objects[eventIndex[p.first]]->getInfo(conf)){
                        cout<<conf.set[Output::system];
                        cout<<(conf.showDetail?"\t" R"(Virtual function "getInfo(Color&) " called. (returned true))""\n":"");
                        cout<<conf.set[Output::none];
                    }else{
                        cout<<conf.set[Output::system];
                        cout<<(conf.showDetail?"\t" R"(Virtual function "getInfo(Color&) " called. (return false) Error?)""\n":"");
                        cout<<conf.set[Output::none];
                    }
                }
            }
            break;
        case Status::OUTPUT:
            cout<<"PREFERENCE";
            cout<<"==============\n";
            cout<<conf.set[Output::none];
            cout<<conf.set[Output::option];
            for(const pair<char,string>&p:cmdPREFERENCE){
                if(valid.count(p.first)){
                    printf("(%c) %s\n",toupper(p.first),p.second.c_str());
                }
            }
            break;
    }
    cout<<conf.set[Output::none];
}
void Dungeon::handleMovement(const Direction&op){
    switch(op){
        case Direction::UP:
            player.changeRoom(player.currentRoom->upRoom);
            break;
        case Direction::DOWN:
            player.changeRoom(player.currentRoom->downRoom);
            break;
        case Direction::LEFT:
            player.changeRoom(player.currentRoom->leftRoom);
            break;
        case Direction::RIGHT:
            player.changeRoom(player.currentRoom->rightRoom);
            break;
        case Direction::BACK:
            player.changeRoom(player.previousRoom);
            break;
    }
}
void Dungeon::handleEvent(const Event&op,Object*o){
    switch(op){
        case Event::showCUR:
            cout<<conf.set[Output::system];
            cout<<(conf.showDetail?"handle Event::showCUR\n":"");
            cout<<conf.set[Output::none];
            this->player.triggerEvent(&player,conf);
            break;
        case Event::goMENU:
            this->status=Status::MENU;
            break;
        case Event::triggerEvent:
            if(o->triggerEvent(&this->player,conf)){
                cout<<conf.set[Output::system];
                cout<<(conf.showDetail?"TriggerEvent return true\n":"");
                cout<<conf.set[Output::none];
                this->player.currentRoom->popObject(o);
            }
            break;
    }
}
void Dungeon::handleMENU(const Menu&op){
    switch(op){
        case Menu::goGAME:
            this->status=Status::GAMING;
            break;
        case Menu::goOPTIONS:
            this->status=Status::OPTIONS;
            break;
        case Menu::SAVE:
            Record::saveToFile(&player,rooms,conf);
            break;
        case Menu::LOAD:
            Record::loadFromFile(&player,rooms,"record.rec",conf);
            break;
        case Menu::QUIT:
            exit(0);
    }
}
void Dungeon::handleOPTIONS(const Options&op){
    switch(op){
        case Options::CONFIG:
            this->config();
            break;
        case Options::goMENU:
            this->status=Status::MENU;
            break;
        case Options::goOUTPUT:
            this->status=Status::OUTPUT;
            break;
    }
}
void Dungeon::handleOUTPUT(const Output&op){
    switch(op){
        case Output::system:
            conf.change(Output::system);
            break;
        case Output::bar:
            conf.change(Output::bar);
            break;
        case Output::alert:
            conf.change(Output::alert);
            break;
        case Output::interaction:
            conf.change(Output::interaction);
            break;
        case Output::option:
            conf.change(Output::option);
            break;
        case Output::name:
            conf.change(Output::name);
            break;
        case Output::none:
            conf.init();//or only set default
            break;
        case Output::goOPTIONS:
            this->status=Status::OPTIONS;
            break;
    }
}
