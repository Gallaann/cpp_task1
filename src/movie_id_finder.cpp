//
// Created by gallaann on 12.03.23.
//

#include <iostream>
#include <vector>
#include <sstream>

#include "movie_id_finder.h"

int GetID(const std::string &file_name, const std::string& character_name) {
    std::ifstream input_file(file_name);
    if (!input_file) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(input_file, line)) {
        std::stringstream cur_line(line);
        std::string value;
        std::getline(cur_line, value, '\t');
        std::string movie_id = value;
        std::string name;
        while (std::getline(cur_line, value, '\t')) {
            name = value;
        }
        if (name.find(character_name) != std::string::npos)
            std::cout << movie_id << " " << name << std::endl;
    }
    input_file.close();
    return 0;
}
