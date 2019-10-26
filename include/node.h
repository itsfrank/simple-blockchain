#ifndef SBCH_NODE_H
#define SBCH_NODE_H

#include <string>
#include <ctime>

#include "sha256.h"

#include "block.h"
#include "network.h"

class Network;

struct BlockWrapper {
    Block *block;
    BlockWrapper* nextBlock;
};

class Node {
    private:
        std::string name;

        int difficulty;

        BlockWrapper* root = NULL;
        BlockWrapper* tail = NULL;

        Block* workingBlock = NULL;
        int workingNonce;

        Network* network;

    public:
        Node(std::string name) : name(name) {};
        
        bool addBlock(Block *block);
        bool validateChain(BlockWrapper* root);
        void generateBlock(std::string data);
        Block* attemptSolveBlock();

        void setNetwork(Network *network);
        void setDifficulty(int difficulty);

        void handleBroadcast(Block *block);

        std::string getName();
        void printChain();
};

#endif