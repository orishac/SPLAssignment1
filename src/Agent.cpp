#include "../include/Agent.h"

Agent::Agent() {};

ContactTracer::ContactTracer() {};

Virus::Virus(int nodeInd) : nodeInd(nodeInd){
};

void Virus::act(Session &session) {


};

void ContactTracer::act(Session &session) {
    int i = session.dequeueInfected();


};