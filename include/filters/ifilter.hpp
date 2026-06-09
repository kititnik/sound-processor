#pragma once

#include "waveform.hpp"

class IFilter {
public:
    virtual ~IFilter() {}
    virtual void apply(Waveform* sound) = 0;
};
