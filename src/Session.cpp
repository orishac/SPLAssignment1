#include "Session.h"
#include <fstream>
#include "json.hpp"
#include <vector>
#include "Agent.h"
#include "Graph.h"

using json = nlohmann:: json;
using namespace std;


Session::Session(const std::string &path) : g({}), treeType(), agents({}), infected({}), IsInfected(g.getSize(), false) {
    ifstream i(path);
    nlohmann::json j;
    i >> j;
    g = Graph(j["graph"]);
    if(j["tree"]== "M") {
        treeType = MaxRank;
    }
    if(j["tree"]== "R") {
        treeType = Root;
    }
    if(j["tree"]== "C") {
        treeType = Cycle;
    }
    for (pair <string, int> dec : j["agents"]) {
        if (dec.first == "V")
            agents.push_back(new Virus(dec.second));
        else
            agents.push_back(new ContactTracer());
    }

    IsInfected.assign(g.getSize(), false);


};

void Session::simulate() {
    for (auto &elem:agents) {
        elem->act(*this);
    }
    while(!infectionCheck()) {
        for (auto &elem:agents) {
            elem->act(*this);
        }
    }
    json output;
    output["graph"]=g.getMatrix();
    output["infected"]=infected;
    ofstream i("../bin/output.json");
    i << output;

};
void Session::addAgent(const Agent &agent) {
    Agent* cloneAgent = agent.clone();
    agents.push_back(cloneAgent);
};

void Session::setGraph(const Graph& graph) {
    g = graph;
};

void Session::enqueueInfected(int a) {
    infected.push_back(a);
    IsInfected[a]=true;
};

int Session::dequeueInfected() {
    int i = infected.back();
    infected.front();
    infected.erase(infected.begin());
    return i;
};

TreeType Session::getTreeType() const {
    return treeType;
};

Graph& Session::getGraph() {
    return g;
};

std::vector<int> Session::getInfected() {
    return infected;
}

void Session::clear() {
    for (auto &agent : agents) {
        if (agent != nullptr)
            delete (agent);
    }
    agents.clear();
    g.clear();
    infected.clear();
    IsInfected.clear();

}

void Session::copy(const Graph other_g, const TreeType other_treeType, const std::vector<Agent *> other_agents,
                   const std::vector<int> other_infected, const std::vector<bool> other_IsInfected) {
    g = other_g;
    treeType = other_treeType;
    agents = other_agents;
    infected = other_infected;
    IsInfected = other_IsInfected;
}

 Session::~Session() { // destructor
    for (auto &agent : agents) {
        if (agent != nullptr)
            delete (agent);
    }
    agents.clear();
    g.clear();
    infected.clear();
    IsInfected.clear();
};

 Session::Session(const Session &aSession, Graph g) : g({}), treeType(), agents({}), infected({}), IsInfected({}) { //copy constructor
     copy(aSession.g, aSession.treeType, aSession.agents,aSession.infected, aSession.IsInfected);
 };

 Session & Session::operator=(const Session &session) { //copy assignment operator
     if (this != &session) {
         clear();
         copy(session.g, session.treeType, session.agents,session.infected, session.IsInfected);
     }
     return *this;
 };

 Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(other.agents),
 infected(other.infected), IsInfected(other.IsInfected) { //move constructor
     other.g.clear();
     other.agents = {};
     other.infected = {} ;
     other.IsInfected = {};
 }

 Session & Session::operator=(Session &&other) { //move assignment operator
     if (this != &other) {
         clear();
         g = other.g;
         agents = other.agents;
         infected = other.infected;
         IsInfected = other.IsInfected;
         other.g.clear();
         other.agents = {};
         other.infected = {};
         other.IsInfected = {};
     }
     return *this;
 }

bool Session::infectionCheck() {
    for (unsigned int i=0; i<g.getMatrix().size(); i++) {
        for(unsigned int j=0; j<g.getMatrix()[i].size(); j++)
            if (g.getMatrix()[i][j]==1) {
                if (g.isInfected(i)) {
                    if (!g.isInfected(j)) {
                        return false;
                    }
                }
            }
    }
    return true;
}
