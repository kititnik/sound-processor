#pragma once

#include "ifilter.hpp"
#include <cstddef>

class RepeatFilter: public IFilter {
public:
    RepeatFilter(size_t count);
    void apply(Waveform* sound) override;

private:
    size_t _count;
};
