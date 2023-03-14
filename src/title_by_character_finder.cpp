//
// Created by gallaann on 12.03.23.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

#include "title_by_character_finder.h"

int MovieTitles::GetID(const std::string &path, const std::string &character_name) {
    std::ifstream input_file(path);
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
            titles[movie_id];
    }
    input_file.close();
    return 0;
}

int MovieTitles::GetPrimaryTitle(const std::string &path) {
    std::ifstream input_file(path);
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
        std::getline(cur_line, value, '\t');
        std::string movie_type = value;
        std::getline(cur_line, value, '\t');
        std::string movie_title = value;
        std::getline(cur_line, value, '\t'); //don't need original title
        std::getline(cur_line, value, '\t');
        std::string is_adult = value;
        if (is_adult == "0" && movie_type == "movie" && titles.find(movie_id) != titles.end())
            titles[movie_id] = movie_title;
        else
            titles.erase(movie_id);
    }
    input_file.close();
    return 0;
}

int MovieTitles::GetLocalizedTitle(const std::string &path) {
    std::ifstream input_file(path);
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
        std::getline(cur_line, value, '\t'); //don't need ordering
        std::getline(cur_line, value, '\t');
        std::string movie_title = value;
        std::getline(cur_line, value, '\t');
        std::string region = value;
        if (region == "RU" && titles.find(movie_id) != titles.end())
            titles[movie_id] = movie_title;
    }
    input_file.close();
    return 0;
}

void MovieTitles::PrintResult() {
    for (const auto &container: titles)
        std::cout << container.second << "\n";
}
