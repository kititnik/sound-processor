#pragma once

#include <optional>
#include <string_view>
#include <vector>
#include <string>
#include "filter_descriptor.hpp"

class ArgsParser {
public:
    void parseArgs(int argc, char* argv[]);
    
    const std::optional<std::string>& getInputFileName() const;
    const std::optional<std::string>& getOutputFileName() const;
    const std::vector<FilterDescriptor>& getFilterDescriptors() const;

private:
    std::string_view requireNext(int argvIdx, int argc, char* argv[], std::string_view flag);
    
    std::optional<std::string> _inputFileName;
    std::optional<std::string> _outputFileName;
    std::vector<FilterDescriptor> _filterDescriptors;
};