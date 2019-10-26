#include "network.h"

void Network::registerNode(Node *node) {
    this->nodes.push_back(node);
    node->setNetwork(this);
}

void Network::broadcast(Node *sourceNode, Block *block) {
    if (sourceNode != NULL) std::cout << "Node: " << sourceNode->getName() << " attempting to add block" << std::endl;
    block->print();

    for (Node *node : this->nodes) {
        node->handleBroadcast(block);
    }
}