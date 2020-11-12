#include "Tree.h"
#include "Session.h"
#include <vector>
#include <queue>


Tree::Tree(int rootLabel) : node(), children(){
    node = rootLabel;
};


void Tree::addChild(const Tree &child) {
    for (int i=0; i<children.size(); i++) {
        if (child.node<children[i]->node) {
            Tree* temp = children[i];
            children[i];
        }
    }
};


Tree* Tree::createTree(const Session &session, int rootLabel) {
    Tree* retTree;
    if (session.getTreeType()==Cycle) {
        retTree = new CycleTree(rootLabel, session.getTreeType());
    }
    if (session.getTreeType()==MaxRank) {
        retTree = new MaxRankTree(rootLabel);
    }
    if (session.getTreeType()==Root) {
        retTree = new RootTree(rootLabel);
    }

    return retTree;
};


void Tree::bfs(Session &session) {
    std::queue<Tree*> nextNode;
    std::vector<bool> visited(session.getGraph().getSize(), false);
    Graph second = session.getGraph();
    nextNode.push(this);
    Tree* currNode;
    while (!nextNode.empty()) {
        currNode=nextNode.front();
        nextNode.pop();
        for (int i=0; i < second.getSize() ;i++) {
            if (second.getMatrix()[currNode->node][i]==1 && !visited[i]) {
                Tree* a = createTree(session, i);
                currNode->addChild(*a);
                nextNode.push(a);
                visited[i] = true;
            }
        }
    }
};

int Tree::childrenSize() {
    return children.size();
}

int Tree::getRoot() {
    return node;
};

Tree * Tree::getChildren(int nodeInd) {
    return children[nodeInd];
}

int MaxRankTree::traceTree() {
    int ret = childrenSize();
    if (childrenSize() > 0) {
        for (int i = 0; i < childrenSize(); i++) {
            if (getChildren(i)->traceTree() > ret)
                ret = getChildren(i)->traceTree();
        }
    }
    return ret;
};

int RootTree::traceTree() {
    return getRoot();
};

int CycleTree::traceTree() {
    if (getChildren(0)!=nullptr)
        return getChildren(0)->traceTree();
    else
        return getRoot();
};