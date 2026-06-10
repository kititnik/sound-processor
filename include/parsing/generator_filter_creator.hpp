#pragma once

#include "parsing/filter_registry.hpp"
#include <string>

class GeneratorFilterCreator {
public:
    void addGeneratorProducer(const std::string& filterName, const FilterProducer& filterProducer);
    // Dispatches to correct generator subtype based on first param (sin|am|fm)
    IFilter* operator()(const FilterDescriptor& filterDescriptor) const;

private:
    FilterRegistry _filterRegistry;
};
