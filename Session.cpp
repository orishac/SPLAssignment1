#include "Session.h"
class Agent;

    enum TreeType {
        Cycle,
        MaxRank,
        Root
    };

    class Session {
    public:
        Session(const std::string &path);

        void simulate();

        void addAgent(const Agent &agent) {
            agents.push_back(agent);
        };

        void setGraph(const Graph &graph){
            g = &graph
        };

        void enqueueInfected(int);

        int dequeueInfected();

        TreeType getTreeType() const;

    private:
        Graph g;
        TreeType treeType;
        std::vector<Agent *> agents;
    };