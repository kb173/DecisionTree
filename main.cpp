#include <iostream>
#include "CSVReader.h"

int main() {
    CSVReader csvReader = CSVReader();
    auto data = csvReader.readAs2dArray("/home/karl/Data/Technikum/SEM4/MLE/DecisionTree/Datasets/spam_char.csv", ',');

    std::cout << data[1][0] << std::endl;

    // For each column:
    // Make frequency table:
    return 0;
}