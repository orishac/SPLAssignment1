#ifndef SESSION_H_
#define SESSION_H_

#include <string>
#include "Graph.h"
#include "Tree.h"
#include "Agent.h"
#include <queue>

class Agent;

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

    virtual ~Session();
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infected;
    std::vector<bool> IsInfected;
};

#endif
