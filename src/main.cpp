#include <iostream>
#include "Session.h"
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    ifstream i("../bin/config1.json");
    json j;
    i >> j;
    cout << j["graph"] << endl;
    Session sess(argv[1]);
    sess.simulate();
    return 0;
};
