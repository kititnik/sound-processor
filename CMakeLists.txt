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
    src/filters/sin_gen_filter.cpp
    src/filters/am_sin_gen_filter.cpp
    src/filters/fm_sin_gen_filter.cpp
    src/filters/reverse_filter.cpp
    src/filters/repeat_filter.cpp
    src/filters/fade_filter.cpp
    src/parsing/args_parser.cpp
    src/parsing/cmd_line_args_2_pipeline_converter.cpp
    src/parsing/filter_producers.cpp
    src/parsing/filter_registry.cpp
    src/parsing/generator_filter_creator.cpp
)

target_include_directories(sound_processor PRIVATE include/)

find_package(Doxygen OPTIONAL_COMPONENTS dot)
if (DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_RECURSIVE YES)
    doxygen_add_docs(docs include/ ALL)
endif()

if (BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)
    enable_testing()

    add_executable(sound_processor_tests
        tests/waveform_test.cpp
        tests/wav_io_test.cpp
        tests/args_parser_test.cpp
        tests/filters_test.cpp
        tests/pipeline_test.cpp
        src/pipeline.cpp
        src/wav_reader.cpp
        src/wav_writer.cpp
        src/waveform.cpp
        src/filters/ampl_filter.cpp
        src/filters/normalize_filter.cpp
        src/filters/silence_filter.cpp
        src/filters/timestretch_filter.cpp
        src/filters/lowpass_filter.cpp
        src/filters/sin_gen_filter.cpp
        src/filters/am_sin_gen_filter.cpp
        src/filters/fm_sin_gen_filter.cpp
        src/filters/reverse_filter.cpp
        src/filters/repeat_filter.cpp
        src/filters/fade_filter.cpp
        src/parsing/args_parser.cpp
        src/parsing/cmd_line_args_2_pipeline_converter.cpp
        src/parsing/filter_producers.cpp
        src/parsing/filter_registry.cpp
        src/parsing/generator_filter_creator.cpp
    )

    target_include_directories(sound_processor_tests PRIVATE include/)
    target_link_libraries(sound_processor_tests PRIVATE Catch2::Catch2WithMain)
    add_test(NAME Tests COMMAND $<TARGET_FILE:sound_processor_tests>)
endif()