#include <iostream>
#include "CSVReader.h"
#include "DecisionTree.h"

int main() {
    CSVReader csvReader = CSVReader();
    auto data = csvReader.readAs2dArray("/home/karl/Data/Technikum/SEM4/MLE/DecisionTree/Datasets/spam_char.csv", ',');

    DecisionTree dt = DecisionTree();

    dt.build(data);

    dt.print();

    // Check accuracy
    auto attrNames = data.front();
    data.erase(data.begin() + 0);

    int truePos = 0;
    int falsePos = 0;
    int trueNeg = 0;
    int falseNeg = 0;

    for (auto line : data) {
        std::map<std::string, std::string> entry;

        for (int i = 0; i < line.size() - 1; i++) {
            entry[attrNames[i]] = line[i];
        }

        if (dt.classify(entry) == "yes") {
            if (line.back() == "yes") {
                truePos += 1;
            } else {
                falsePos += 1;
            }
        } else {
            if (line.back() == "yes") {
                falseNeg += 1;
            } else {
                trueNeg += 1;
            }
        }
    }

    std::cout << "True positives: " << truePos << std::endl;
    std::cout << "True negatives: " << trueNeg << std::endl;
    std::cout << "False positives: " << falsePos << std::endl;
    std::cout << "False negatives: " << falseNeg << std::endl;

    double accuracy = double(truePos + trueNeg) / (truePos + trueNeg + falsePos + falseNeg);

    std::cout << "Accuracy: " << accuracy << std::endl;

    return 0;
}