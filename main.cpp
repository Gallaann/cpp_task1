#include <iostream>
#include <unordered_map>

#include <title_by_character_finder.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> <file3> <name>" << std::endl;
        return 1;
    }
    MovieTitles movie_titles;
    movie_titles.ParseID(argv[1], argv[4]);
    movie_titles.ParsePrimaryTitle(argv[2]);
    movie_titles.ParseLocalizedTitle(argv[3]);
    movie_titles.PrintResult();
    return 0;
}
