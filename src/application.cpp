#include "application.hpp"
#include "loggers/console_logger.hpp"
#include "parsing/args_parser.hpp"
#include "parsing/cmd_line_args_2_pipeline_converter.hpp"
#include "parsing/filter_producers.hpp"
#include "pipeline.hpp"
#include "wav_reader.hpp"
#include "wav_writer.hpp"
#include "waveform.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>

void Application::configure() {
    Logger::set(std::make_shared<ConsoleLogger>());
    Logger::log("Logger connected");

    _cmdLineArgs2PipelineConverter.addFilterProducer("ampl", amplFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("normalize", normalizeFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("silence", silenceFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("timestretch", timestretchFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("lowpass", lowpassFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("reverse", reverseFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("repeat", repeatFilterCreator);
    _cmdLineArgs2PipelineConverter.addFilterProducer("fade", fadeFilterCreator);
    _generatorCreator.addGeneratorProducer("sin", sinGeneratorCreator);
    _generatorCreator.addGeneratorProducer("am", amGeneratorCreator);
    _generatorCreator.addGeneratorProducer("fm", fmGeneratorCreator);
    // _generatorCreator used as FilterProducer via operator()
    _cmdLineArgs2PipelineConverter.addFilterProducer("generator", _generatorCreator);

    Logger::log("All filters registered");
}

void Application::run(int argc, const char* argv[]) {
    if(argc == 1) {
        std::cout << _helpMessage << '\n';
        return;
    }

    ArgsParser argsParser;
    argsParser.parseArgs(argc, argv);

    Waveform waveform;

    if(argsParser.getInputFileName() != std::nullopt) {
        Logger::log("Reading: " + *argsParser.getInputFileName());
        WavReader wavReader;
        std::ifstream fileStream(argsParser.getInputFileName()->c_str(), std::ifstream::binary);
        waveform = wavReader.read(fileStream);
        Logger::log("Read " + std::to_string(waveform.size()) + " samples");
    }

    const auto& filterDescriptors = argsParser.getFilterDescriptors();
    Pipeline pipeline = _cmdLineArgs2PipelineConverter.createPipeline(filterDescriptors);
    Logger::log("Pipeline created with " + std::to_string(pipeline.getFilterCount()) + " filters");
    pipeline.apply(&waveform);
    Logger::log("Pipeline complete");

    if(argsParser.getOutputFileName() != std::nullopt) {
        Logger::log("Writing: " + *argsParser.getOutputFileName());
        WavWriter wavWriter;
        std::ofstream fileStream(argsParser.getOutputFileName()->c_str(), std::ofstream::binary);
        wavWriter.write(fileStream, waveform);
        Logger::log("Write complete");
    }
}
