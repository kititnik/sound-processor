#pragma once

#include "filters/ifilter.hpp"
#include "parsing/filter_descriptor.hpp"

IFilter* amplFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* normalizeFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* silenceFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* timestretchFilterCreator(const FilterDescriptor& filterDescriptor);
IFilter* lowpassFilterCreator(const FilterDescriptor& filterDescriptor);