#include "title_by_character_finder.h"

#include <iostream>

int main(int argc, char *argv[]) {
    MovieTitles movieTitles{};
    movieTitles.findLocalizedMoviesTitlesByCharacterName(argc, argv);
    return 0;
}
