#include "Color.h"

void Color::listAll(){
    cout<<"\033[0m"<<"reset\n";
    cout<<"\033[30m"<<"black\n";
    cout<<"\033[31m"<<"red\n";
    cout<<"\033[32m"<<"green\n";
    cout<<"\033[33m"<<"yellow\n";
    cout<<"\033[34m"<<"blue\n";
    cout<<"\033[35m"<<"magenta\n";
    cout<<"\033[36m"<<"cyan\n";
    cout<<"\033[37m"<<"white\n";
    cout<<"\033[1m\033[30m"<<"bold black\n";
    cout<<"\033[1m\033[31m"<<"bold red\n";
    cout<<"\033[1m\033[32m"<<"bold green\n";
    cout<<"\033[1m\033[33m"<<"bold yellow\n";
    cout<<"\033[1m\033[34m"<<"bold blue\n";
    cout<<"\033[1m\033[35m"<<"bold magenta\n";
    cout<<"\033[1m\033[36m"<<"bold cyan\n";
    cout<<"\033[1m\033[37m"<<"bold white\n";
}
void Color::init(){
    linux_gcc["RESET"]="\033[0m";
    linux_gcc["BLACK"]="\033[30m";
    linux_gcc["RED"]="\033[31m";
    linux_gcc["GREEN"]="\033[32m";
    linux_gcc["YELLOW"]="\033[33m";
    linux_gcc["BLUE"]="\033[34m";
    linux_gcc["MAGENTA"]="\033[35m";
    linux_gcc["CYAN"]="\033[36m";
    linux_gcc["WHITE"]="\033[37m";
    linux_gcc["BOLD BLACK"]="\033[1m\033[30m";
    linux_gcc["BOLD RED"]="\033[1m\033[31m";
    linux_gcc["BOLD GREEN"]="\033[1m\033[32m";
    linux_gcc["BOLD YELLOW"]="\033[1m\033[33m";
    linux_gcc["BOLD BLUE"]="\033[1m\033[34m";
    linux_gcc["BOLD MAGENTA"]="\033[1m\033[35m";
    linux_gcc["BOLD CYAN"]="\033[1m\033[36m";
    linux_gcc["BOLD WHITE"]="\033[1m\033[37m";
    this->listAll();
    cout<<linux_gcc["RESET"];
    cout<<"Can you see these colors? [Y/n] ";
    string input;
    while(getline(cin,input)){
        transform(input.begin(),input.end(),input.begin(),[](char c){
              return tolower(c);
        });
        unordered_set<string> valid{"yes","y","no","n"};
        if(valid.count(input)){
            cout<<"Valid! It is a valid input.\n";
            break;
        }else{
            cout<<"Invalid! It is an invalid input.\n";
        }
        cout<<R"(Please input "yes" or "no" )""\n";
        cout<<"Can you see this colors? [Y/n] ";
    }
    unordered_map<string,bool> mean{{"yes",false},
                                    {"y",  false},
                                    {"no", true},
                                    {"n",  true}};
    this->mingw=mean[input];
    if(this->mingw){
        linux_gcc.clear();
    }
    colors=linux_gcc;
    this->setDefault();
}
void Color::setDefault(){
    set[Output::system]=linux_gcc["WHITE"];
    set[Output::bar]=linux_gcc["CYAN"];
    set[Output::alert]=linux_gcc["RED"];
    set[Output::interaction]=linux_gcc["BLUE"];
    set[Output::option]=linux_gcc["MAGENTA"];
    set[Output::name]=linux_gcc["GREEN"];
    set[Output::none]=linux_gcc["RESET"];
    cout<<set[Output::system]<<"Set all color settings to default."<<endl;
}
void Color::change(const Output&op){
    cout<<set[Output::interaction]<<"Choose one color by the following list\n"<<set[Output::none];
    listAll();
    string input;
    while(getline(cin,input)){
        transform(input.begin(),input.end(),input.begin(),[](char c){
              return toupper(c);
        });
        if(linux_gcc.count(input)){
            cout<<set[Output::system]<<(this->showDetail?"Legal color chose\n":"")<<set[Output::none];
            break;
        }
        cout<<set[Output::system]<<(this->showDetail?"Illegal color chose\n":"")<<set[Output::none];
        cout<<set[Output::alert]<<"Your input need to be chose in the following list\n"<<set[Output::none];
        listAll();
    }
    set[op]=linux_gcc[input];
}
