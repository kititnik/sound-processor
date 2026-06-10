#pragma once

#include "parsing/filter_descriptor.hpp"
#include "parsing/filter_registry.hpp"
#include "pipeline.hpp"
#include <string>

class CmdLineArgs2PipelineConverter {
public:
    Pipeline createPipeline(const std::vector<FilterDescriptor>& filterDescriptors) const;
    void addFilterProducer(const std::string& filterName, const FilterProducer& filterProducer);

private:
    FilterRegistry _filterRegistry;
};
