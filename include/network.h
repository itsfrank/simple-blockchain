#ifndef SBCH_NETWORK_H
#define SBCH_NETWORK_H

#include <string>
#include <ctime>
#include <vector>
#include <iostream>

#include "sha256.h"

#include "block.h"
#include "node.h"

class Node;

class Network {
    private:
        std::vector<Node*> nodes;
    public:
        void registerNode(Node *node);
        void broadcast(Node *sourceNode, Block *block);
};

#endif