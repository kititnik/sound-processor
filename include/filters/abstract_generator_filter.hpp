#pragma once

#include "ifilter.hpp"
#include "waveform.hpp"
#include <stdexcept>

/** Base class for generator filters, subclass must implement computeSample(double sampleSec) */
template <typename Filter> class AbstractGeneratorFilter: public IFilter {
public:
    void apply(Waveform* sound) override {
        if(sound == nullptr) {
            throw std::runtime_error("Waveform* sound is nullptr");
        }
        size_t sampleCount = Waveform::msToSamples(_durationMs);
        // Replaces waveform content with generated signal
        sound->resize(sampleCount);
        for(size_t i = 0; i < sampleCount; i++) {
            // sampleSec is time position in seconds passed to computeSample
            double sampleSec = Waveform::samplesToMs(i) / 1000.0;
            // Calls computeSample on the derived class
            sound->setSample(i, static_cast<Filter*>(this)->computeSample(sampleSec));
        }
    }

protected:
    AbstractGeneratorFilter(double durationMs): _durationMs(durationMs) {}

private:
    double _durationMs;
};
