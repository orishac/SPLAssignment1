
#include "Agent.h"

Agent::Agent() {};

ContactTracer::ContactTracer() {};

Virus::Virus(int _nodeInd) : nodeInd(_nodeInd){
};

void Virus::act(Session &session) {
    if (!session.getGraph().isInfected(nodeInd))
        session.enqueueInfected(nodeInd);
    int v = session.getGraph().getNonInfectedNeighbor(nodeInd);
    Virus* newV = new Virus(v);
    session.addAgent(*newV);
};

void ContactTracer::act(Session &session) {
    int i = session.dequeueInfected();
    MaxRankTree* maxRank = new MaxRankTree(i);
    maxRank->bfs(session);
    int biggest = maxRank->traceTree();
    for (int j=0; i<session.getGraph().getSize() ; j++) {
        session.getGraph().getMatrix()[biggest][j] = 0;
        session.getGraph().getMatrix()[j][biggest] = 0;
    }
};

Agent * Virus::clone() const {
    return new Virus(*this);
};

Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
};
