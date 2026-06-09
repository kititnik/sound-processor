#include <catch2/catch_all.hpp>
#include "parsing/args_parser.hpp"

TEST_CASE("Check i/o files parsing", "ArgsParser") {
    const char* argv[] = {"sound_processor", "-i", "in.wav", "-o", "out.wav"};
    ArgsParser parser;
    parser.parseArgs(std::size(argv), argv);
    REQUIRE(parser.getInputFileName().value() == "in.wav");
    REQUIRE(parser.getOutputFileName().value() == "out.wav");
}

TEST_CASE("ArgsParser with params", "ArgsParser") {
    const char* argv[] = {"sound_processor", "-f", "silence", "sec", "1", "2"};
    ArgsParser parser;
    parser.parseArgs(std::size(argv), argv);
    REQUIRE(parser.getFilterDescriptors().size() == 1);
    REQUIRE(parser.getFilterDescriptors()[0].name == "silence");
    REQUIRE(parser.getFilterDescriptors()[0].params.size() == 3);
}

TEST_CASE("ArgsParser unknown flag throws error", "ArgsParser") {
    const char* argv[] = {"sound_processor", "-a"};
    ArgsParser parser;
    REQUIRE_THROWS(parser.parseArgs(std::size(argv), argv));
}
