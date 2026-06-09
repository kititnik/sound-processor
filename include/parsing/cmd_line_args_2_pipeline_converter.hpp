#pragma once

#include "filters/ifilter.hpp"
#include "parsing/filter_descriptor.hpp"
#include "pipeline.hpp"
#include <map>
#include <string>

using FilterProducer = IFilter* (*)(const FilterDescriptor&);

class CmdLineArgs2PipelineConverter {
public:
    Pipeline
    createPipeline(const std::vector<FilterDescriptor>& filterDescriptors);
    void addFilterProducer(std::string filterName,
                           FilterProducer filterProducer);

private:
    std::map<std::string, FilterProducer> _producers;
};
