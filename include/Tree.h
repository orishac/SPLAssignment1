#ifndef TREE_H_
#define TREE_H_


#include <vector>

class Session;
class Graph;
class Agent;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    void bfs(Session& session);
    int getRoot();
    Tree* getChildren(int nodeInd);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    int childrenSize();

    Tree (const Tree &aTree); //copy constructor
    virtual ~Tree(); //destructor
    Tree &operator=(const Tree &tree); //copy assignment operator

private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif
