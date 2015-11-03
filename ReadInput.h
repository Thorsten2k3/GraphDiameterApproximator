#ifndef READINPUT_H_
#define READINPUT_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdexcept>
#include <cassert>
#include <tuple>

//typedef uint64_t index;
//typedef index node;

typedef uint64_t count;
typedef count node;

class ReadInput {

protected:

    std::ifstream graphFile;

public:

    ReadInput(std::string path);

    virtual ~ReadInput() = default;
       
    std::tuple<count, count, count> getHeader();

    bool hasNext();

    std::vector<node> getNext();

};

#endif // _READINPUT_H_
