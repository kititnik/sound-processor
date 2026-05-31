#pragma once

#include "ifilter.hpp"

class NormalizeFilter : public IFilter {
public:
    NormalizeFilter(double peak = 1);
    void apply(Waveform* sound) override;
private:
    double _peak;
};