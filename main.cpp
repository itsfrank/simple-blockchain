#include <string>
#include <vector>
#include <iostream>

#include "block.h"
#include "node.h"
#include "network.h"

int main(int argc, char const *argv[]) {
    const std::string ZERO_256H = "0000000000000000000000000000000000000000000000000000000000000000";

    int animalIdx = 0;
    const std::vector<std::string> animalVec = {
        "Beaver",
        "Moose",
        "Raccoon",
        "Wolf",
        "Bear"
    };

    int companiesIdx = 0;
    const std::vector<std::string> companiesVec = {
        "Google",
        "Apple",
        "Microsoft",
        "Qualcomm",
        "Intel"
    };

    int citiesIdx = 0;
    const std::vector<std::string> citiesVec = {
        "Montreal",
        "Quebec",
        "Toronto",
        "Chicago",
        "Washington"
    };

    int difficulty = 2;

    Block* genesisBlock = new Block(ZERO_256H, "nil");

    Node* animalNode = new Node("Animal Node");
    Node* companiesNode = new Node("Companies Node");
    Node* citiesNode = new Node("Cities Node");

    Network network;
    network.registerNode(animalNode);
    network.registerNode(companiesNode);
    network.registerNode(citiesNode);

    animalNode->setDifficulty(difficulty);
    companiesNode->setDifficulty(difficulty);
    citiesNode->setDifficulty(difficulty);

    network.broadcast(NULL, genesisBlock);

    bool animalsDone = false;
    bool companiesDone = false;
    bool citiesDone = false;
    while (!(animalsDone && companiesDone && citiesDone)) {
        if (animalIdx < animalVec.size()) {
            animalNode->generateBlock(animalVec[animalIdx]);
            Block* newBlock = animalNode->attemptSolveBlock();
            if (newBlock != NULL) {
                animalIdx++;
                network.broadcast(animalNode, newBlock);
            }
        } else {
            animalsDone = true;
        }

        if (companiesIdx < companiesVec.size()) {
            companiesNode->generateBlock(companiesVec[companiesIdx]);
            Block* newBlock = companiesNode->attemptSolveBlock();
            if (newBlock != NULL) {
                companiesIdx++;
                network.broadcast(companiesNode, newBlock);
            }
        } else {
            companiesDone = true;
        }

        if (citiesIdx < citiesVec.size()) {
            citiesNode->generateBlock(citiesVec[citiesIdx]);
            Block* newBlock = citiesNode->attemptSolveBlock();
            if (newBlock != NULL) {
                citiesIdx++;
                network.broadcast(citiesNode, newBlock);
            }
        } else {
            citiesDone = true;
        }
    }

    std::cout << std::endl;
    animalNode->printChain();
    std::cout << std::endl;
    companiesNode->printChain();
    std::cout << std::endl;
    citiesNode->printChain();
    return 0;
}
