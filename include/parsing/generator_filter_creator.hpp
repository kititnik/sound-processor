#pragma once

#include "parsing/filter_registry.hpp"
#include <string>

class GeneratorFilterCreator {
public:
    void addGeneratorProducer(const std::string& filterName, const FilterProducer& filterProducer);
    IFilter* operator()(const FilterDescriptor& filterDescriptor) const;

private:
    FilterRegistry _filterRegistry;
};
