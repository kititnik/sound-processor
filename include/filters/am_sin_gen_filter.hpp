#pragma once

#include "abstract_generator_filter.hpp"

class AmSinGenFilter: public AbstractGeneratorFilter {
public:
    AmSinGenFilter(double amplitude, double carrierHz, double modulationHz,
                   double depth, double durationMs);

protected:
    int16_t computeSample(double sampleSec) const override;

private:
    double _amplitude;
    double _carrierHz;
    double _modulationHz;
    double _depth;
};
