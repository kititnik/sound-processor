#pragma once

#include "waveform.hpp"

class IFilter {
public:
    IFilter() = default;
    virtual ~IFilter() = default;
    IFilter(const IFilter&) = delete;
    IFilter& operator=(const IFilter&) = delete;
    virtual void apply(Waveform* sound) = 0;
};
