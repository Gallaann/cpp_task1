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
    bool findMovieIdByCharacterName(const std::filesystem::path &path, const std::string &characterName);
    bool findPrimaryTitleForMovies(const std::filesystem::path &path);
    bool findLocalizedTitleForMovies(const std::filesystem::path &path);
    void printResult() const;
    bool static findColumns(std::string &columns_naming_line, std::unordered_map<std::string, int> &columnNamesMap);

private:
    bool static getInputStream(std::stringstream &input_stream, const std::filesystem::path &path);

    std::unordered_map<std::string, std::string> m_titles;
};

#endif //TASK1_TITLE_BY_CHARACTER_FINDER_H
