#ifndef CPP_HSE_FILTERS_H
#define CPP_HSE_FILTERS_H

#include <vector>
#include "bmp.h"

class BasicFilter {
public:
    virtual void ApplyFilter(Bitmap& bmp) = 0;
};

class Crop : BasicFilter {
public:
    Crop(size_t width, size_t height);
    void ApplyFilter(Bitmap& bmp);

private:
    size_t width_;
    size_t height_;
};

class Grayscale : BasicFilter {
public:
    void ApplyFilter(Bitmap& bmp) override;

private:
    const double r_coeff_ = 0.299;
    const double g_coeff_ = 0.587;
    const double b_coeff_ = 0.114;
};

class Negative : BasicFilter {
public:
    void ApplyFilter(Bitmap& bmp) override;
private:
    const u_char pxsize_ = 255;
};

class Sharpening : BasicFilter {
public:
    void ApplyFilter(Bitmap& bmp) override;
private:
    const std::vector<int> kernel_ = {0, -1, 0, -1, 5, -1, 0, -1, 0};
};

class EdgeDetection : BasicFilter {
public:
    EdgeDetection(double threshold);
    void ApplyFilter(Bitmap& bmp) override;
private:
    const std::vector<int> kernel_ = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    const double threshold_;
};

#endif  // CPP_HSE_FILTERS_H
