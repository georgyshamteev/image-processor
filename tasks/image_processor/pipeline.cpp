#include "pipeline.h"

Pipeline::Pipeline(const std::vector<FilterDescriptors>& descriptors) : descriptors_(descriptors) {
}

std::vector<std::unique_ptr<BasicFilter>> Pipeline::CreatePipeline() {
    std::vector<std::unique_ptr<BasicFilter>> vector_filters;
    FilterProducing filter_producer;

    for (const auto& i : descriptors_) {
        vector_filters.push_back(filter_producer.GetFilter(i));
    }
    return vector_filters;
}
