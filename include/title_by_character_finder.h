//
// Created by gallaann on 12.03.23.
//

#ifndef TASK1_TITLE_BY_CHARACTER_FINDER_H
#define TASK1_TITLE_BY_CHARACTER_FINDER_H

#include <vector>
#include <unordered_map>
#include <string>

class MovieTitles {
public:
    bool ParseID(const std::string &path, const std::string &character_name);

    bool ParsePrimaryTitle(const std::string &path);

    bool ParseLocalizedTitle(const std::string &path);

    void PrintResult() const;

    bool static findColumns(std::string &columns_naming_line, std::unordered_map<std::string, int> &column_names_map);

private:
    std::unordered_map<std::string, std::string> m_titles;

    bool static getInputStream(std::stringstream &input_stream, const std::string &path_to_file);
};

#endif //TASK1_TITLE_BY_CHARACTER_FINDER_H
