#include "bmp.h"

//// READ BMP

void Bitmap::ReadBmp(const std::string& filename) {

    std::ifstream file;
    file.open(filename, std::ios_base::in | std::ios_base::binary);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        throw std::runtime_error("Bad file");
    }

    BmpHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    bmp_header_ = header;

    BmpInfo info;
    file.read(reinterpret_cast<char*>(&info), sizeof(info));
    bmp_info_ = info;

    CheckBMP(header, info, filename);

    int32_t width = info.width;
    int32_t height = info.height;

    bmp_.Resize(width, height);

    for (int32_t y = height - 1; y >= 0; --y) {
        for (int32_t x = 0; x < width; ++x) {
            char b = 0;
            char g = 0;
            char r = 0;
            file.read(&b, sizeof(b));
            file.read(&g, sizeof(g));
            file.read(&r, sizeof(r));
            bmp_(y, x) = Pixel{static_cast<u_char>(r), static_cast<u_char>(g), static_cast<u_char>(b)};
        }

        char padding = 0;
        for (size_t i = 0; i < (4 - ((width * sizeof(Pixel)) % 4)) % 4; ++i) {
            file.read(&padding, sizeof(padding));
        }
    }
}

void Bitmap::Resize(size_t h, size_t w) {
    bmp_.Resize(w, h);
}

size_t Bitmap::GetRowsNum() const {
    return bmp_.GetRowsNum();
}

size_t Bitmap::GetColsNum() const {
    return bmp_.GetCollsNum();
}
Bitmap::Pixel Bitmap::operator()(size_t i, size_t j) const {
    return bmp_(i, j);
}
Bitmap::Pixel& Bitmap::operator()(size_t i, size_t j) {
    return bmp_(i, j);
}
Bitmap& Bitmap::operator=(const TMatrix<Pixel>& mat) {
    bmp_ = mat;
    return *this;
}

//// WRITE BMP

void Bitmap::WriteBmp(const std::string& filename) {

    std::ofstream file;
    file.open(filename, std::ios_base::out | std::ios_base::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));

    file.write(reinterpret_cast<char*>(&bmp_info_), sizeof(bmp_info_));

    int32_t width = bmp_info_.width;
    int32_t height = bmp_info_.height;

    for (int32_t y = height - 1; y >= 0; --y) {
        for (int32_t x = 0; x < width; ++x) {

            file.write(reinterpret_cast<char*>(&bmp_(y, x).b), sizeof(bmp_(y, x).b));
            file.write(reinterpret_cast<char*>(&bmp_(y, x).g), sizeof(bmp_(y, x).g));
            file.write(reinterpret_cast<char*>(&bmp_(y, x).r), sizeof(bmp_(y, x).r));
        }

        char padding = 0;
        for (size_t i = 0; i < (4 - ((width * sizeof(Pixel)) % 4)) % 4; ++i) {
            file.write(&padding, sizeof(padding));
        }
    }
}
void Bitmap::SetWidthHeight(int32_t w, int32_t h) {
    bmp_info_.height = h;
    bmp_info_.width = w;
}
void Bitmap::CheckBMP(const Bitmap::BmpHeader& header, const Bitmap::BmpInfo& info, const std::string& filename) {
    const size_t bit_size = 8;

    if (header.signature[0] != 'B' || header.signature[1] != 'M') {
        std::cerr << "Not a BMP file: " << filename << std::endl;
        throw std::runtime_error("Bad file");
    }
    if (info.info_size != sizeof(BmpInfo)) {
        std::cerr << "Invalid BMP format: " << filename << std::endl;
        throw std::runtime_error("Bad file");
    }
    if (info.bit_count != 3 * bit_size) {
        std::cerr << "Only 24-bit BMPs are supported: " << filename << std::endl;
        throw std::runtime_error("Bad file");
    }
    if (info.compression != 0) {
        std::cerr << "Compressed BMPs are not supported: " << filename << std::endl;
        throw std::runtime_error("Bad file");
    }
    if (info.colors_used != 0 || info.colors_important != 0) {
        std::cerr << "BMPs with color tables are not supported: " << filename << std::endl;
        throw std::runtime_error("Bad file");
    }
}
