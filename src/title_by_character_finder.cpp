//
// Created by gallaann on 12.03.23.
//

#include "title_by_character_finder.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

enum {
    kNotFound = -1
};

const std::string kTitleField = "title";
const std::string kTitleIdField = "titleId";
const std::string kRegionField = "region";
const std::string kPrimaryTitleField = "primaryTitle";
const std::string kTitleTypeField = "titleType";
const std::string kIsAdultField = "isAdult";
const std::string kTconstField = "tconst";
const std::string kCharactersField = "characters";

namespace {
    std::unordered_map<std::string, int> principalsColumnMap = {{kCharactersField, kNotFound},
                                                                {kTconstField,     kNotFound}};

    std::unordered_map<std::string, int> basicsColumnMap = {{kTconstField,       kNotFound},
                                                            {kIsAdultField,      kNotFound},
                                                            {kTitleTypeField,    kNotFound},
                                                            {kPrimaryTitleField, kNotFound}};

    std::unordered_map<std::string, int> akas_column_map = {{kTitleIdField, kNotFound},
                                                            {kTitleField,   kNotFound},
                                                            {kRegionField,  kNotFound}};
};

void MovieTitles::findLocalizedMoviesTitlesByCharacterName(int argc, char **argv) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> <file3> <name>" << std::endl;
    }

    findMovieIdByCharacterName(argv[1], argv[4]);
    findPrimaryTitleForMovies(argv[2]);
    findLocalizedTitleForMovies(argv[3]);
    printResult();
}

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
        std::string movieId;
        std::string name;
        for (int i = 0; std::getline(currentLine, value, '\t'); ++i) {
            if (i == principalsColumnMap.at(kTconstField)) {
                movieId = value;
            }
            if (i == principalsColumnMap.at(kCharactersField)) {
                name = value;
            }
        }
        if (name.find("\"" + characterName + "\"") != std::string::npos) {  // character names represented in files as ["name1", "name2", etc.]
            m_titles[movieId];  // make new pair with empty value field
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

    while (std::getline(inputStream, line)) {
        std::stringstream currentLine(line);
        std::string value;
        std::string movieId;
        std::string isAdult;
        std::string movieTitle;
        std::string movieType;
        for (int i = 0; std::getline(currentLine, value, '\t'); ++i) {
            if (i == basicsColumnMap.at(kTconstField)) {
                movieId = value;
            }
            if (i == basicsColumnMap.at(kIsAdultField)) {
                isAdult = value;
            }
            if (i == basicsColumnMap.at(kTitleTypeField)) {
                movieType = value;
            }
            if (i == basicsColumnMap.at(kPrimaryTitleField)) {
                movieTitle = value;
            }
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

    while (std::getline(inputStream, line)) {
        std::stringstream currentLine(line);
        std::string value;
        std::string movieId;
        std::string movieTitle;
        std::string movieRegion;
        for (int i = 0; std::getline(currentLine, value, '\t'); ++i) {
            if (i == akas_column_map.at(kTitleIdField)) {
                movieId = value;
            }
            if (i == akas_column_map.at(kTitleField)) {
                movieTitle = value;
            }
            if (i == akas_column_map.at(kRegionField)) {
                movieRegion = value;
            }
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

    for (const auto &it: m_titles) {
        std::cout << it.second << std::endl;
    }
}

bool MovieTitles::findColumns(std::string &columns_naming_line, std::unordered_map<std::string, int> &columnNamesMap) {
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
