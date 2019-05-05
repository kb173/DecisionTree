#include <utility>

//
// Created by karl on 05.05.19.
//

#include "DecisionTree.h"

void DecisionTreeNode::addNode(const std::string& attributeVal, std::shared_ptr<DecisionTreeNode> next) {
    nextNodes[attributeVal] = std::move(next);
}
