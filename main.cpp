#include <iostream>
#include "CSVReader.h"
#include "DecisionTree.h"

int main() {
    CSVReader csvReader = CSVReader();
    auto data = csvReader.readAs2dArray("/home/karl/Data/Technikum/SEM4/MLE/DecisionTree/Datasets/spam_char.csv", ',');

    DecisionTree dt = DecisionTree();

    dt.build(data);

    dt.print();

    // For each column:
    // Make frequency table:
    return 0;
}