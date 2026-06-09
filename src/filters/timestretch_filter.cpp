#include "filters/timestretch_filter.hpp"
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <vector>

TimestretchFilter::TimestretchFilter(double factor): _factor(factor) {}

void TimestretchFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }

    size_t oldSize = sound->size();
    size_t newSize = static_cast<size_t>(std::round(oldSize * _factor));

    std::vector<int16_t> result(newSize);
    for(size_t i = 0; i < newSize; i++) {
        double pos = i / _factor;
        size_t pastIdx = static_cast<size_t>(std::floor(pos));
        double frac = pos - pastIdx;

        if(pastIdx == oldSize - 1) {
            result[i] = sound->getSample(pastIdx);
        }
        else {
            double newValue = sound->getSample(pastIdx) * (1.0 - frac) +
                              sound->getSample(pastIdx + 1) * frac;
            result[i] = static_cast<int16_t>(newValue);
        }
    }

    sound->resize(newSize);
    for(size_t i = 0; i < newSize; i++) {
        sound->setSample(i, result[i]);
    }
}
