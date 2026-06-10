#pragma once

#include "abstract_generator_filter.hpp"

class FmSinGenFilter: public AbstractGeneratorFilter<FmSinGenFilter> {
public:
    FmSinGenFilter(double amplitude, double carrierHz, double modulationHz, double deviationHz, double durationMs);
    int16_t computeSample(double sampleSec) const;

private:
    double _amplitude;
    double _carrierHz;
    double _modulationHz;
    double _deviationHz;
};
