#include "parsing/filter_registry.hpp"

void FilterRegistry::add(const std::string& name, const FilterProducer& producer) {
    _producers.emplace(name, producer);
}

const FilterProducer* FilterRegistry::find(const std::string& name) const {
    auto it = _producers.find(name);
    if(it == _producers.end()) {
        return nullptr;
    }
    return &it->second;
}
