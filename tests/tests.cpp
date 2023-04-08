//
// Created by gallaann on 07.04.23.
//

#include "title_by_character_finder.h"

#include <gtest/gtest.h>

TEST(SplitArgumentsTest, EmptyInput) {
    int argc = 1;
    char **argv = new char *[argc];
    argv[0] = const_cast<char *>("name1=value1");

    MovieTitles movieTitles{};
    auto args = movieTitles.splitNamedArguments(argc, argv);

    EXPECT_TRUE(args.empty());
}

TEST(SplitArgumentsTest, NotEnoughArguments) {
    int argc = 3;
    char **argv = new char *[argc];
    argv[0] = const_cast<char *>("name1=value1");
    argv[1] = const_cast<char *>("principals=path1");
    argv[2] = const_cast<char *>("basics=path2");

    MovieTitles movieTitles{};
    auto args = movieTitles.splitNamedArguments(argc, argv);

    EXPECT_TRUE(args.empty());
}

TEST(SplitArgumentsTest, TooManyArguments) {
    int argc = 6;
    char **argv = new char *[argc];
    argv[0] = const_cast<char *>("name1=value1");
    argv[1] = const_cast<char *>("principals=path1");
    argv[2] = const_cast<char *>("basics=path2");
    argv[3] = const_cast<char *>("akas=path3");
    argv[4] = const_cast<char *>("character=some_name");
    argv[4] = const_cast<char *>("name2=value2");

    MovieTitles movieTitles{};
    auto args = movieTitles.splitNamedArguments(argc, argv);

    EXPECT_TRUE(args.empty());
}

TEST(SplitArgumentsTest, NameWithoutValue) {
    int argc = 5;
    char **argv = new char *[argc];
    argv[0] = const_cast<char *>("name1=value1");
    argv[1] = const_cast<char *>("principals=");
    argv[2] = const_cast<char *>("basics=");
    argv[3] = const_cast<char *>("akas=");
    argv[4] = const_cast<char *>("character=");

    MovieTitles movieTitles{};
    auto args = movieTitles.splitNamedArguments(argc, argv);

    EXPECT_TRUE(args.empty());
}

TEST(SplitArgumentsTest, ValueWithoutName) {
    int argc = 5;
    char **argv = new char *[argc];
    argv[0] = const_cast<char *>("name1=value1");
    argv[1] = const_cast<char *>("=path1");
    argv[2] = const_cast<char *>("=path2");
    argv[3] = const_cast<char *>("=path3");
    argv[4] = const_cast<char *>("=some_name");

    MovieTitles movieTitles{};
    auto args = movieTitles.splitNamedArguments(argc, argv);

    EXPECT_TRUE(args.empty());
}

TEST(SplitArgumentsTest, NoDelimeter) {
    int argc = 5;
    char **argv = new char *[argc];
    argv[0] = const_cast<char *>("name");
    argv[1] = const_cast<char *>("path1");
    argv[2] = const_cast<char *>("path2");
    argv[3] = const_cast<char *>("path3");
    argv[4] = const_cast<char *>("some_name");

    MovieTitles movieTitles{};
    auto args = movieTitles.splitNamedArguments(argc, argv);

    EXPECT_TRUE(args.empty());
}

TEST(SplitArgumentsTest, BadName) {
    int argc = 5;
    char **argv = new char *[argc];
    argv[0] = const_cast<char *>("name=value");
    argv[1] = const_cast<char *>("--=path1");
    argv[2] = const_cast<char *>("-some_name=path2");
    argv[3] = const_cast<char *>("some_name--=path3");
    argv[4] = const_cast<char *>("-some_name-=some_name");

    MovieTitles movieTitles{};
    auto args = movieTitles.splitNamedArguments(argc, argv);

    EXPECT_TRUE(args.empty());
}

TEST(SplitArgumentsTest, GoodTest) {
    int argc = 5;
    char **argv = new char *[argc];
    argv[0] = const_cast<char *>("name1=value1");
    argv[1] = const_cast<char *>("principals=path1");
    argv[2] = const_cast<char *>("basics=path2");
    argv[3] = const_cast<char *>("akas=path3");
    argv[4] = const_cast<char *>("character=some_name");

    MovieTitles movieTitles{};
    auto args = movieTitles.splitNamedArguments(argc, argv);

    std::unordered_map<std::string, std::string> arguments = {{"principals", "path1"},
                                                              {"basics",     "path2"},
                                                              {"akas",       "path3"},
                                                              {"character",  "some_name"}};

    EXPECT_EQ(args, arguments);
}

TEST(MovieByCharacterTest, OpenFile) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findMovieIdByCharacterName(".", "Self");
    EXPECT_EQ(false, status);
}

TEST(MovieByCharacterTest, NotEnoughColumns) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findMovieIdByCharacterName("../tests/test_notEnoughColumns.tsv", "Self");
    EXPECT_EQ(false, status);
}

TEST(MovieByCharacterTest, EnoughColumns) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findMovieIdByCharacterName("../tests/test_principals.tsv", "Self");
    EXPECT_EQ(true, status);
}

TEST(PrimaryTitleTest, OpenFile) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findPrimaryTitleForMovies(".");
    EXPECT_EQ(false, status);
}

TEST(PrimaryTitleTest, NotEnoughColumns) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findPrimaryTitleForMovies("../tests/test_notEnoughColumns.tsv");
    EXPECT_EQ(false, status);
}

TEST(PrimaryTitleTest, EnoughColumns) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findPrimaryTitleForMovies("../tests/test_basics.tsv");
    EXPECT_EQ(true, status);
}

TEST(LocalizedTitleTest, NotOpenFile) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findLocalizedTitleForMovies(".");
    EXPECT_EQ(false, status);
}

TEST(LocalizedTitleTest, NotEnoughColumns) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findLocalizedTitleForMovies("../tests/test_notEnoughColumns.tsv");
    EXPECT_EQ(false, status);
}

TEST(LocalizedTitleTest, EnoughColumns) {
    MovieTitles movieTitles{};
    bool status = movieTitles.findLocalizedTitleForMovies("../tests/test_akas.tsv");
    EXPECT_EQ(true, status);
}
