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
    kNotFound = -1
};

namespace {
    std::unordered_map<std::string, int> principalsColumnMap = {{"characters", kNotFound},
                                                                {"tconst",     kNotFound}};

    std::unordered_map<std::string, int> basicsColumnMap = {{"tconst",       kNotFound},
                                                            {"isAdult",      kNotFound},
                                                            {"titleType",    kNotFound},
                                                            {"primaryTitle", kNotFound}};

    std::unordered_map<std::string, int> akas_column_map = {{"titleId", kNotFound},
                                                            {"title",   kNotFound},
                                                            {"region",  kNotFound}};
};

bool MovieTitles::findMovieIdByCharacterName(const std::filesystem::path &path, const std::string &characterName) {
    std::stringstream inputStream;
    getInputStream(inputStream, path);

    std::string line;
    std::getline(inputStream, line);

    if (!findColumns(line, principalsColumnMap)) {
        std::cerr << "Error: not enough columns in file" << std::endl;
        return false;
    }

    while (std::getline(inputStream, line)) {
        std::stringstream currentLine(line);
        std::string value;
        std::size_t i = 0;
        std::string movieId;
        std::string name;
        while (std::getline(currentLine, value, '\t')) {
            if (i == principalsColumnMap["tconst"]) {
                movieId = value;
            }
            if (i == principalsColumnMap["characters"]) {
                name = value;
            }
            ++i;
        }
        if (name.find("\"" + characterName + "\"") != std::string::npos) { //character names represented in files as ["name1", "name2", etc.]
            m_titles[movieId];
        }
    }

    return true;
}

bool MovieTitles::findPrimaryTitleForMovies(const std::filesystem::path &path) {
    if (m_titles.empty()) {
        return false;
    }

    std::stringstream inputStream;
    getInputStream(inputStream, path);

    std::string line;
    std::getline(inputStream, line);
    if (!findColumns(line, basicsColumnMap)) {
        std::cerr << "Error: not enough columns in file" << std::endl;
        return false;
    }

    while (std::getline(inputStream, line) && !m_titles.empty()) {
        std::stringstream currentLine(line);
        std::string value;
        std::size_t i = 0;
        std::string movieId;
        std::string isAdult;
        std::string movieTitle;
        std::string movieType;
        while (std::getline(currentLine, value, '\t')) {
            if (i == basicsColumnMap["tconst"]) {
                movieId = value;
            }
            if (i == basicsColumnMap["isAdult"]) {
                isAdult = value;
            }
            if (i == basicsColumnMap["titleType"]) {
                movieType = value;
            }
            if (i == basicsColumnMap["primaryTitle"]) {
                movieTitle = value;
            }
            ++i;
        }
        if (isAdult == "0" && movieType == "movie" && m_titles.find(movieId) != m_titles.end()) {
            m_titles[movieId] = movieTitle;
        } else {
            m_titles.erase(movieId);
        }
    }
    return true;
}

bool MovieTitles::findLocalizedTitleForMovies(const std::filesystem::path &path) {
    if (m_titles.empty()) {
        return false;
    }

    std::stringstream inputStream;
    getInputStream(inputStream, path);

    std::string line;
    std::getline(inputStream, line);
    if (!findColumns(line, akas_column_map)) {
        std::cerr << "Error: not enough columns in file" << std::endl;
        return false;
    }

    while (std::getline(inputStream, line) && !m_titles.empty()) {
        std::stringstream currentLine(line);
        std::string value;
        std::size_t i = 0;
        std::string movieId;
        std::string movieTitle;
        std::string movieRegion;
        while (std::getline(currentLine, value, '\t')) {
            if (i == akas_column_map["titleId"]) {
                movieId = value;
            }
            if (i == akas_column_map["title"]) {
                movieTitle = value;
            }
            if (i == akas_column_map["region"]) {
                movieRegion = value;
            }
            ++i;
        }
        if (movieRegion == "RU" && m_titles.find(movieId) != m_titles.end()) {
            m_titles[movieId] = movieTitle;
        }
    }
    return true;
}

void MovieTitles::printResult() {
    if (m_titles.empty()) {
        std::cerr << "No results found" << std::endl;
        return;
    }
    for (const auto &container: m_titles) {
        std::cout << container.second << std::endl;
    }
}

bool
MovieTitles::findColumns(std::string &columns_naming_line, std::unordered_map<std::string, int> &columnNamesMap) {
    int indexOfColumn = 0;
    auto numberOfColumnsToFind = columnNamesMap.size();
    std::string columnName;
    std::stringstream columnsNamingLineStream(columns_naming_line);
    while (std::getline(columnsNamingLineStream, columnName, '\t')) {
        if (columnNamesMap.find(columnName) != columnNamesMap.end()) {
            columnNamesMap[columnName] = indexOfColumn;
            --numberOfColumnsToFind;
        }
        ++indexOfColumn;
    }
    return numberOfColumnsToFind == 0;
}

bool MovieTitles::getInputStream(std::stringstream &input_stream, const std::filesystem::path &path) {
    std::ifstream inputFileStream(path);
    if (!inputFileStream) {
        std::cerr << "Error: could not open file" << std::endl;
        return false;
    }
    input_stream << inputFileStream.rdbuf();
    return true;
}
