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
    ifstream i("config1.json");
    json j;
    j << i;
    cout << j["graph"] << endl;
    return 0;
    /*
    Session sess(argv[1]);
    sess.simulate();
    return 0;
     */
}
