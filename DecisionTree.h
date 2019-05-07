#include <utility>

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
    DecisionTreeNode(std::string _attribute) : attribute(std::move(_attribute)) {};

    void addNode(const std::string& attributeVal, std::shared_ptr<DecisionTreeNode> next);

private:
    std::map<std::string, std::shared_ptr<DecisionTreeNode>> nextNodes;
public:
    const std::map<std::string, std::shared_ptr<DecisionTreeNode>> &getNextNodes() const;

private:

    std::string attribute;
public:
    const std::string &getAttribute() const;
};


class DecisionTree {
public:
    DecisionTree() = default;

    void build(std::vector<std::vector<std::string>> data);

    void print();

private:
    std::shared_ptr<DecisionTreeNode> root;

    std::shared_ptr<DecisionTreeNode> buildRec(std::vector<std::vector<std::string>> data);

    void printRec(std::shared_ptr<DecisionTreeNode> currentNode, int depth);
};


#endif //DECISIONTREE_DECISIONTREE_H
