//
// Created by gallaann on 12.03.23.
//

#ifndef TASK1_TITLE_BY_CHARACTER_FINDER_H
#define TASK1_TITLE_BY_CHARACTER_FINDER_H

#include <vector>

class MovieTitles {
private:
    std::unordered_map<std::string, std::string> titles;
public:
    int ParseID(const std::string &path, const std::string &character_name);

    int ParsePrimaryTitle(const std::string &path);

    int ParseLocalizedTitle(const std::string &path);

    void PrintResult();
};

bool FindColumns(std::stringstream header_line, std::unordered_map<std::string, int> some_map);

#endif //TASK1_TITLE_BY_CHARACTER_FINDER_H
