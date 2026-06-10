#pragma once

#include "filters/ifilter.hpp"
#include "parsing/filter_descriptor.hpp"
#include <functional>
#include <map>
#include <string>

using FilterProducer = std::function<IFilter*(const FilterDescriptor&)>;

class FilterRegistry {
public:
    void add(const std::string& name, const FilterProducer& producer);
    const FilterProducer* find(const std::string& name) const;

private:
    std::map<std::string, FilterProducer> _producers;
};
