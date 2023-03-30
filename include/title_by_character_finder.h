//
// Created by gallaann on 12.03.23.
//

#ifndef TASK1_TITLE_BY_CHARACTER_FINDER_H
#define TASK1_TITLE_BY_CHARACTER_FINDER_H

#include <vector>

class MovieTitles {
private:
    std::unordered_map<std::string, std::string> m_titles;

    bool static OpenFile(std::stringstream string_stream, std::string &path_to_file);

public:
    bool ParseID(const std::string &path, const std::string &character_name);

    bool ParsePrimaryTitle(const std::string &path);

    bool ParseLocalizedTitle(const std::string &path);

    void PrintResult() const;

    bool static FindColumns(std::string &header_line, std::unordered_map<std::string, int> &some_map);
};

#endif //TASK1_TITLE_BY_CHARACTER_FINDER_H
