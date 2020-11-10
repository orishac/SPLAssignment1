#include "Tree.h"
#include <iostream>
#include <vector>


Tree::Tree(int rootLabel) : Tree(new std::vector<Tree*>){
        node = rootLabel;
};

void Tree::addChild(const Tree &child) {
    for (int i=0; i<children.size(); i++) {
        if (child.node<children[i]->node) {
            Tree* temp = children[i];
            children[i]

        }
    }
};


static Tree* createTree(const Session& session, int rootLabel) {

}
virtual int traceTree()=0 {

}