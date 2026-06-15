#pragma once

#include "ifilter.hpp"

class ReverseFilter: public IFilter {
public:
    ReverseFilter() = default;
    void apply(Waveform* sound) override;
};
