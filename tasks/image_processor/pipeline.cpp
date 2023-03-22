#include "pipeline.h"

Pipeline::Pipeline(const std::vector<FilterDescriptors>& descriptors) : descriptors_(descriptors) {
}

std::vector<std::shared_ptr<BasicFilter>> Pipeline::GetPipeline() {
    std::vector<std::shared_ptr<BasicFilter>> pipeline;
    FilterProducing filter_producer;
    for (const auto& i : descriptors_) {
        ProducedFilter produced_filter = filter_producer.GetFilter(i);
        std::shared_ptr<BasicFilter> filter(produced_filter(i));
        pipeline.push_back(filter);
    }
    return pipeline;
}
