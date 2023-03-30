//
// Created by gallaann on 12.03.23.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

#include <title_by_character_finder.h>

bool MovieTitles::ParseID(const std::string &path, const std::string &character_name) {
    std::ifstream input_file(path);
    if (!input_file) {
        std::cerr << "Error: could not open file." << std::endl;
        return false;
    }

    std::string line;
    std::getline(input_file, line);
    std::unordered_map<std::string, int> column_map = {{"characters", 0},
                                                       {"tconst",     0}};
    if (!FindColumns(line, column_map)) {
        std::cerr << "Error: not enough columns in file." << std::endl;
        return false;
    }

    while (std::getline(input_file, line)) {
        std::stringstream cur_line(line);
        std::string value;
        std::size_t i = 0;
        std::string movie_id;
        std::string name;
        while (std::getline(cur_line, value, '\t')) {
            if (i == column_map["tconst"]) {
                movie_id = value;
            }
            if (i == column_map["characters"]) {
                name = value;
            }
            i++;
        }
        if (name.find("\"" + character_name + "\"") != std::string::npos) {
            m_titles[movie_id];
        }
    }

    input_file.close();
    return true;
}

bool MovieTitles::ParsePrimaryTitle(const std::string &path) {
    if (m_titles.empty()) {
        return false;
    }
    std::ifstream input_file(path);
    if (!input_file) {
        std::cerr << "Error: could not open file." << std::endl;
        return false;
    }

    std::string line;
    std::getline(input_file, line);
    std::unordered_map<std::string, int> column_map = {{"tconst",       0},
                                                       {"isAdult",      0},
                                                       {"titleType",    0},
                                                       {"primaryTitle", 0}};
    if (!FindColumns(line, column_map)) {
        std::cerr << "Error: not enough columns in file." << std::endl;
        return false;
    }

    while (std::getline(input_file, line) && !m_titles.empty()) {
        std::stringstream cur_line(line);
        std::string value;
        std::size_t i = 0;
        std::string movie_id;
        std::string is_adult;
        std::string movie_title;
        std::string movie_type;
        while (std::getline(cur_line, value, '\t')) {
            if (i == column_map["tconst"]) {
                movie_id = value;
            }
            if (i == column_map["isAdult"]) {
                is_adult = value;
            }
            if (i == column_map["titleType"]) {
                movie_type = value;
            }
            if (i == column_map["primaryTitle"]) {
                movie_title = value;
            }
            i++;
        }
        if (is_adult == "0" && movie_type == "movie" && m_titles.find(movie_id) != m_titles.end()) {
            m_titles[movie_id] = movie_title;
        } else {
            m_titles.erase(movie_id);
        }
    }
    input_file.close();
    return true;
}

bool MovieTitles::ParseLocalizedTitle(const std::string &path) {
    if (m_titles.empty()) {
        return false;
    }
    std::ifstream input_file(path);
    if (!input_file) {
        std::cerr << "Error: could not open file." << std::endl;
        return false;
    }
    std::string line;
    std::getline(input_file, line);
    std::unordered_map<std::string, int> column_map = {{"titleId", 0},
                                                       {"title",   0},
                                                       {"region",  0}};
    if (!FindColumns(line, column_map)) {
        std::cerr << "Error: not enough columns in file." << std::endl;
        return false;
    }

    while (std::getline(input_file, line) && !m_titles.empty()) {
        std::stringstream cur_line(line);
        std::string value;
        std::size_t i = 0;
        std::string movie_id;
        std::string movie_title;
        std::string movie_region;
        while (std::getline(cur_line, value, '\t')) {
            if (i == column_map["titleId"]) {
                movie_id = value;
            }
            if (i == column_map["title"]) {
                movie_title = value;
            }
            if (i == column_map["region"]) {
                movie_region = value;
            }
            i++;
        }
        if (movie_region == "RU" && m_titles.find(movie_id) != m_titles.end()) {
            m_titles[movie_id] = movie_title;
        }
    }
    input_file.close();
    return true;
}

void MovieTitles::PrintResult() const {
    if (m_titles.empty()) {
        std::cerr << "No results found." << std::endl;
        return;
    }
    for (const auto &container: m_titles) {
        std::cout << container.second << std::endl;
    }
}

bool MovieTitles::FindColumns(std::string &header_line, std::unordered_map<std::string, int> &some_map) {
    std::string value;
    int i = 0;
    auto number_of_columns = some_map.size();
    std::stringstream ss_header_line(header_line);
    while (std::getline(ss_header_line, value, '\t')) {
        if (some_map.find(value) != some_map.end()) {
            some_map[value] = i;
            number_of_columns--;
        }
        i++;
    }
    return number_of_columns == 0;
}

bool MovieTitles::OpenFile(std::stringstream string_stream, std::string &path_to_file) {
    std::ifstream input_file(path_to_file);
    if (!input_file) {
        std::cerr << "Error: could not open file." << std::endl;
        return false;
    }
    string_stream << input_file.rdbuf();
    input_file.close();
    return true;
}
