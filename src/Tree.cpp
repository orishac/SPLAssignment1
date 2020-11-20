#include "Tree.h"
#include "Session.h"
#include <vector>
#include <queue>


Tree::Tree(int rootLabel) : node(), children(){
    node = rootLabel;
};


void Tree::addChild(const Tree &child) {
    bool added = false;
    if (childrenSize() == 0) {
        Tree *copyChild = child.clone();
        children.push_back(copyChild);
        added = true;
    }
    for (unsigned int i = 0; !added & i < children.size(); i++) {
        if (child.node < children[i]->node) {
            Tree *temp = children[i];
            Tree *copyChild = child.clone();
            for (unsigned int j = i; j <= childrenSize(); j++) {
                children[j] = copyChild;
                copyChild = temp;
                if (j != childrenSize()) {
                    temp = children[j + 1];
                }
            }
            added = true;
        } else if (!added & (i < childrenSize() - 1)) {
            if (child.node > children[i]->node & child.node < children[i + 1]->node & !added) {
                Tree *temp = children[i + 1];
                Tree *copyChild = child.clone();
                for (unsigned int j = i + 1; !added & j < childrenSize(); j++) {
                    children[j] = copyChild;
                    copyChild = temp;
                    if (j != childrenSize()) {
                        temp = children[j + 1];
                    }
                }
                added =true;
            }
        }
    }
    if (!added) {
        Tree *copyChild = child.clone();
        children.push_back(copyChild);
        added = true;
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
    visited[this->node]=true;
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
                Tree* realChild = currNode->getSameChild(a->node);
                nextNode.push(realChild);
                visited[i] = true;
            }
        }
    }
    while (!nextNode.empty())
        nextNode.pop();

};

int Tree::childrenSize() {
    return children.size();
}

int Tree::getRoot() {
    return node;
};

Tree*  Tree::getSameChild(int nodeInd) {
    for (Tree* child: children)
        if (child->node==nodeInd)
            return child;
}

int MaxRankTree::traceNeighbor() {
    int ret;
    for (int i=0; i<childrenSize(); i++) {
        if (getChildren(i)->childrenSize() > ret) {
            ret = getChildren(i)->getRoot();
        }
    }
    return ret;
}

Tree * Tree::getChildren(int nodeInd) {
    return children[nodeInd];
};

Tree * CycleTree::clone() const {
    return new CycleTree(*this);
};
Tree * RootTree::clone() const {
    return new RootTree(*this);
};
Tree * MaxRankTree::clone() const {
    return new MaxRankTree(*this);
};
int MaxRankTree::traceTree() {
    int ret = this->getRoot();
    Tree* treeRet = this;
    std::vector<Tree*> allChilds;
    allChilds.push_back(this);
    this->fillMaxRankVector(allChilds);
    for (Tree * child : allChilds) {
        if (child->childrenSize() > treeRet->childrenSize()) {
            treeRet = child;
            ret = child->getRoot();
        }
    }
    return ret;
};

void Tree::fillMaxRankVector(std::vector<Tree*> vector) {
    if (childrenSize()>0) {
        for (Tree *child : children) {
            vector.push_back(child);
            child->fillMaxRankVector(vector);
        }
    }
}

int RootTree::traceTree() {
    return getRoot();
};

int CycleTree::traceTree() {
    if (getChildren(0)!=nullptr)
        return getChildren(0)->traceTree();
    else
        return getRoot();
};

void Tree::clear() {
    for (Tree* child:children) {
        delete child;
    }
    children.clear();
}

void Tree::copy(const int other_node, const std::vector<Tree *> other_children) {
    node = other_node;
    children = other_children;
}

Tree::~Tree() { //destructor
    clear();
}

Tree::Tree(const Tree &aTree) : node(aTree.node), children(){ //copy constructor
    copy(aTree.node, aTree.children);
}

Tree & Tree::operator=(const Tree &tree) { //copy assignment operator
    if (this != &tree) {
        clear();
        copy(tree.node, tree.children);
    }
    return *this;
}

Tree::Tree(Tree &&other) :node(other.node), children(other.children) { //move constructor
    other.node = 0;
    other.children.clear();
}

Tree & Tree::operator=(Tree &&other) { //move assignment operator
    if (this != &other) {
        clear();
        node = other.node;
        children = other.children;
        other.node = 0;
        other.children.clear();
    }

    return *this;
}

void Tree::setRoot(int otherNode) {
    node = otherNode;
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle){
    setRoot(rootLabel);
    currCycle = currCycle;
}

MaxRankTree::MaxRankTree(int rootLabel) :Tree(rootLabel)  {
    setRoot(rootLabel);
}

RootTree::RootTree(int rootLabel) :Tree(rootLabel) {
    setRoot(rootLabel);
}