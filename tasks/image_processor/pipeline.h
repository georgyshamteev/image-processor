#ifndef CPP_HSE_PIPELINE_H
#define CPP_HSE_PIPELINE_H

#include "command_parser.h"
#include "filter_producing.h"
#include <memory>

class Pipeline {
public:
    explicit Pipeline(const std::vector<FilterDescriptors>& descriptors);
    std::vector<std::shared_ptr<BasicFilter>> GetPipeline();

private:
    const std::vector<FilterDescriptors> descriptors_;
};

#endif  // CPP_HSE_PIPELINE_H
