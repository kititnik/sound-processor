#pragma once

#include "parsing/cmd_line_args_2_pipeline_converter.hpp"
#include <string_view>

class Application {
public:
    void configure();
    void run(int argc, const char* argv[]);

private:
    CmdLineArgs2PipelineConverter _cmdLineArgs2PipelineConverter;
    static constexpr std::string_view _helpMessage =
        "Usage: sound_processor [-i input.wav] [-o output.wav] [-f filter "
        "[params...]...]";
};
