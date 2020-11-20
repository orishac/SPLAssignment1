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
    void clear();
    void copy (const int node, const std::vector<Tree*> children);
    virtual Tree *clone() const =0;
    void setRoot(int otherNode);
    Tree* getSameChild(int nodeInd);
    void fillMaxRankVector(std::vector<Tree*> vector);

    virtual ~Tree(); //destructor
    Tree (const Tree &aTree); //copy constructor
    Tree &operator=(const Tree &tree); //copy assignment operator
    Tree (Tree &&other); //move constructor
    Tree& operator=(Tree &&other); //move assignment operator

private:
    int node;
    std::vector<Tree*> children;


};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree *clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree *clone() const;
    int traceNeighbor();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree *clone() const;
};

#endif
