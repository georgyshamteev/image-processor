#ifndef CPP_HSE_FILTER_PRODUCING_H
#define CPP_HSE_FILTER_PRODUCING_H

#include "filters.h"
#include "command_parser.h"
#include <map>

using ProducedFilter = BasicFilter* (*)(const FilterDescriptors&);

namespace filter_producing_functions {

BasicFilter* MakeCrop(const FilterDescriptors& fd);
BasicFilter* MakeGrayScale(const FilterDescriptors& fd);
BasicFilter* MakeNegative(const FilterDescriptors& fd);
BasicFilter* MakeSharpening(const FilterDescriptors& fd);
BasicFilter* MakeEdgeDetection(const FilterDescriptors& fd);
BasicFilter* MakeGaussianBlur(const FilterDescriptors& fd);

}  // namespace filter_producing_functions

class FilterProducing {
public:
    FilterProducing();
    ProducedFilter GetFilter(const FilterDescriptors& fd);

private:
    std::map<std::string_view, ProducedFilter> pipeline_;
};

#endif  // CPP_HSE_FILTER_PRODUCING_H
