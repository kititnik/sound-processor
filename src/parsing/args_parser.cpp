#include "parsing/args_parser.hpp"
#include "parsing/filter_descriptor.hpp"
#include <format>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

void ArgsParser::parseArgs(int argc, char* argv[]) {
    for(int i = 1; i < argc; ) {
        std::string_view arg = argv[i];
        if(arg == "-i") {
            _inputFileName = requireNext(i, argc, argv, "-i");
            i += 2;
        }
        else if(arg == "-o") {
            _outputFileName = requireNext(i, argc, argv, "-o");
            i += 2;
        }
        else if(arg == "-f") {
            FilterDescriptor filterDescriptor;
            filterDescriptor.name = requireNext(i, argc, argv, "-f");
            i += 2;
            while(i < argc && argv[i][0] != '-') {
                filterDescriptor.params.push_back(argv[i]);
                i++;
            }
            _filterDescriptors.push_back(std::move(filterDescriptor));
        }
        else {
            throw std::runtime_error(std::format("Wrong CLI input: unknown flag: {}", argv[i]));
        }
    }
}

std::string_view ArgsParser::requireNext(int argvIdx, int argc, char* argv[], std::string_view flag) {
    if(argvIdx + 1 >= argc) {
        throw std::runtime_error(std::format("Wrong CLI input: missing value after {}", flag));
    }
    return argv[argvIdx+1];
}

const std::optional<std::string>& ArgsParser::getInputFileName() const {
    return _inputFileName;
}

const std::optional<std::string>& ArgsParser::getOutputFileName() const {
    return _outputFileName;
}

const std::vector<FilterDescriptor>& ArgsParser::getFilterDescriptors() const {
    return _filterDescriptors;
}