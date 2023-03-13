#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "movie_id_finder.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> <file3> <name>" << std::endl;
        return 1;
    }
    GetID(argv[1], argv[2]);
    return 0;
}
