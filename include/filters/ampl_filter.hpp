#pragma once

#include "ifilter.hpp"

class AmplFilter : public IFilter {
public:
    AmplFilter(double factor);
    void apply(Waveform* sound) override;
private:
    double _factor;
};