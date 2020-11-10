#include "../include/Tree.h"
#include <iostream>
#include <vector>
#include <queue>
#include "../include/Session.h"



Tree::Tree(int rootLabel) : node(rootLabel){
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


Tree * Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    Tree* root;
    Graph cuurG = session.
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