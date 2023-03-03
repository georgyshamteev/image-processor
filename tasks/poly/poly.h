#pragma once

#include <initializer_list>
#include <cstdint>
#include <utility>
#include <map>
#include <sstream>

class Poly {
public:
    Poly();
    Poly(std::initializer_list<int64_t> lst);
    Poly(std::initializer_list<std::pair<size_t, int64_t>> lst);

    int64_t operator()(int64_t num) const;
    bool operator==(const Poly& other) const;
    Poly operator-() const;
    Poly operator-(const Poly& other) const;
    Poly operator+(const Poly& other) const;
    Poly operator+=(const Poly& other);
    Poly operator-=(const Poly& other);
    Poly operator*(const Poly& other) const;
    Poly operator*=(const Poly& other);
    void operator=(const Poly& other);
    friend std::ostream& operator<<(std::ostream& out, const Poly& poly);

    struct MyComp {
        bool operator()(const auto& lhs, const auto& rhs) const {
            return lhs > rhs;
        }
    };

private:
    std::map<size_t, int64_t, MyComp> coefs_;
};
