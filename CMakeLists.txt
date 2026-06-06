cmake_minimum_required(VERSION 3.10)
project(sound_processor)

set(CMAKE_CXX_STANDARD 23)

add_executable(sound_processor
    app/main.cpp
    src/application.cpp
    src/pipeline.cpp
    src/wav_reader.cpp
    src/wav_writer.cpp
    src/waveform.cpp
    src/filters/ampl_filter.cpp
    src/filters/normalize_filter.cpp
    src/filters/silence_filter.cpp
    src/filters/timestretch_filter.cpp
    src/filters/lowpass_filter.cpp
    src/parsing/args_parser.cpp
    src/parsing/cmd_line_args_2_pipeline_converter.cpp
    src/parsing/filter_producers.cpp
)

target_include_directories(sound_processor PRIVATE include/)