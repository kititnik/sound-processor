#pragma once

#include "abstract_generator_filter.hpp"

class FmSinGenFilter: public AbstractGeneratorFilter {
public:
    FmSinGenFilter(double amplitude, double carrierHz, double modulationHz,
                   double deviationHz, double durationMs);

protected:
    int16_t computeSample(double sampleSec) const override;

private:
    double _amplitude;
    double _carrierHz;
    double _modulationHz;
    double _deviationHz;
};
