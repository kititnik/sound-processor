#include "filters/normalize_filter.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>

NormalizeFilter::NormalizeFilter(double peak) : _peak(peak) {}

void NormalizeFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }
    int32_t currentPeak = 0;
    for(size_t i = 0; i < sound->size(); i++) {
        int32_t sample = std::abs(sound->getSample(i));
        currentPeak = std::max(sample, currentPeak);
    }
    if(currentPeak == 0) {
        return;
    }
    double scale = _peak * std::numeric_limits<int16_t>::max() / currentPeak;
    for(size_t i = 0; i < sound->size(); i++) {
        double newSampleValue = sound->getSample(i) * scale;
        double clampedSampleValue = std::clamp(newSampleValue, 
            static_cast<double>(std::numeric_limits<int16_t>::min()), 
            static_cast<double>(std::numeric_limits<int16_t>::max()));
        sound->setSample(i, static_cast<int16_t>(clampedSampleValue));
    }
}