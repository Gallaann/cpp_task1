//
// Created by gallaann on 12.03.23.
//

#include "title_by_character_finder.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

enum{
    notFound = -1
};

namespace {
    std::unordered_map<std::string, int> principals_column_map = {{"characters", notFound},
                                                                  {"tconst",     notFound}};

    std::unordered_map<std::string, int> basics_column_map = {{"tconst",       notFound},
                                                              {"isAdult",      notFound},
                                                              {"titleType",    notFound},
                                                              {"primaryTitle", notFound}};

    std::unordered_map<std::string, int> akas_column_map = {{"titleId", notFound},
                                                            {"title",   notFound},
                                                            {"region",  notFound}};
};

bool MovieTitles::findMovieIdByCharacterName(const std::filesystem::path &path, const std::string &character_name) {
    std::stringstream input_stream;
    getInputStream(input_stream, path);

    std::string line;
    std::getline(input_stream, line);

    if (!findColumns(line, principals_column_map)) {
        std::cerr << "Error: not enough columns in file" << std::endl;
        return false;
    }

    while (std::getline(input_stream, line)) {
        std::stringstream cur_line(line);
        std::string value;
        std::size_t i = 0;
        std::string movie_id;
        std::string name;
        while (std::getline(cur_line, value, '\t')) {
            if (i == principals_column_map["tconst"]) {
                movie_id = value;
            }
            if (i == principals_column_map["characters"]) {
                name = value;
            }
            ++i;
        }
        if (name.find("\"" + character_name + "\"") != std::string::npos) { //character names represented in files as ["name1", "name2", etc.]
            m_titles[movie_id];
        }
    }

    return true;
}

bool MovieTitles::findPrimaryTitleForMovies(const std::filesystem::path &path) {
    if (m_titles.empty()) {
        return false;
    }

    std::stringstream input_stream;
    getInputStream(input_stream, path);

    std::string line;
    std::getline(input_stream, line);
    if (!findColumns(line, basics_column_map)) {
        std::cerr << "Error: not enough columns in file" << std::endl;
        return false;
    }

    while (std::getline(input_stream, line) && !m_titles.empty()) {
        std::stringstream cur_line(line);
        std::string value;
        std::size_t i = 0;
        std::string movie_id;
        std::string is_adult;
        std::string movie_title;
        std::string movie_type;
        while (std::getline(cur_line, value, '\t')) {
            if (i == basics_column_map["tconst"]) {
                movie_id = value;
            }
            if (i == basics_column_map["isAdult"]) {
                is_adult = value;
            }
            if (i == basics_column_map["titleType"]) {
                movie_type = value;
            }
            if (i == basics_column_map["primaryTitle"]) {
                movie_title = value;
            }
            ++i;
        }
        if (is_adult == "0" && movie_type == "movie" && m_titles.find(movie_id) != m_titles.end()) {
            m_titles[movie_id] = movie_title;
        } else {
            m_titles.erase(movie_id);
        }
    }
    return true;
}

bool MovieTitles::findLocalizedTitleForMovies(const std::filesystem::path &path) {
    if (m_titles.empty()) {
        return false;
    }

    std::stringstream input_stream;
    getInputStream(input_stream, path);

    std::string line;
    std::getline(input_stream, line);
    if (!findColumns(line, akas_column_map)) {
        std::cerr << "Error: not enough columns in file" << std::endl;
        return false;
    }

    while (std::getline(input_stream, line) && !m_titles.empty()) {
        std::stringstream cur_line(line);
        std::string value;
        std::size_t i = 0;
        std::string movie_id;
        std::string movie_title;
        std::string movie_region;
        while (std::getline(cur_line, value, '\t')) {
            if (i == akas_column_map["titleId"]) {
                movie_id = value;
            }
            if (i == akas_column_map["title"]) {
                movie_title = value;
            }
            if (i == akas_column_map["region"]) {
                movie_region = value;
            }
            ++i;
        }
        if (movie_region == "RU" && m_titles.find(movie_id) != m_titles.end()) {
            m_titles[movie_id] = movie_title;
        }
    }
    return true;
}

void MovieTitles::printResult() const {
    if (m_titles.empty()) {
        std::cerr << "No results found" << std::endl;
        return;
    }
    for (const auto &container: m_titles) {
        std::cout << container.second << std::endl;
    }
}

bool
MovieTitles::findColumns(std::string &columns_naming_line, std::unordered_map<std::string, int> &column_names_map) {
    int index_of_column = 0;
    auto number_of_columns_to_find = column_names_map.size();
    std::string column_name;
    std::stringstream columns_naming_line_stream(columns_naming_line);
    while (std::getline(columns_naming_line_stream, column_name, '\t')) {
        if (column_names_map.find(column_name) != column_names_map.end()) {
            column_names_map[column_name] = index_of_column;
            --number_of_columns_to_find;
        }
        ++index_of_column;
    }
    return number_of_columns_to_find == 0;
}

bool MovieTitles::getInputStream(std::stringstream &input_stream, const std::filesystem::path &path_to_file) {
    std::ifstream input_file_stream(path_to_file);
    if (!input_file_stream) {
        std::cerr << "Error: could not open file" << std::endl;
        return false;
    }
    input_stream << input_file_stream.rdbuf();
    return true;
}
