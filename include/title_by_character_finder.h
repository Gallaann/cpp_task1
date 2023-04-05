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
    bool ParseID(const std::filesystem::path &path, const std::string &character_name);

    bool ParsePrimaryTitle(const std::filesystem::path &path);

    bool ParseLocalizedTitle(const std::filesystem::path &path);

    void PrintResult() const;

    bool static findColumns(std::string &columns_naming_line, std::unordered_map<std::string, int> &column_names_map);

private:
    std::unordered_map<std::string, std::string> m_titles;

    bool static getInputStream(std::stringstream &input_stream, const std::filesystem::path &path_to_file);
};

#endif //TASK1_TITLE_BY_CHARACTER_FINDER_H
