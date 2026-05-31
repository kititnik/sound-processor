#pragma once

#include "ifilter.hpp"

class LowpassFilter : public IFilter {
public:
    LowpassFilter(size_t windowSize);
    void apply(Waveform* sound) override;
private:
    size_t _windowSize;
};
