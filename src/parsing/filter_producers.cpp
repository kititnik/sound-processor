#include "parsing/filter_producers.hpp"
#include "filters/am_sin_gen_filter.hpp"
#include "filters/ampl_filter.hpp"
#include "filters/fm_sin_gen_filter.hpp"
#include "filters/lowpass_filter.hpp"
#include "filters/normalize_filter.hpp"
#include "filters/silence_filter.hpp"
#include "filters/sin_gen_filter.hpp"
#include "filters/timestretch_filter.hpp"
#include <format>
#include <map>
#include <stdexcept>

IFilter* amplFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "ampl") {
        throw std::runtime_error(
            "Wrong filter descriptor for ampl filter producer");
    }
    if(filterDescriptor.params.size() != 1) {
        throw std::runtime_error("Wrong args count for ampl filter producer");
    }
    double factor = 0;
    try {
        factor = std::stod(filterDescriptor.params[0]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting the 1st argument of ampl filter");
    }
    if(factor < 0) {
        throw std::runtime_error(
            std::format("Wrong factor value for ampl filter: expected positive "
                        "or zero, got: {}",
                        factor));
    }
    return new AmplFilter(factor);
}

IFilter* normalizeFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "normalize") {
        throw std::runtime_error(
            "Wrong filter descriptor for normalize filter producer");
    }
    if(filterDescriptor.params.size() > 1) {
        throw std::runtime_error(
            "Wrong args count for normalize filter producer");
    }
    double peak = 1.0;
    if(filterDescriptor.params.size() == 1) {
        try {
            peak = std::stod(filterDescriptor.params[0]);
        }
        catch(std::exception& exception) {
            throw std::runtime_error(
                "Error converting the 1st argument of normalize filter");
        }
        if(peak < 0 || peak > 1) {
            throw std::runtime_error(std::format(
                "Wrong peak value for normalize filter: expected 0..1, got: {}",
                peak));
        }
    }
    return new NormalizeFilter(peak);
}

IFilter* silenceFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "silence") {
        throw std::runtime_error(
            "Wrong filter descriptor for silence filter producer");
    }
    if(filterDescriptor.params.size() != 3) {
        throw std::runtime_error(
            "Wrong args count for silence filter producer");
    }
    const std::string& unit = filterDescriptor.params[0];
    if(unit != "sec" && unit != "ms") {
        throw std::runtime_error(std::format(
            "Wrong unit for silence filter: expected sec or ms, got: {}",
            unit));
    }
    double start = 0;
    double end = 0;
    try {
        start = std::stod(filterDescriptor.params[1]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting the 2nd argument of silence filter");
    }
    try {
        end = std::stod(filterDescriptor.params[2]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting the 3rd argument of silence filter");
    }
    if(start < 0) {
        throw std::runtime_error(std::format(
            "Wrong start value for silence filter: expected >= 0, got: {}",
            start));
    }
    if(end < start) {
        throw std::runtime_error(
            std::format("Wrong end value for silence filter: expected >= "
                        "start({}), got: {}",
                        start, end));
    }
    return new SilenceFilter(unit, start, end);
}

IFilter* timestretchFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "timestretch") {
        throw std::runtime_error(
            "Wrong filter descriptor for timestretch filter producer");
    }
    if(filterDescriptor.params.size() != 1) {
        throw std::runtime_error(
            "Wrong args count for timestretch filter producer");
    }
    double factor = 0;
    try {
        factor = std::stod(filterDescriptor.params[0]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting the 1st argument of timestretch filter");
    }
    if(factor <= 0) {
        throw std::runtime_error(std::format(
            "Wrong factor value for timestretch filter: expected > 0, got: {}",
            factor));
    }
    return new TimestretchFilter(factor);
}

IFilter* lowpassFilterCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.name != "lowpass") {
        throw std::runtime_error(
            "Wrong filter descriptor for lowpass filter producer");
    }
    if(filterDescriptor.params.size() != 1) {
        throw std::runtime_error(
            "Wrong args count for lowpass filter producer");
    }
    unsigned long windowSize = 0;
    try {
        windowSize = std::stoul(filterDescriptor.params[0]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting the 1st argument of lowpass filter");
    }
    if(windowSize < 1 || windowSize % 2 == 0) {
        throw std::runtime_error(std::format(
            "Wrong window size for lowpass filter: expected odd >= 1, got: {}",
            windowSize));
    }
    return new LowpassFilter(static_cast<size_t>(windowSize));
}

IFilter* sinGeneratorCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.params.size() != 3) {
        throw std::runtime_error("Wrong args count for generator sin: expected "
                                 "frequency_hz duration_ms");
    }
    double frequencyHz = 0;
    double durationMs = 0;
    try {
        frequencyHz = std::stod(filterDescriptor.params[1]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting frequency_hz argument of generator sin");
    }
    try {
        durationMs = std::stod(filterDescriptor.params[2]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting duration_ms argument of generator sin");
    }
    if(frequencyHz < 0) {
        throw std::runtime_error(std::format(
            "Wrong frequency_hz for generator sin: expected >= 0, got: {}",
            frequencyHz));
    }
    if(durationMs < 0) {
        throw std::runtime_error(std::format(
            "Wrong duration_ms for generator sin: expected >= 0, got: {}",
            durationMs));
    }
    return new SinGenFilter(frequencyHz, durationMs);
}

IFilter* amGeneratorCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.params.size() != 6) {
        throw std::runtime_error(
            "Wrong args count for generator am: expected amplitude carrier_hz "
            "modulation_hz depth duration_ms");
    }
    double amplitude = 0;
    double carrierHz = 0;
    double modulationHz = 0;
    double depth = 0;
    double durationMs = 0;
    try {
        amplitude = std::stod(filterDescriptor.params[1]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting amplitude argument of generator am");
    }
    try {
        carrierHz = std::stod(filterDescriptor.params[2]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting carrier_hz argument of generator am");
    }
    try {
        modulationHz = std::stod(filterDescriptor.params[3]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting modulation_hz argument of generator am");
    }
    try {
        depth = std::stod(filterDescriptor.params[4]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting depth argument of generator am");
    }
    try {
        durationMs = std::stod(filterDescriptor.params[5]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting duration_ms argument of generator am");
    }
    if(amplitude < 0 || amplitude > 1) {
        throw std::runtime_error(std::format(
            "Wrong amplitude for generator am: expected 0..1, got: {}",
            amplitude));
    }
    if(carrierHz < 0) {
        throw std::runtime_error(std::format(
            "Wrong carrier_hz for generator am: expected >= 0, got: {}",
            carrierHz));
    }
    if(modulationHz < 0) {
        throw std::runtime_error(std::format(
            "Wrong modulation_hz for generator am: expected >= 0, got: {}",
            modulationHz));
    }
    if(depth < 0 || depth > 1) {
        throw std::runtime_error(std::format(
            "Wrong depth for generator am: expected 0..1, got: {}", depth));
    }
    if(durationMs < 0) {
        throw std::runtime_error(std::format(
            "Wrong duration_ms for generator am: expected >= 0, got: {}",
            durationMs));
    }
    return new AmSinGenFilter(amplitude, carrierHz, modulationHz, depth,
                              durationMs);
}

IFilter* fmGeneratorCreator(const FilterDescriptor& filterDescriptor) {
    if(filterDescriptor.params.size() != 6) {
        throw std::runtime_error(
            "Wrong args count for generator fm: expected amplitude carrier_hz "
            "modulation_hz deviation_hz duration_ms");
    }
    double amplitude = 0;
    double carrierHz = 0;
    double modulationHz = 0;
    double deviationHz = 0;
    double durationMs = 0;
    try {
        amplitude = std::stod(filterDescriptor.params[1]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting amplitude argument of generator fm");
    }
    try {
        carrierHz = std::stod(filterDescriptor.params[2]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting carrier_hz argument of generator fm");
    }
    try {
        modulationHz = std::stod(filterDescriptor.params[3]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting modulation_hz argument of generator fm");
    }
    try {
        deviationHz = std::stod(filterDescriptor.params[4]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting deviation_hz argument of generator fm");
    }
    try {
        durationMs = std::stod(filterDescriptor.params[5]);
    }
    catch(std::exception& exception) {
        throw std::runtime_error(
            "Error converting duration_ms argument of generator fm");
    }
    if(amplitude < 0 || amplitude > 1) {
        throw std::runtime_error(std::format(
            "Wrong amplitude for generator fm: expected 0..1, got: {}",
            amplitude));
    }
    if(carrierHz < 0) {
        throw std::runtime_error(std::format(
            "Wrong carrier_hz for generator fm: expected >= 0, got: {}",
            carrierHz));
    }
    if(modulationHz <= 0) {
        throw std::runtime_error(std::format(
            "Wrong modulation_hz for generator fm: expected > 0, got: {}",
            modulationHz));
    }
    if(deviationHz < 0) {
        throw std::runtime_error(std::format(
            "Wrong deviation_hz for generator fm: expected >= 0, got: {}",
            deviationHz));
    }
    if(durationMs < 0) {
        throw std::runtime_error(std::format(
            "Wrong duration_ms for generator fm: expected >= 0, got: {}",
            durationMs));
    }
    return new FmSinGenFilter(amplitude, carrierHz, modulationHz, deviationHz,
                              durationMs);
}