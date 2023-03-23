#include <cmath>
#include "filters.h"
#include "vector"

namespace {
//// CAST_FUNC

void CastRgb(double r, double g, double b, Bitmap::Pixel& px) {
    px.b = static_cast<u_char>(b);
    px.g = static_cast<u_char>(g);
    px.r = static_cast<u_char>(r);
}

//// APPLY MATRIX

std::vector<Bitmap::Pixel> GetNeighbours(size_t ii, size_t jj, Bitmap& bmp, int32_t size) {
    std::vector<Bitmap::Pixel> result;
    ssize_t i = static_cast<ssize_t>(ii);
    ssize_t j = static_cast<ssize_t>(jj);
    ssize_t height = static_cast<ssize_t>(bmp.GetRowsNum());
    ssize_t width = static_cast<ssize_t>(bmp.GetColsNum());
    const ssize_t lower = 0;
    for (int h = -size / 2; h <= size / 2; ++h) {
        for (int w = -size / 2; w <= size / 2; ++w) {
            result.emplace_back(
                bmp(std::max(lower, std::min(height - 1, i + h)), std::max(lower, std::min(width - 1, j + w))));
        }
    }
    return result;
}

template <typename T>
void ApplyMatrix(Bitmap& bmp, const std::vector<T>& kernel) {
    const double upper = 255;
    const double lower = 0;
    TMatrix<Bitmap::Pixel> new_bmp(bmp.GetRowsNum(), bmp.GetColsNum());
    int32_t size = std::sqrt(kernel.size());
    for (size_t i = 0; i < bmp.GetRowsNum(); ++i) {
        for (size_t j = 0; j < bmp.GetColsNum(); ++j) {
            std::vector<Bitmap::Pixel> nbrs = GetNeighbours(i, j, bmp, size);
            double res_r = 0;
            double res_g = 0;
            double res_b = 0;
            for (size_t idx = 0; idx < nbrs.size(); ++idx) {
                res_r += static_cast<double>(nbrs[idx].r) * kernel[idx];
                res_g += static_cast<double>(nbrs[idx].g) * kernel[idx];
                res_b += static_cast<double>(nbrs[idx].b) * kernel[idx];
            }
            new_bmp(i, j).r = static_cast<u_char>((std::max(lower, std::min(upper, res_r))));
            new_bmp(i, j).g = static_cast<u_char>((std::max(lower, std::min(upper, res_g))));
            new_bmp(i, j).b = static_cast<u_char>((std::max(lower, std::min(upper, res_b))));
        }
    }
    for (size_t i = 0; i < bmp.GetRowsNum(); ++i) {
        for (size_t j = 0; j < bmp.GetColsNum(); ++j) {
            bmp(i, j) = new_bmp(i, j);
        }
    }
}
}  // namespace
//// CROP

Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}

void Crop::ApplyFilter(Bitmap& bmp) {
    if (height_ > bmp.GetRowsNum()) {
        height_ = bmp.GetRowsNum();
    }
    if (width_ > bmp.GetColsNum()) {
        width_ = bmp.GetColsNum();
    }
    bmp.Resize(height_, width_);
    bmp.SetWidthHeight(static_cast<int32_t>(width_), static_cast<int32_t>(height_));
}
Crop::~Crop() {
}

//// GRAYSCALE

void Grayscale::ApplyFilter(Bitmap& bmp) {
    for (size_t i = 0; i < bmp.GetRowsNum(); ++i) {
        for (size_t j = 0; j < bmp.GetColsNum(); ++j) {
            Bitmap::Pixel& elem = bmp(i, j);
            double new_value = b_coeff_ * elem.b + g_coeff_ * elem.g + r_coeff_ * elem.r;
            CastRgb(new_value, new_value, new_value, elem);
        }
    }
}
Grayscale::~Grayscale() {
}

//// NEGATIVE

void Negative::ApplyFilter(Bitmap& bmp) {
    for (size_t i = 0; i < bmp.GetRowsNum(); ++i) {
        for (size_t j = 0; j < bmp.GetColsNum(); ++j) {
            Bitmap::Pixel& elem = bmp(i, j);
            elem.r = pxsize_ - elem.r;
            elem.g = pxsize_ - elem.g;
            elem.b = pxsize_ - elem.b;
        }
    }
}
Negative::~Negative() {
}

//// Sharpening

void Sharpening::ApplyFilter(Bitmap& bmp) {
    ApplyMatrix(bmp, kernel_);
}

Sharpening::~Sharpening() {
}

//// Edge Detection

void EdgeDetection::ApplyFilter(Bitmap& bmp) {
    const u_char upper_bound = 255;
    Grayscale gs = Grayscale();
    gs.ApplyFilter(bmp);
    ApplyMatrix(bmp, kernel_);
    for (size_t i = 0; i < bmp.GetRowsNum(); ++i) {
        for (size_t j = 0; j < bmp.GetColsNum(); ++j) {
            auto value = std::min(1.0, std::max(0.0, (static_cast<double>(bmp(i, j).r)) / upper_bound));
            if (value > threshold_) {
                bmp(i, j) = Bitmap::Pixel{upper_bound, upper_bound, upper_bound};
            } else {
                bmp(i, j) = Bitmap::Pixel{0, 0, 0};
            }
        }
    }
}
EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}
EdgeDetection::~EdgeDetection() {
}

//// GAUSSIAN BLUR

GaussianBlur::~GaussianBlur() {
}

GaussianBlur::GaussianBlur(double sigma) : sigma_(std::ceil(sigma)) {
    const size_t gauss_size = static_cast<size_t>(std::ceil(6 * sigma_)) + 1;
    int32_t half_gauss_size = gauss_size / 2;

    coeffs_.resize(gauss_size);

    for (int32_t i = 0; i <= half_gauss_size; ++i) {
        double numenator = std::exp(-static_cast<double>(i * i) / (sigma_ * sigma_ * 2));
        double denumenator = std::sqrt(2 * M_PI * sigma_ * sigma_);
        coeffs_[half_gauss_size - i] = coeffs_[half_gauss_size + i] = numenator / denumenator;
    }
}

void GaussianBlur::ApplyFilter(Bitmap& bmp) {
    const int32_t half_gauss_size = static_cast<int32_t>(coeffs_.size() / 2);

    TMatrix<Bitmap::Pixel> new_bitmap;
    new_bitmap.Resize(bmp.GetColsNum(), bmp.GetRowsNum());

    for (size_t w = 0; w < bmp.GetColsNum(); ++w) {
        for (size_t h = 0; h < bmp.GetRowsNum(); ++h) {
            Bitmap::Pixel& pixel = new_bitmap(h, w);
            double r = 0;
            double g = 0;
            double b = 0;
            double sum = 0;
            for (int diff = -half_gauss_size; diff <= half_gauss_size; ++diff) {
                int32_t yy =
                    std::max(0, std::min(static_cast<int32_t>(bmp.GetRowsNum() - 1), static_cast<int32_t>(h) + diff));
                sum += coeffs_[diff + half_gauss_size];
                r += static_cast<double>(bmp(yy, w).r) * coeffs_[diff + half_gauss_size];
                g += static_cast<double>(bmp(yy, w).g) * coeffs_[diff + half_gauss_size];
                b += static_cast<double>(bmp(yy, w).b) * coeffs_[diff + half_gauss_size];
            }
            pixel.r = static_cast<u_char>(r / sum);
            pixel.g = static_cast<u_char>(g / sum);
            pixel.b = static_cast<u_char>(b / sum);
        }
    }

    for (size_t h = 0; h < bmp.GetRowsNum(); ++h) {
        for (size_t w = 0; w < bmp.GetColsNum(); ++w) {

            Bitmap::Pixel& pixel = bmp(h, w);
            pixel.r = pixel.g = pixel.b = 0;

            double sum = 0;
            double r = 0;
            double g = 0;
            double b = 0;

            for (int diff = -half_gauss_size; diff <= half_gauss_size; ++diff) {
                int32_t xx =
                    std::max(0, std::min(static_cast<int32_t>(bmp.GetColsNum() - 1), static_cast<int32_t>(w) + diff));
                sum += coeffs_[diff + half_gauss_size];
                r += static_cast<double>(new_bitmap(h, xx).r) * coeffs_[diff + half_gauss_size];
                g += static_cast<double>(new_bitmap(h, xx).g) * coeffs_[diff + half_gauss_size];
                b += static_cast<double>(new_bitmap(h, xx).b) * coeffs_[diff + half_gauss_size];
            }

            pixel.r = static_cast<u_char>(r/sum);
            pixel.g = static_cast<u_char>(g/sum);
            pixel.b = static_cast<u_char>(b/sum);
        }
    }
}
