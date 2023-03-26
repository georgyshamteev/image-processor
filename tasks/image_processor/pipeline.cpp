#include "pipeline.h"

PipelineGenerator::PipelineGenerator(const std::vector<FilterDescriptors>& descriptors) : descriptors_(descriptors) {
}

Pipeline PipelineGenerator::CreatePipeline() {
    Pipeline vector_filters;
    FilterProducing filter_producer;

    for (const auto& i : descriptors_) {
        vector_filters.push_back(filter_producer.GetFilter(i));
    }
    return vector_filters;
}
