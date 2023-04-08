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

const std::string kCharactersFileName = "principals";
const std::string kPrimaryTitleFileName = "basics";
const std::string kLocalizedTitleFileName = "akas";
const std::string kCharacterName = "character";

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


std::unordered_map<std::string, std::string> MovieTitles::splitNamedArguments(int argc, char **argv) {
    std::unordered_map<std::string, std::string> arguments = {{kCharactersFileName,     ""},
                                                              {kPrimaryTitleFileName,   ""},
                                                              {kLocalizedTitleFileName, ""},
                                                              {kCharacterName,          ""}};

    std::string name;
    std::string value;

    if (argc != 5) {
        arguments.clear();
        return arguments;
    }

    for (int i = 1; i < argc; ++i) {
        std::string oneArgument = argv[i];

        if (oneArgument.find('=') == std::string::npos) {
            arguments.clear();
            return arguments;
        }

        name = oneArgument.substr(0, oneArgument.find('='));
        value = oneArgument.substr(oneArgument.find('=') + 1, oneArgument.length() - 1);

        if (arguments.find(name) == arguments.end() || value.empty()) {
            arguments.clear();
            return arguments;
        }

        arguments.at(name) = value;
    }

    return arguments;
}

void MovieTitles::findLocalizedMoviesTitlesByCharacterName(int argc, char **argv) {
    auto arguments = splitNamedArguments(argc, argv);

    if (arguments.empty()) {
        return;
    }

    if (!findMovieIdByCharacterName(arguments.at(kCharactersFileName), arguments.at(kCharacterName))) {
        return;
    };
    if (!findPrimaryTitleForMovies(arguments.at(kPrimaryTitleFileName))) {
        return;
    }
    if (!findLocalizedTitleForMovies(arguments.at(kLocalizedTitleFileName))) {
        return;
    }

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
        if (name.find("\"" + characterName + "\"") !=
            std::string::npos) {  // character names represented in files as ["name1", "name2", etc.]
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
            m_titles.at(movieId) = movieTitle;
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
            m_titles.at(movieId) = movieTitle;
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

bool MovieTitles::findColumns(std::string &header, std::unordered_map<std::string, int> &columnNamesMap) {
    auto numberOfColumnsToFind = columnNamesMap.size();
    std::string columnName;
    std::stringstream columnsNamingLineStream(header);
    for (int indexOfColumn = 0; std::getline(columnsNamingLineStream, columnName, '\t'); ++indexOfColumn) {
        if (columnNamesMap.find(columnName) != columnNamesMap.end()) {
            columnNamesMap[columnName] = indexOfColumn;
            --numberOfColumnsToFind;
        }
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
