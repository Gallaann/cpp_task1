#include "title_by_character_finder.h"

#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> <file3> <name>" << std::endl;
        return 1;
    }
    MovieTitles movie_titles;
    movie_titles.findMovieIdByCharacterName(argv[1], argv[4]);
    movie_titles.findPrimaryTitleForMovies(argv[2]);
    movie_titles.findLocalizedTitleForMovies(argv[3]);
    movie_titles.printResult();
    return 0;
}
