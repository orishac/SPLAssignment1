#include "Agent.h"

Agent::Agent() {};

ContactTracer::ContactTracer() {};

Virus::Virus(int nodeInd) : nodeInd(nodeInd){
};

void Virus::act(Session &session) {
    if (!session.getGraph().isInfected(session.getGraph().getOneNeighbor(nodeInd))) {
        session.enqueueInfected(session.getGraph().getOneNeighbor(nodeInd));
    }
}

void ContactTracer::act(Session &session) {
    session.dequeueInfected();
}