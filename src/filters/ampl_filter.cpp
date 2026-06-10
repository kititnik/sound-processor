#include "filters/ampl_filter.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>

AmplFilter::AmplFilter(double factor): _factor(factor) {}

void AmplFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }
    for(size_t i = 0; i < sound->size(); i++) {
        double newSampleValue = sound->getSample(i) * _factor;
        double clampedSampleValue = std::clamp(newSampleValue, static_cast<double>(std::numeric_limits<int16_t>::min()),
                                               static_cast<double>(std::numeric_limits<int16_t>::max()));
        sound->setSample(i, static_cast<int16_t>(clampedSampleValue));
    }
}
