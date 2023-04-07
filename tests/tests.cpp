//
// Created by gallaann on 07.04.23.
//

#include "title_by_character_finder.h"

#include <gtest/gtest.h>

TEST(MovieByCharacterTest, OpenFile){
    MovieTitles movieTitles{};
    bool status = movieTitles.findMovieIdByCharacterName(".","Self");
    EXPECT_EQ(false, status);
}

TEST(MovieByCharacterTest, NotEnoughColumns){
    MovieTitles movieTitles{};
    bool status = movieTitles.findMovieIdByCharacterName("../tests/test_notEnoughColumns.tsv","Self");
    EXPECT_EQ(false, status);
}

TEST(MovieByCharacterTest, EnoughColumns){
    MovieTitles movieTitles{};
    bool status = movieTitles.findMovieIdByCharacterName("../media/data3.tsv","Self");
    EXPECT_EQ(true, status);
}

TEST(PrimaryTitleTest, OpenFile){
    MovieTitles movieTitles{};
    bool status = movieTitles.findPrimaryTitleForMovies(".");
    EXPECT_EQ(false, status);
}

TEST(PrimaryTitleTest, NotEnoughColumns){
    MovieTitles movieTitles{};
    bool status = movieTitles.findPrimaryTitleForMovies("../tests/test_notEnoughColumns.tsv");
    EXPECT_EQ(false, status);
}

TEST(PrimaryTitleTest, EnoughColumns){
    MovieTitles movieTitles{};
    bool status = movieTitles.findPrimaryTitleForMovies("../media/data1.tsv");
    EXPECT_EQ(true, status);
}

TEST(LocalizedTitleTest, NotOpenFile){
    MovieTitles movieTitles{};
    bool status = movieTitles.findLocalizedTitleForMovies(".");
    EXPECT_EQ(false, status);
}

TEST(LocalizedTitleTest, NotEnoughColumns){
    MovieTitles movieTitles{};
    bool status = movieTitles.findLocalizedTitleForMovies("../tests/test_notEnoughColumns.tsv");
    EXPECT_EQ(false, status);
}

TEST(LocalizedTitleTest, EnoughColumns){
    MovieTitles movieTitles{};
    bool status = movieTitles.findLocalizedTitleForMovies("../media/data2.tsv");
    EXPECT_EQ(true, status);
}
