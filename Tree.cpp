#include "Tree.h"
#include <iostream>
#include <vector>


Tree::Tree(int rootLabel) : Tree(new std::vector<Tree*>){
        node = rootLabel;
};

void Tree::addChild(const Tree &child) {
    children.push_back(child);
};


static Tree* createTree(const Session& session, int rootLabel) {

}
virtual int traceTree()=0 {

}