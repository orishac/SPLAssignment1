#ifndef SESSION_H_
#define SESSION_H_

#include <string>
#include <queue>
#include "Graph.h"

class Agent;
class Graph;
class Tree;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};


class Session{
public:
    Session(const std::string& path);
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    Graph getGraph();
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    void clear();
    void copy(const Graph g, const TreeType treeType, const std::vector<Agent*> agents,
                 const std::queue<int > infected, const std::vector<bool> IsInfected);
    virtual ~Session(); //destructor
    Session& operator=(const Session &session); //copy assignment operator
    Session(const Session &aSession, Graph g); //copy constructor
    Session(Session &&other); //move constructor
    Session& operator=(Session &&other); //move assignment
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infected;
    std::vector<bool> IsInfected;
};

#endif
