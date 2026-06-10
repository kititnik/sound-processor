#pragma once

#include "ifilter.hpp"
#include "waveform.hpp"
#include <stdexcept>

template <typename Filter> class AbstractGeneratorFilter: public IFilter {
public:
    void apply(Waveform* sound) override {
        if(sound == nullptr) {
            throw std::runtime_error("Waveform* sound is nullptr");
        }
        size_t sampleCount = Waveform::msToSamples(_durationMs);
        sound->resize(sampleCount);
        for(size_t i = 0; i < sampleCount; i++) {
            double sampleSec = Waveform::samplesToMs(i) / 1000.0;
            sound->setSample(i, static_cast<Filter*>(this)->computeSample(sampleSec));
        }
    }

protected:
    AbstractGeneratorFilter(double durationMs): _durationMs(durationMs) {}

private:
    double _durationMs;
};
