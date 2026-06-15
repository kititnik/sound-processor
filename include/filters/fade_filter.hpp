#pragma once

#include "ifilter.hpp"
#include <string>

class FadeFilter: public IFilter {
public:
    FadeFilter(const std::string& direction, double durationMs);
    void apply(Waveform* sound) override;

private:
    std::string _direction;
    double _durationMs;
};
