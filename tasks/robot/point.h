#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

struct Point {
    size_t x = 0;
    size_t y = 0;

    bool operator==(const Point& p2) const {
        return (this->x == p2.x && this->y == p2.y);
    }
};

template <>
struct std::hash<Point> {
    std::size_t operator()(const Point& p) const {
        return std::hash<size_t>{}(p.y) ^ std::hash<size_t>{}(p.x);
    }
};