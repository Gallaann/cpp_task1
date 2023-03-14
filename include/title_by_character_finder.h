//
// Created by gallaann on 12.03.23.
//

#ifndef TASK1_TITLE_BY_CHARACTER_FINDER_H
#define TASK1_TITLE_BY_CHARACTER_FINDER_H

class MovieTitles {
private:
    std::unordered_map<std::string, std::string> titles;
public:
    int GetID(const std::string &path, const std::string &character_name);

    int GetPrimaryTitle(const std::string &path);

    int GetLocalizedTitle(const std::string &path);

    void PrintResult();
};


#endif //TASK1_TITLE_BY_CHARACTER_FINDER_H
