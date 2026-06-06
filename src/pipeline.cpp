#include "pipeline.hpp"
#include <cstddef>

void Pipeline::addFilter(std::unique_ptr<IFilter> filter) {
    _filters.push_back(std::move(filter));
}

void Pipeline::apply(Waveform* waveform) {
    for(size_t i = 0; i < _filters.size(); i++) {
        _filters[i]->apply(waveform);
    }
}

size_t Pipeline::getFilterCount() {
    return _filters.size();
}