#include "application.hpp"
#include "parsing/args_parser.hpp"
#include "parsing/cmd_line_args_2_pipeline_converter.hpp"
#include "parsing/filter_producers.hpp"
#include "pipeline.hpp"
#include "wav_reader.hpp"
#include "wav_writer.hpp"
#include "waveform.hpp"
#include <fstream>
#include <iostream>
#include <optional>

void Application::configure() {

    _cmdLineArgs2PipelineConverter.addFilterProducer("ampl", amplFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("normalize",
                                                     normalizeFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("silence",
                                                     silenceFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("timestretch",
                                                     timestretchFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("lowpass",
                                                     lowpassFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("generator",
                                                     generatorFilterCreator);
}

void Application::run(int argc, const char* argv[]) {
    if(argc == 1) {
        std::cout << _helpMessage << '\n';
    }

    ArgsParser argsParser;
    argsParser.parseArgs(argc, argv);

    Waveform waveform;

    if(argsParser.getInputFileName() != std::nullopt) {
        WavReader wavReader;
        std::ifstream fileStream(argsParser.getInputFileName()->c_str(),
                                 std::ifstream::binary);
        waveform = wavReader.read(fileStream);
    }

    const auto& filterDescriptors = argsParser.getFilterDescriptors();
    Pipeline pipeline =
        _cmdLineArgs2PipelineConverter.createPipeline(filterDescriptors);
    pipeline.apply(&waveform);

    if(argsParser.getOutputFileName() != std::nullopt) {
        WavWriter wavWriter;
        std::ofstream fileStream(argsParser.getOutputFileName()->c_str(),
                                 std::ofstream::binary);
        wavWriter.write(fileStream, waveform);
    }
}
