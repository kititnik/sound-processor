#pragma once

#include <string>
#include "parsing/filter_registry.hpp"

class GeneratorFilterCreator {
public:
    void addGeneratorProducer(const std::string& filterName, const FilterProducer& filterProducer);
    IFilter* operator()(const FilterDescriptor& filterDescriptor) const;
private:
    FilterRegistry _filterRegistry;
};