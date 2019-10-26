#include "node.h"
#include <iostream>

bool Node::addBlock(Block *block) {
    if (this->root == NULL) { // genesis block
        BlockWrapper* newBlock = new BlockWrapper;
        newBlock->block = block;
        newBlock->nextBlock = NULL;
        this->root = newBlock;
        this->tail = newBlock;
        return true;
    }

    if (block->getPrevHash().compare(this->tail->block->computeHash()) != 0) {
        std::cout << "Previous hash does not match: <" << block->getPrevHash() << "> vs <" << this->tail->block->computeHash() << ">" << std::endl; 
        return false; //can't add block, previous hash does not batch tail block
    }

    std::string blockHash = block->computeHash();
    for (int i = 0; i < this->difficulty; i++) {
        if (blockHash.at(i) != '0') {
            std::cout << "Invalid block hash: <" << blockHash << ">" << std::endl; 
            return false; // block hash is not valid, or does not match difficulty
        }
    }

    // Block is valid
    BlockWrapper* newBlock = new BlockWrapper;
    newBlock->block = block;
    newBlock->nextBlock = NULL;
    
    this->tail->nextBlock = newBlock;
    if (this->validateChain(this->root)) {
        this->tail = newBlock;
    } else {
        this->tail->nextBlock = NULL;
        std::cout << "Chain Invalid" << std::endl; 
        return false;
    }

    return true;
};

bool Node::validateChain(BlockWrapper* root) {
    BlockWrapper* currentBlock = root;

    while (currentBlock->nextBlock != NULL) {
        std::string currentHash = currentBlock->block->computeHash();
        if (currentHash.compare(currentBlock->nextBlock->block->getPrevHash()) != 0) return false;

        currentBlock = currentBlock->nextBlock;
    }

    return true;
};

void Node::generateBlock(std::string data) {
    if (workingBlock != NULL) return;
    Block* block = new Block(this->tail->block->computeHash(), data);
    this->workingBlock = block;
};

Block* Node::attemptSolveBlock() {
    this->workingBlock->setNonce(this->workingNonce);
    std::string blockHash = this->workingBlock->computeHash();
    bool solved = true;
    for (int i = 0; i < this->difficulty; i++) {
        if (blockHash.at(i) != '0') {
            solved = false; // block hash is not valid, or does not match difficulty
            break;
        }
    }
    this->workingNonce++;
    return solved ? this->workingBlock : NULL;
};

void Node::setNetwork(Network *network) {
    this->network = network;
};

void Node::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
};

void Node::handleBroadcast(Block *block) {
    if (this->addBlock(block)) {
        std::cout << "Block <" << block->computeHash() << "> accepted by " << this->name << std::endl;  
        if (this->workingBlock != NULL) delete this->workingBlock;
        this->workingBlock = NULL;
        this->workingNonce = 0;
    } else {
        std::cout << "Block <" << block->computeHash() << "> rejected by " << this->name << std::endl; 
    }
};

std::string Node::getName() {
    return this->name;
}

void Node::printChain() {
    BlockWrapper* currentBlock = root;
    std::cout << "Blockchain at Node: " << this->name << std::endl;

    while (currentBlock->nextBlock != NULL) {
        currentBlock->block->print();
        currentBlock = currentBlock->nextBlock;
    }
}