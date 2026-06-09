#pragma once

#include "abstract_generator_filter.hpp"

class SinGenFilter : public AbstractGeneratorFilter {
public:
    SinGenFilter(double frequencyHz, double durationMs);
protected:
    int16_t computeSample(double sampleSec) const override;
private:
    double _frequencyHz;
};
