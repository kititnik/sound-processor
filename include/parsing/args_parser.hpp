#pragma once

#include "filter_descriptor.hpp"
#include <optional>
#include <string>
#include <string_view>
#include <vector>

class ArgsParser {
public:
    void parseArgs(int argc, const char* argv[]);

    const std::optional<std::string>& getInputFileName() const;
    const std::optional<std::string>& getOutputFileName() const;
    const std::vector<FilterDescriptor>& getFilterDescriptors() const;

private:
    std::string_view requireNext(int argvIdx, int argc, const char* argv[],
                                 std::string_view flag);

    std::optional<std::string> _inputFileName;
    std::optional<std::string> _outputFileName;
    std::vector<FilterDescriptor> _filterDescriptors;
};
