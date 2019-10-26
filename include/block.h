#ifndef SBCH_BLOCK_H
#define SBCH_BLOCK_H

#include <string>
#include <ctime>
#include <iostream>
#include "sha256.h"

class Block {
    private:
        const std::string prevHash; // Hash of previous block
        const time_t timestamp;
        const std::string data;         // Actual data contained in this block
        int nonce;                      // nonce to randomize hash (modify this to search for appropriate number of leading 0s)
    
    public:
        Block(std::string prevHash, std::string data);
        Block(const Block &block);
        void setNonce(int nonce);
        time_t getTimestamp();
        std::string getData();
        std::string getHash();
        std::string getPrevHash();
        std::string computeHash();
        std::string computeBaseHash();
        void print();
};

#endif