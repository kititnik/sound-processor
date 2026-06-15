#include "filters/fade_filter.hpp"
#include "waveform.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>

FadeFilter::FadeFilter(const std::string& direction, double durationMs)
    : _direction(direction), _durationMs(durationMs) {}

void FadeFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }
    size_t fadeSamples = Waveform::msToSamples(_durationMs);
    if(fadeSamples > sound->size()) {
        throw std::runtime_error("Wrong duration");
    }
    if(fadeSamples <= 1) {
        return;
    }
    double steps = static_cast<double>(fadeSamples - 1);
    if(_direction == "in") {
        for(size_t i = 0; i < fadeSamples; i++) {
            double factor = i / steps;
            double newValue = sound->getSample(i) * factor;
            sound->setSample(i, static_cast<int16_t>(std::clamp(newValue,
                static_cast<double>(std::numeric_limits<int16_t>::min()),
                static_cast<double>(std::numeric_limits<int16_t>::max()))));
        }
    }
    else {
        size_t offset = sound->size() - fadeSamples;
        for(size_t i = 0; i < fadeSamples; i++) {
            double factor = (steps - i) / steps;
            double newValue = sound->getSample(offset + i) * factor;
            sound->setSample(offset + i, static_cast<int16_t>(std::clamp(newValue,
                static_cast<double>(std::numeric_limits<int16_t>::min()),
                static_cast<double>(std::numeric_limits<int16_t>::max()))));
        }
    }
}
