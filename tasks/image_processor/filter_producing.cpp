#include "filter_producing.h"
#include <string>

//// MAKE FUNCTIONS

std::unique_ptr<BasicFilter> MakeCrop(const FilterDescriptors& fd) {
    if (fd.parameters.size() != 2) {
        throw std::invalid_argument("Wrong number of arguments. Crop only takes 2 arguments.");
    }
    const std::string width = {fd.parameters[0].begin(), fd.parameters[0].end()};
    const std::string height = {fd.parameters[1].begin(), fd.parameters[1].end()};
    return std::make_unique<Crop>(std::stoll(width), std::stoll(height));
}

std::unique_ptr<BasicFilter> MakeGrayScale(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Grayscale doesn`t take any arguments. Consider deleting all arguments.");
    }
    return std::make_unique<Grayscale>();
}

std::unique_ptr<BasicFilter> MakeNegative(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Negative doesn`t take any arguments. Consider deleting all arguments.");
    }
    return std::make_unique<Negative>();
}

std::unique_ptr<BasicFilter> MakeSharpening(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Sharpening doesn`t take any arguments. Consider deleting all arguments.");
    }
    return std::make_unique<Sharpening>();
}

std::unique_ptr<BasicFilter> MakeEdgeDetection(const FilterDescriptors& fd) {
    if (fd.parameters.size() != 1) {
        throw std::invalid_argument("Wrong number of arguments. EdgeDetection only takes 1 argument.");
    }
    const std::string threshold = {fd.parameters[0].begin(), fd.parameters[0].end()};
    return std::make_unique<EdgeDetection>(std::stod(threshold));
}

std::unique_ptr<BasicFilter> MakeGaussianBlur(const FilterDescriptors& fd) {
    if (fd.parameters.size() != 1) {
        throw std::invalid_argument("Wrong number of arguments. EdgeDetection only takes 1 argument.");
    }
    const std::string sigma = {fd.parameters[0].begin(), fd.parameters[0].end()};
    return std::make_unique<GaussianBlur>(std::stod(sigma));
}

std::unique_ptr<BasicFilter> MakeSobel(const FilterDescriptors& fd) {
    if (!fd.parameters.empty()) {
        throw std::invalid_argument("Sobel doesn`t take any arguments. Consider deleting all arguments.");
    }
    return std::make_unique<Sobel>();
}

//// CREATING MAP

FilterProducing::FilterProducing() {
    pipeline_["crop"] = &MakeCrop;
    pipeline_["gs"] = &MakeGrayScale;
    pipeline_["neg"] = &MakeNegative;
    pipeline_["sharp"] = &MakeSharpening;
    pipeline_["edge"] = &MakeEdgeDetection;
    pipeline_["blur"] = &MakeGaussianBlur;
    pipeline_["sobel"] = &MakeSobel;
}

//// GET FUNCTION

std::unique_ptr<BasicFilter> FilterProducing::GetFilter(const FilterDescriptors& fd) {
    auto it = pipeline_.find(fd.name);
    if (it == pipeline_.end()) {
        throw std::invalid_argument("wrong filter name");
    }
    return (pipeline_[fd.name])(fd);
}
