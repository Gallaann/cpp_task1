//
// Created by gallaann on 12.03.23.
//

#ifndef TASK1_TITLE_BY_CHARACTER_FINDER_H
#define TASK1_TITLE_BY_CHARACTER_FINDER_H

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

class MovieTitles {
public:
    std::unordered_map<std::string, std::string> splitNamedArguments(int argc, char *argv[]);
    void findLocalizedMoviesTitlesByCharacterName(int argc, char *argv[]);
    bool findMovieIdByCharacterName(const std::filesystem::path &path, const std::string &characterName);
    bool findPrimaryTitleForMovies(const std::filesystem::path &path);
    bool findLocalizedTitleForMovies(const std::filesystem::path &path);
    void printResult();
    bool findColumns(std::string &header, std::unordered_map<std::string, int> &columnNamesMap);

private:
    bool getInputStream(std::stringstream &input_stream, const std::filesystem::path &path);

    std::unordered_map<std::string, std::string> m_titles;
};

#endif //TASK1_TITLE_BY_CHARACTER_FINDER_H
