#ifndef CPP_HSE_FILTER_PRODUCING_H
#define CPP_HSE_FILTER_PRODUCING_H

#include "filters.h"
#include "command_parser.h"
#include <map>
#include <memory>

namespace filter_producing_functions {

std::unique_ptr<BasicFilter> MakeCrop(const FilterDescriptors& fd);
std::unique_ptr<BasicFilter> MakeGrayScale(const FilterDescriptors& fd);
std::unique_ptr<BasicFilter> MakeNegative(const FilterDescriptors& fd);
std::unique_ptr<BasicFilter> MakeSharpening(const FilterDescriptors& fd);
std::unique_ptr<BasicFilter> MakeEdgeDetection(const FilterDescriptors& fd);
std::unique_ptr<BasicFilter> MakeGaussianBlur(const FilterDescriptors& fd);
std::unique_ptr<BasicFilter> MakeSobel(const FilterDescriptors& fd);

}  // namespace filter_producing_functions

class FilterProducing {
    using Signature = std::unique_ptr<BasicFilter>(const FilterDescriptors&);
    using ProducedFilter = Signature*;

public:
    FilterProducing();
    std::unique_ptr<BasicFilter> GetFilter(const FilterDescriptors& fd);

private:
    std::map<std::string_view, ProducedFilter> pipeline_;
};

#endif  // CPP_HSE_FILTER_PRODUCING_H
