#include "filters/silence_filter.hpp"
#include "waveform.hpp"
#include <algorithm>
#include <stdexcept>

SilenceFilter::SilenceFilter(const std::string& unit, double start, double end)
    : _unit(unit), _start(start), _end(end) {}

void SilenceFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }
    size_t startSample = 0;
    size_t endSample = 0;
    if(_unit == "sec") {
        startSample = Waveform::secToSamples(_start);
        endSample = Waveform::secToSamples(_end);
    }
    else if(_unit == "ms") {
        startSample = Waveform::msToSamples(_start);
        endSample = Waveform::msToSamples(_end);
    }
    else {
        throw std::runtime_error("Unknown unit for silence filter: " + _unit);
    }
    size_t pos = std::min(startSample, sound->size());
    size_t count = endSample - startSample;
    sound->insert(pos, count, 0);
}
