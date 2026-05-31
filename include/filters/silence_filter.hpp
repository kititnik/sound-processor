#pragma once

#include "ifilter.hpp"
#include <string>

class SilenceFilter : public IFilter {
public:
    SilenceFilter(const std::string& unit, double start, double end);
    void apply(Waveform* sound) override;
private:
    std::string _unit;
    double _start;
    double _end;
};
