#pragma once

#include "filters/ifilter.hpp"
#include "parsing/filter_descriptor.hpp"
#include <memory>

std::unique_ptr<IFilter> amplFilterCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> normalizeFilterCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> silenceFilterCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> timestretchFilterCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> lowpassFilterCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> sinGeneratorCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> amGeneratorCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> fmGeneratorCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> reverseFilterCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> repeatFilterCreator(const FilterDescriptor& filterDescriptor);
std::unique_ptr<IFilter> fadeFilterCreator(const FilterDescriptor& filterDescriptor);
