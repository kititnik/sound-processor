#include "filters/repeat_filter.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

RepeatFilter::RepeatFilter(size_t count): _count(count) {}

void RepeatFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }
    size_t originalSize = sound->size();
    std::vector<int16_t> original(originalSize);
    for(size_t i = 0; i < originalSize; i++) {
        original[i] = sound->getSample(i);
    }
    sound->resize(originalSize * _count);
    for(size_t rep = 1; rep < _count; rep++) {
        for(size_t i = 0; i < originalSize; i++) {
            sound->setSample(rep * originalSize + i, original[i]);
        }
    }
}
