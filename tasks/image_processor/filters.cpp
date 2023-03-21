#include "filters.h"
#include "vector"

//// CAST_FUNC

void CastRgb(double r, double g, double b, Bitmap::Pixel& px) {
    px.b = static_cast<char>(b);
    px.g = static_cast<char>(g);
    px.r = static_cast<char>(r);
}

//// APPLY MATRIX

std::vector<Bitmap::Pixel> GetNeighbours(size_t ii, size_t jj, Bitmap& bmp) {
    std::vector<Bitmap::Pixel> result;
    ssize_t i = static_cast<ssize_t>(ii);
    ssize_t j = static_cast<ssize_t>(jj);
    const ssize_t lower_bound = 0;
    for (int h = -1; h < 2; ++h) {
        for (int w = -1; w < 2; ++w) {
            result.emplace_back(bmp(std::min(lower_bound, std::max(static_cast<ssize_t>(bmp.GetRowsNum()), i + h)),
                                    std::min(lower_bound, std::max(static_cast<ssize_t>(bmp.GetColsNum()), j + w))));
        }
    }
    return result;
}

template <typename T>
void ApplyMatrix(Bitmap& bmp, const std::vector<T>& kernel) {
    const double upper_bound = 255;
    TMatrix<Bitmap::Pixel> new_bmp(bmp.GetRowsNum(), bmp.GetColsNum());

    for (size_t i = 0; i < bmp.GetRowsNum(); ++i) {
        for (size_t j = 0; j < bmp.GetColsNum(); ++j) {
            std::vector<Bitmap::Pixel> nbrs = GetNeighbours(i, j, bmp);
            T res_r = 0;
            T res_g = 0;
            T res_b = 0;
            for (size_t idx = 0; idx < nbrs.size(); ++idx) {
                res_r += static_cast<double>(nbrs[idx].r) / upper_bound * kernel[idx];
                res_g += static_cast<double>(nbrs[idx].g) / upper_bound * kernel[idx];
                res_b += static_cast<double>(nbrs[idx].b) / upper_bound * kernel[idx];
            }
            new_bmp(i, j).r = static_cast<u_char>(res_r);
            new_bmp(i, j).g = static_cast<u_char>(res_g);
            new_bmp(i, j).b = static_cast<u_char>(res_b);
        }
    }
    // might be leak here ??
    bmp = new_bmp;
}

//// CROP

Crop::Crop(size_t width, size_t height) {
    width_ = width;
    height_ = height;
}

void Crop::ApplyFilter(Bitmap& bmp) {
    bmp.Resize(height_, width_);
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

//// Sharpening

void Sharpening::ApplyFilter(Bitmap& bmp) {
    ApplyMatrix(bmp, kernel_);
}

//// Edge Detection

void EdgeDetection::ApplyFilter(Bitmap& bmp) {
    const u_char upper_bound = 255;
    Grayscale gs = Grayscale();
    gs.ApplyFilter(bmp);
    ApplyMatrix(bmp, kernel_);
    for (size_t i = 0; i < bmp.GetRowsNum(); ++i) {
        for (size_t j = 0; j < bmp.GetColsNum(); ++j) {
            if (bmp(i, j).r > threshold_) {
                bmp(i, j) = Bitmap::Pixel{upper_bound, upper_bound, upper_bound};
            } else {
                bmp(i, j) = Bitmap::Pixel{0, 0, 0};
            }
        }
    }
}
