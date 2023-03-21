#ifndef CPP_HSE_FILTER_PIPELINE_H
#define CPP_HSE_FILTER_PIPELINE_H

#include "filters.h"
#include "command_parser.h"

#include <map>

class Pipeline {
public:
    Pipeline();

    BasicFilter* MakeCrop(const FilterDescriptors& fd);
    BasicFilter* MakeGrayScale(const FilterDescriptors& fd);
    BasicFilter* MakeNegative(const FilterDescriptors& fd);
    BasicFilter* MakeSharpening(const FilterDescriptors& fd);
    BasicFilter* MakeEdgeDetection(const FilterDescriptors& fd);
    BasicFilter* MakeGaussianBlur(const FilterDescriptors& fd);

private:
    std::map<std::string, BasicFilter* (Pipeline::*)(const FilterDescriptors&)> pipeline_;
};

#endif  // CPP_HSE_FILTER_PIPELINE_H
