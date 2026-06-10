#pragma once

#include "filters/ifilter.hpp"
#include <cstddef>
#include <memory>
#include <vector>

class Pipeline {
public:
    void addFilter(std::unique_ptr<IFilter> filter);
    void apply(Waveform* waveform);
    size_t getFilterCount() const;

private:
    std::vector<std::unique_ptr<IFilter>> _filters;
};
