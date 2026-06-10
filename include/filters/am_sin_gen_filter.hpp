#pragma once

#include "abstract_generator_filter.hpp"

class AmSinGenFilter: public AbstractGeneratorFilter<AmSinGenFilter> {
public:
    AmSinGenFilter(double amplitude, double carrierHz, double modulationHz, double depth, double durationMs);
    int16_t computeSample(double sampleSec) const;

private:
    double _amplitude;
    double _carrierHz;
    double _modulationHz;
    double _depth;
};
