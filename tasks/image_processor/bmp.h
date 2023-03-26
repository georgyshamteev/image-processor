#ifndef CPP_HSE_BMP_H
#define CPP_HSE_BMP_H

#include <iostream>
#include <fstream>
#include "tmatrix.h"

class Bitmap {
public:
    Bitmap() = default;

    // структура для хранения заголовка BMP
    struct BmpHeader {
        char signature[2];
        uint32_t file_size;
        uint32_t reserved;
        uint32_t data_offset;
    } __attribute__((__packed__));

    // структура для хранения информации о BMP
    struct BmpInfo {
        uint32_t info_size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bit_count;
        uint32_t compression;
        uint32_t image_size;
        uint32_t x_pixels_per_meter;
        uint32_t y_pixels_per_meter;
        uint32_t colors_used;
        uint32_t colors_important;
    } __attribute__((__packed__));

    struct Pixel {
        u_char r;
        u_char g;
        u_char b;
    };

    void ReadBmp(const std::string& filename);
    void WriteBmp(const std::string& filename);
    void Resize(size_t h, size_t w);
    size_t GetRowsNum() const;
    size_t GetColsNum() const;
    Pixel operator()(size_t i, size_t j) const;
    Pixel& operator()(size_t i, size_t j);
    Bitmap& operator=(const TMatrix<Pixel>&);

    void SetWidthHeight(int32_t w, int32_t h);

private:
    void CheckBMP(const BmpHeader& header, const BmpInfo& info, const std::string& filename);
    TMatrix<Pixel> bmp_ = {};
    BmpHeader bmp_header_;
    BmpInfo bmp_info_;
};

#endif  // CPP_HSE_BMP_H
