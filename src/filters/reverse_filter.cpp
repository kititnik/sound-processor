#include "filters/reverse_filter.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

void ReverseFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }
    size_t n = sound->size();
    std::vector<int16_t> samples(n);
    for(size_t i = 0; i < n; i++) {
        samples[i] = sound->getSample(i);
    }
    for(size_t i = 0; i < n; i++) {
        sound->setSample(i, samples[n - 1 - i]);
    }
}
