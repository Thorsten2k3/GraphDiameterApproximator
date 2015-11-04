#include "../include/ReadInput.h"

static std::vector<node> parseLine(const std::string& line) {
    std::stringstream stream(line);
    std::string token;
    char delim = ' ';
    std::vector<node> adjacencies;

    while (std::getline(stream, token, delim)) {
        if (token.size() != 0) {
            node v = stoi(token);
            adjacencies.push_back(v);
        }
    }

    return adjacencies;
}

ReadInput::ReadInput(std::string path) : graphFile(path) {
    if( ! (this->graphFile) ) {  // TODO: try??
        throw std::runtime_error("invalid graph file");
    } 
}

bool ReadInput::hasNext() {
    return this->graphFile.good();
}

std::tuple<count, count, count> ReadInput::getHeader() {
    count n, m, weighted;

    std::string line = "";
    assert (this->graphFile);

    if (std::getline(this->graphFile, line)) {
        while (line[0] == '%') {
            std::getline(this->graphFile, line);
        }

        std::vector<node> tokens = parseLine(line);
        n = tokens[0];
        m = tokens[1];
        if (tokens.size() == 2) {
            return std::tuple<count, count, count>(n,m,0);
        }
        if (tokens.size() == 3) {
            if( tokens[2] < 2 ) {
                weighted = tokens[2];
            } else {
                throw std::runtime_error("nodes are weighted");
                return std::tuple<count, count, count>(0,0,0);
            }
        }
        return std::tuple<count, count, count>(n,m,weighted);
    } else {
        throw std::runtime_error("getting METIS file header failed");
        return std::tuple<count, count, count>(0,0,0);
    }
}

std::vector<node> ReadInput::getNext() {

    std::string line;
    bool comment = false;
    do {
        comment = false;
        std::getline(this->graphFile, line);
        if (line[0] == '%') {
            comment = true;
        } else {
            return parseLine(line);
        }

    } while (comment);

    throw std::runtime_error("bad METIS file structure");
    std::vector<node> fail;
    return fail;
}
