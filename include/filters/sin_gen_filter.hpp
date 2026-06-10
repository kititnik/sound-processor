#pragma once

#include "abstract_generator_filter.hpp"

class SinGenFilter: public AbstractGeneratorFilter<SinGenFilter> {
public:
    SinGenFilter(double frequencyHz, double durationMs);
    int16_t computeSample(double sampleSec) const;

private:
    double _frequencyHz;
};
