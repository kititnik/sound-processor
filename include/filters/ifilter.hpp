#pragma once

#include "waveform.hpp"

// Base interface for all audio filters
class IFilter {
public:
    IFilter() = default;
    virtual ~IFilter() = default;
    IFilter(const IFilter&) = delete;
    IFilter& operator=(const IFilter&) = delete;
    IFilter(IFilter&&) = default;
    IFilter& operator=(IFilter&&) = default;
    virtual void apply(Waveform* sound) = 0;
};
