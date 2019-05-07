#include <fstream>
#include <sstream>
#include "CSVReader.h"

std::vector<std::vector<std::string>> CSVReader::readAs2dArray(const std::string &filepath, const char &separator) {
    auto data = std::vector<std::vector<std::string>>();
    std::ifstream file(filepath);
    std::string line;

    while (getline(file, line)) {
        std::vector<std::string> row;

        std::stringstream iss(line);
        std::string val;

        while (getline(iss, val, separator)) {
            row.push_back(val);
        }

        data.push_back(row);
    }

    return data;
}
