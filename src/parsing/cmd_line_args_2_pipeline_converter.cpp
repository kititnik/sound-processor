#include "parsing/cmd_line_args_2_pipeline_converter.hpp"
#include "filters/ifilter.hpp"
#include "pipeline.hpp"
#include <cstddef>
#include <format>
#include <memory>
#include <stdexcept>

void CmdLineArgs2PipelineConverter::addFilterProducer(
    std::string filterName, FilterProducer filterProducer) {
    _producers.emplace(filterName, filterProducer);
}

Pipeline CmdLineArgs2PipelineConverter::createPipeline(
    const std::vector<FilterDescriptor>& filterDescriptors) const {
    Pipeline pipeline;
    for(size_t i = 0; i < filterDescriptors.size(); i++) {
        auto producersMapIt = _producers.find(filterDescriptors[i].name);
        if(producersMapIt == _producers.end()) {
            throw std::runtime_error(
                std::format("Error creating pipeline. Unknown filter: {}. You "
                            "should register your filter to use it",
                            filterDescriptors[i].name));
        }
        IFilter* filter = producersMapIt->second(filterDescriptors[i]);
        if(filter == nullptr) {
            throw std::runtime_error(std::format(
                "Error creating pipeline: cannot create filter n. {} named {}",
                i, filterDescriptors[i].name));
        }
        pipeline.addFilter(std::unique_ptr<IFilter>(filter));
    }
    return pipeline;
}
