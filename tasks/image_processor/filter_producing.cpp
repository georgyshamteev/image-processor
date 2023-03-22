#include "filter_producing.h"
#include <string>

//// MAKE FUNCTIONS

BasicFilter* MakeCrop(const FilterDescriptors& fd) {
    if (fd.parameters.size() != 2) {
        throw std::invalid_argument("Wrong number of arguments. Crop only takes 2 arguments.");
    }
    const std::string width = {fd.parameters[0].begin(), fd.parameters[0].end()};
    const std::string height = {fd.parameters[1].begin(), fd.parameters[1].end()};
    return new Crop(std::stoll(width), std::stoll(height));
}

BasicFilter* MakeGrayScale(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Grayscale doesn`t take any arguments. Consider deleting all arguments.");
    }
    return new Grayscale;
}

BasicFilter* MakeNegative(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Negative doesn`t take any arguments. Consider deleting all arguments.");
    }
    return new Negative;
}

BasicFilter* MakeSharpening(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Sharpening doesn`t take any arguments. Consider deleting all arguments.");
    }
    return new Sharpening;
}

BasicFilter* MakeEdgeDetection(const FilterDescriptors& fd) {
    if (fd.parameters.size() != 1) {
        throw std::invalid_argument("Wrong number of arguments. EdgeDetection only takes 1 argument.");
    }
    const std::string threshold = {fd.parameters[0].begin(), fd.parameters[0].end()};
    return new EdgeDetection(std::stod(threshold));
}

BasicFilter* MakeGaussianBlur(const FilterDescriptors& fd) {
    return nullptr;
}

//// CREATING MAP

FilterProducing::FilterProducing() {
    pipeline_["crop"] = &MakeCrop;
    pipeline_["gs"] = &MakeGrayScale;
    pipeline_["neg"] = &MakeNegative;
    pipeline_["sharp"] = &MakeSharpening;
    pipeline_["edge"] = &MakeEdgeDetection;
}

//// GET FUNCTION

ProducedFilter FilterProducing::GetFilter(const FilterDescriptors& fd) {
    return pipeline_[fd.name];
}
