#include "filter_pipeline.h"
#include <string>

BasicFilter* Pipeline::MakeCrop(const FilterDescriptors& fd) {
    if (fd.parameters.size() != 2) {
        throw std::invalid_argument("Wrong number of arguments. Crop only takes 2 arguments.");
    }
    const std::string width = {fd.parameters[0].begin(), fd.parameters[0].end()};
    const std::string height = {fd.parameters[1].begin(), fd.parameters[1].end()};
    return new Crop(std::stoi(width), std::stoi(height));
}

BasicFilter* Pipeline::MakeGrayScale(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Grayscale doesn`t take any arguments. Consider deleting all arguments.");
    }
    return new Grayscale;
}

BasicFilter* Pipeline::MakeNegative(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Negative doesn`t take any arguments. Consider deleting all arguments.");
    }
    return new Negative;
}

BasicFilter* Pipeline::MakeSharpening(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Sharpening doesn`t take any arguments. Consider deleting all arguments.");
    }
    return new Sharpening;
}

BasicFilter* Pipeline::MakeEdgeDetection(const FilterDescriptors& fd) {
    if (fd.parameters.size() != 1) {
        throw std::invalid_argument("Wrong number of arguments. EdgeDetection only takes 1 argument.");
    }
    const std::string threshold = {fd.parameters[0].begin(), fd.parameters[0].end()};
    return new EdgeDetection(std::stod(threshold));
}

BasicFilter* Pipeline::MakeGaussianBlur(const FilterDescriptors& fd) {
    return nullptr;
}

Pipeline::Pipeline() {
    pipeline_["crop"] = &Pipeline::MakeCrop;
    pipeline_["gs"] = &Pipeline::MakeGrayScale;
    pipeline_["neg"] = &Pipeline::MakeNegative;
    pipeline_["sharp"] = &Pipeline::MakeSharpening;
    pipeline_["edge"] = &Pipeline::MakeEdgeDetection;

}
