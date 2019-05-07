//
// Created by karl on 05.05.19.
//

#include <numeric>
#include "FrequencyTable.h"
#include "EntropyCalculator.h"
#include<map>


FrequencyTable::FrequencyTable(const std::vector<std::vector<std::string>> &data, int column,
                               const std::string& positiveResultName) {

    for (const auto& line : data) {
        std::string attributeVal = line[column];
        std::string resultVal = line.back();

        bool outcome = false;
        if (resultVal == positiveResultName) {
            outcome = true;
        }

        attributeFrequencies[attributeVal][outcome] += 1;
    }
}

double FrequencyTable::getGain() {
    EntropyCalculator ec = EntropyCalculator();

    double gain = 0;

    for (const auto& attribute : attributeFrequencies) {
        std::string attributeName = attribute.first;
        std::map<bool, int> countAtOutcome = attribute.second;

        std::vector line = std::vector({countAtOutcome[true], countAtOutcome[false]});

        // Total number of occurrences of this attribute in data
        int sum = std::accumulate(line.begin(), line.end(), 0);

        // Here, the actual formula is applied
        gain -= (double(sum) / attributeCount) * ec.getEntroy(line, sum);
    }

    return gain;
}

std::list<std::string> FrequencyTable::getAttributes() {
    auto attributes = std::list<std::string>();

    for (const auto& attribute : attributeFrequencies) {
        attributes.push_back(attribute.first);
    }

    return attributes;
}
