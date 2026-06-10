#include "parsing/generator_filter_creator.hpp"
#include <format>
#include <stdexcept>

void GeneratorFilterCreator::addGeneratorProducer(const std::string& filterName, const FilterProducer& filterProducer) {
    _filterRegistry.add(filterName, filterProducer);
}

IFilter* GeneratorFilterCreator::operator()(const FilterDescriptor& filterDescriptor) const {
    if(filterDescriptor.params.empty()) {
        throw std::runtime_error("Wrong args count for generator filter: "
                                 "expected sin|am|fm as first argument");
    }
    const std::string& type = filterDescriptor.params[0];
    auto producer = _filterRegistry.find(type);
    if(producer == nullptr) {
        throw std::runtime_error(std::format(
            "Unknown generator type: expected sin|am|fm, got: {}", type));
    }
    return (*producer)(filterDescriptor);;
}
