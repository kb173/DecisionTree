#ifndef KNN_CSVREADER_H
#define KNN_CSVREADER_H


#include <vector>
#include <list>

class CSVReader {

public:
    std::vector<std::vector<std::string>> readAs2dArray(const std::string &, const char &);

};


#endif //KNN_CSVREADER_H
