#pragma once

#include "ifilter.hpp"

class TimestretchFilter: public IFilter {
public:
    TimestretchFilter(double factor);
    void apply(Waveform* sound) override;

private:
    double _factor;
};
