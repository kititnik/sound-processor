#pragma once

#include "ifilter.hpp"
#include "waveform.hpp"

class AbstractGeneratorFilter : public IFilter {
public:
    void apply(Waveform* sound) override;
protected:
    AbstractGeneratorFilter(double durationMs);
    virtual int16_t computeSample(double sampleSec) const = 0;
private:
    double _durationMs;
};