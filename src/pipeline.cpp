#include "pipeline.hpp"
#include "loggers/logger.hpp"
#include <cstddef>
#include <string>

void Pipeline::addFilter(std::unique_ptr<IFilter> filter) {
    _filters.push_back(std::move(filter));
}

void Pipeline::apply(Waveform* waveform) {
    for(size_t i = 0; i < _filters.size(); i++) {
        Logger::log("Applying filter " + std::to_string(i + 1) + "/" + std::to_string(_filters.size()));
        _filters[i]->apply(waveform);
    }
}

size_t Pipeline::getFilterCount() const {
    return _filters.size();
}
