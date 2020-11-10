#include "../include/Agent.h"

Agent::Agent() {};

ContactTracer::ContactTracer() {};

Virus::Virus(int nodeInd) : nodeInd(nodeInd){
    //
};

void Virus::act(Session &session) {
    int v = session.getGraph().getNonInfectedNeighbor(nodeInd);
    session.enqueueInfected(v);
    session.getGraph().infectNode(v);
};

void ContactTracer::act(Session &session) {
    int i = session.dequeueInfected();
    MaxRankTree* maxRank = new MaxRankTree(i);
    maxRank->bfs(session);
    int biggest = maxRank->returnBiggest();
    for (int j=0; i<session.getGraph().getSize() ; j++) {
        session.getGraph().getMatrix()[biggest][j] = 0;
        session.getGraph().getMatrix()[j][biggest] = 0;
    }
};