#pragma once

#include "parsing/cmd_line_args_2_pipeline_converter.hpp"
#include "parsing/generator_filter_creator.hpp"
#include <string_view>

class Application {
public:
    void configure();
    void run(int argc, const char* argv[]);

private:
    CmdLineArgs2PipelineConverter _cmdLineArgs2PipelineConverter;
    GeneratorFilterCreator _generatorCreator;
    static constexpr std::string_view _helpMessage = "Usage: sound_processor [-i input.wav] [-o output.wav] [-f filter "
                                                     "[params...]...]";
};
