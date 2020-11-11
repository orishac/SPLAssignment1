#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();
    virtual Agent* clone();
    virtual void act(Session& session)=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual Agent* clone();
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual Agent* clone();
    virtual void act(Session& session);
    Virus (const Virus &otherVirus); //copy constructor
private:
    const int nodeInd;
};

#endif
