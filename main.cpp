#include <iostream>
#include <unordered_map>

#include "title_by_character_finder.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> <file3> <name>" << std::endl;
        return 1;
    }
    MovieTitles movie_titles;
    movie_titles.GetID(argv[1], argv[4]);
    movie_titles.GetPrimaryTitle(argv[2]);
    movie_titles.GetLocalizedTitle(argv[3]);
    movie_titles.PrintResult();
    return 0;
}
