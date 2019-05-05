//
// Created by karl on 05.05.19.
//

#ifndef DECISIONTREE_DECISIONTREE_H
#define DECISIONTREE_DECISIONTREE_H


#include <string>
#include <vector>
#include <memory>
#include <map>


// A node for an attribute. Depending on the attribute value, it leads to other nodes.
class DecisionTreeNode {
public:
    DecisionTreeNode() = default;

    void addNode(const std::string& attributeVal, std::shared_ptr<DecisionTreeNode> next);

private:
    std::map<std::string, std::shared_ptr<DecisionTreeNode>> nextNodes;
};


class DecisionTree {
public:
    DecisionTree() = default;

    void build(std::vector<std::vector<std::string>> data);

    std::string toString();

private:
    std::shared_ptr<DecisionTreeNode> root;

    void buildRec(std::vector<std::vector<std::string>> data, std::shared_ptr<DecisionTreeNode> currentNode);
};


#endif //DECISIONTREE_DECISIONTREE_H
