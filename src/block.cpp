#include "block.h"

Block::Block(std::string prevHash, std::string data) :
    prevHash(prevHash),
    timestamp(time(NULL)),
    data(data)
    {
        this->nonce = 0;
    };

Block::Block(const Block &block) :
    prevHash(block.prevHash),
    timestamp(block.timestamp),
    nonce(block.nonce),
    data(block.data)
    {};

void Block::setNonce(int nonce) {
    this->nonce = nonce;
}

time_t Block::getTimestamp() {
    return this->timestamp;
}

std::string Block::getData() {
    return this->data;
}

std::string Block::getPrevHash() {
    return this->prevHash;
}

std::string Block::computeHash() {
    std::string baseHash = this->computeBaseHash();

    SHA256 sha256;
    sha256.add(baseHash.c_str(), baseHash.length());
    sha256.add(&this->nonce, sizeof(this->nonce));
    
    return sha256.getHash();
}

std::string Block::computeBaseHash() {
    SHA256 sha256;
    
    sha256.add(this->prevHash.c_str(), this->prevHash.length());
    sha256.add(&this->timestamp, sizeof(this->timestamp));
    sha256.add(this->data.c_str(), this->data.length());

    return sha256.getHash();
}

void Block::print() {
    std::cout << "Block <" << this->computeHash() << ">" << std::endl;
    std::cout << "\tTimestamp: " << this->getTimestamp() << std::endl;
    std::cout << "\tData: " << this->getData() << std::endl;
}