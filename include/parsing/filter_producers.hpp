#pragma once

#include "filters/ifilter.hpp"
#include "parsing/filter_descriptor.hpp"

IFilter* amplFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* normalizeFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* silenceFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* timestretchFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* lowpassFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* sinGeneratorCreator(const FilterDescriptor& filterDescriptor);
IFilter* amGeneratorCreator(const FilterDescriptor& filterDescriptor);
IFilter* fmGeneratorCreator(const FilterDescriptor& filterDescriptor);
