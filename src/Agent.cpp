
#include "Agent.h"
#include "Session.h"
#include "Tree.h"

Agent::Agent() {};

ContactTracer::ContactTracer() {};

Virus::Virus(int _nodeInd) : nodeInd(_nodeInd){
};

void Virus::act(Session &session) {
    if (!session.getGraph().isInfected(nodeInd)) {
        session.enqueueInfected(nodeInd);
        session.getGraph().infectNode(nodeInd);
    }
    int v = session.getGraph().getNonInfectedNeighbor(nodeInd);
    Virus* newV = new Virus(v);
    session.addAgent(*newV);
    delete newV;
};

void ContactTracer::act(Session &session) {
    int i = session.dequeueInfected();
    MaxRankTree* maxRank = new MaxRankTree(0, i);
    maxRank->bfs(session);
    int biggest = maxRank->traceTree();
    for (int j=0; j<session.getGraph().getSize() ; j++) {
        session.getGraph().getMatrix()[biggest][j] = 0;
        session.getGraph().getMatrix()[j][biggest] = 0;
    }
    delete maxRank;
};

Agent * Virus::clone() const {
    return new Virus(*this);
};

Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
};

Agent::~Agent() {};

Agent * Agent::clone() const {};

void Agent::act(Session &session) {};



