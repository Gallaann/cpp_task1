#include <iostream>
#include <string>
#include <unordered_map>

#include "movie_id_finder.h"

auto print_key_value = [](const auto &key, const auto &value) {
    std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
};

int main(int argc, char *argv[]) {
//    if (argc < 2) {
//        std::cerr << "Usage: " << argv[0] << " <file1> <file2> <file3> <name>" << std::endl;
//        return 1;
//    }
    std::unordered_map<std::string, std::string> titles;
    GetID(argv[1], argv[3], titles);
    GetPrimaryTitle(argv[2], titles);
    for (const auto &n: titles)
        print_key_value(n.first, n.second);
    return 0;
}
