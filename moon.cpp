#include "moon.h"
using namespace std;

vector<string> split(const string&st){
    vector <string> ret;
    char*str=const_cast<char*>(st.c_str());
    char*pch;
    pch=strtok(str," ");
    while(pch!=nullptr){
        ret.emplace_back(pch);
        pch=strtok(nullptr," ");
    }
    return ret;
}
