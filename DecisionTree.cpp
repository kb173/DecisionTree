#include <utility>

#include <utility>
#include <iostream>

//
// Created by karl on 05.05.19.
//

#include "DecisionTree.h"
#include "FrequencyTable.h"

void DecisionTreeNode::addNode(const std::string& attributeVal, std::shared_ptr<DecisionTreeNode> next) {
    nextNodes[attributeVal] = std::move(next);
}

const std::map<std::string, std::shared_ptr<DecisionTreeNode>> &DecisionTreeNode::getNextNodes() const {
    return nextNodes;
}

const std::string &DecisionTreeNode::getAttribute() const {
    return attribute;
}

void DecisionTree::build(std::vector<std::vector<std::string>> data) {
    std::cout << "Building decision tree..." << std::endl;

    root = buildRec(std::move(data));
}

void DecisionTree::print() {
    printRec(root, 0);
}

void DecisionTree::printRec(std::shared_ptr<DecisionTreeNode> currentNode, int depth) {
    if (currentNode == nullptr) {
        return;
    }

    auto nodes = currentNode->getNextNodes();

    for (int i = 0; i < depth; i++) {
        std::cout << "\t";
    }
    std::cout << "Attribute: " << currentNode->getAttribute() << std::endl;

    for (auto nextNode : nodes) {
        for (int i = 0; i < depth; i++) {
            std::cout << "\t";
        }
        std::cout << "-> " << nextNode.first << std::endl;

        printRec(nextNode.second, ++depth);
    }
}

std::shared_ptr<DecisionTreeNode> DecisionTree::buildRec(std::vector<std::vector<std::string>> data) {
    // Pure decision?
    std::string firstOutcome = data[1].back();
    bool pure = true;

    for (int i = 1; i < data.size(); i++) {
        if (data[i].back() != firstOutcome) {
            pure = false;
            break;
        }
    }

    if (pure) {
        // Make leaf node here
        return nullptr;
    }

    // No more attributes?
    if (data[0].size() == 1) { // Only the 'Play' column left
        return nullptr;
    }



    int colNumber = data.front().size();

    // Check where the gain would be the highest
    double highestGain = -1000; // TODO: Initialize properly
    int colWithHighestGain = 0;
    FrequencyTable frequencyTableWithHighestGain = FrequencyTable(data, 0, "yes"); // TODO: Ugly

    for (int col = 0; col < colNumber - 1; col++) {
        FrequencyTable ft = FrequencyTable(data, col, "yes");
        double gain = ft.getGain();

        if (gain > highestGain) {
            highestGain = gain;
            colWithHighestGain = col;
            frequencyTableWithHighestGain = ft;
        }
    }

    // Build this node using that information
    DecisionTreeNode newNode = DecisionTreeNode(data.front()[colWithHighestGain]);
    std::shared_ptr<DecisionTreeNode> currentNode = std::make_shared<DecisionTreeNode>(newNode);

    for (const auto &attribute : frequencyTableWithHighestGain.getAttributes()) {
        // Delete rows with this attribute from a copy of the table
        std::vector<std::vector<std::string>> new_data;
        std::vector<std::string> firstLine = data[0];
        firstLine.erase(firstLine.begin() + colWithHighestGain);

        new_data.push_back(firstLine);

        for (int i = 1; i < data.size(); i++) {
            if (data[i][colWithHighestGain] == attribute) {
                std::vector<std::string> line = data[i];
                line.erase(line.begin() + colWithHighestGain);

                new_data.push_back(line);
            }
        }

        currentNode->addNode(attribute, buildRec(new_data));
    }

    return currentNode;
}
