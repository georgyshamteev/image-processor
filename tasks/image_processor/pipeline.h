#ifndef CPP_HSE_PIPELINE_H
#define CPP_HSE_PIPELINE_H

#include "command_parser.h"
#include "filter_producing.h"
#include <memory>

using Pipeline = std::vector<std::unique_ptr<BasicFilter>>;

class PipelineGenerator {
public:
    explicit PipelineGenerator(const std::vector<FilterDescriptors>& descriptors);
    Pipeline CreatePipeline();

private:
    const std::vector<FilterDescriptors> descriptors_;
};

#endif  // CPP_HSE_PIPELINE_H
