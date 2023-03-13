//
// Created by gallaann on 12.03.23.
//

#ifndef TASK1_MOVIE_ID_FINDER_H
#define TASK1_MOVIE_ID_FINDER_H

int GetID(const std::string &file_name, const std::string &character_name, std::unordered_map <std::string, std::string> &movies);
int GetPrimaryTitle(const std::string &file_name, std::unordered_map <std::string, std::string> &movies);
int GetLocalizedTitle(const std::string &file_name, std::unordered_map <std::string, std::string> &movies);

#endif //TASK1_MOVIE_ID_FINDER_H
