#include "filters/abstract_generator_filter.hpp"
#include <stdexcept>

AbstractGeneratorFilter::AbstractGeneratorFilter(double durationMs)
    : _durationMs(durationMs) {}

void AbstractGeneratorFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }
    size_t sampleCount = Waveform::msToSamples(_durationMs);
    sound->resize(sampleCount);
    for(size_t i = 0; i < sampleCount; i++) {
        double sampleSec = Waveform::samplesToMs(i) / 1000.0;
        sound->setSample(i, computeSample(sampleSec));
    }
}
