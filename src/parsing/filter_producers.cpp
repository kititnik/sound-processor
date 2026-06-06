#include "parsing/filter_producers.hpp"
#include "filters/ampl_filter.hpp"
#include "filters/normalize_filter.hpp"
#include "filters/silence_filter.hpp"
#include "filters/timestretch_filter.hpp"
#include "filters/lowpass_filter.hpp"
#include <format>
#include <stdexcept>

IFilter* amplFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "ampl") {
        throw std::runtime_error("Wrong filter descriptor for ampl filter producer");
    }
    if(filterDescriptor.params.size() != 1) {
        throw std::runtime_error("Wrong args count for ampl filter producer");
    }
    double factor = 0;
    try {
        factor = std::stod(filterDescriptor.params[0]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error("Error converting the 1st argument of ampl filter");
    }
    if(factor < 0) {
        throw std::runtime_error(std::format("Wrong factor value for ampl filter: expected positive or zero, got: {}", factor));
    }
    return new AmplFilter(factor);
}

IFilter* normalizeFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "normalize") {
        throw std::runtime_error("Wrong filter descriptor for normalize filter producer");
    }
    if(filterDescriptor.params.size() > 1) {
        throw std::runtime_error("Wrong args count for normalize filter producer");
    }
    double peak = 1.0;
    if(filterDescriptor.params.size() == 1) {
        try {
            peak = std::stod(filterDescriptor.params[0]);
        }
        catch(std::exception& exception) {
            throw std::runtime_error("Error converting the 1st argument of normalize filter");
        }
        if(peak < 0 || peak > 1) {
            throw std::runtime_error(std::format("Wrong peak value for normalize filter: expected 0..1, got: {}", peak));
        }
    }
    return new NormalizeFilter(peak);
}

IFilter* silenceFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "silence") {
        throw std::runtime_error("Wrong filter descriptor for silence filter producer");
    }
    if(filterDescriptor.params.size() != 3) {
        throw std::runtime_error("Wrong args count for silence filter producer");
    }
    const std::string& unit = filterDescriptor.params[0];
    if(unit != "sec" && unit != "ms") {
        throw std::runtime_error(std::format("Wrong unit for silence filter: expected sec or ms, got: {}", unit));
    }
    double start = 0;
    double end = 0;
    try {
        start = std::stod(filterDescriptor.params[1]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error("Error converting the 2nd argument of silence filter");
    }
    try {
        end = std::stod(filterDescriptor.params[2]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error("Error converting the 3rd argument of silence filter");
    }
    if(start < 0) {
        throw std::runtime_error(std::format("Wrong start value for silence filter: expected >= 0, got: {}", start));
    }
    if(end < start) {
        throw std::runtime_error(std::format("Wrong end value for silence filter: expected >= start({}), got: {}", start, end));
    }
    return new SilenceFilter(unit, start, end);
}

IFilter* timestretchFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "timestretch") {
        throw std::runtime_error("Wrong filter descriptor for timestretch filter producer");
    }
    if(filterDescriptor.params.size() != 1) {
        throw std::runtime_error("Wrong args count for timestretch filter producer");
    }
    double factor = 0;
    try {
        factor = std::stod(filterDescriptor.params[0]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error("Error converting the 1st argument of timestretch filter");
    }
    if(factor <= 0) {
        throw std::runtime_error(std::format("Wrong factor value for timestretch filter: expected > 0, got: {}", factor));
    }
    return new TimestretchFilter(factor);
}

IFilter* lowpassFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "lowpass") {
        throw std::runtime_error("Wrong filter descriptor for lowpass filter producer");
    }
    if(filterDescriptor.params.size() != 1) {
        throw std::runtime_error("Wrong args count for lowpass filter producer");
    }
    unsigned long windowSize = 0;
    try {
        windowSize = std::stoul(filterDescriptor.params[0]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error("Error converting the 1st argument of lowpass filter");
    }
    if(windowSize < 1 || windowSize % 2 == 0) {
        throw std::runtime_error(std::format("Wrong window size for lowpass filter: expected odd >= 1, got: {}", windowSize));
    }
    return new LowpassFilter(static_cast<size_t>(windowSize));
}
