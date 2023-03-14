#include "overflow_topology.h"

#include <iostream>

std::vector<Point> OverflowTopology::GetNeighbours(const Point& point) const {
    auto f = GetField();
    std::vector<Point> ret;
    int y_len = static_cast<int>(game_field_.GetSize().first);
    int x_len = static_cast<int>(game_field_.GetSize().second);
    int yy = static_cast<int>(point.y);
    int xx = static_cast<int>(point.x);

    if (!f.field_[(yy - 1 + y_len) % y_len][point.x]) {
        ret.push_back(Point{point.x, static_cast<size_t>((yy - 1 + y_len) % y_len)});
    }
    if (!f.field_[(yy + 1) % y_len][point.x]) {
        ret.push_back(Point{point.x, static_cast<size_t>((yy + 1) % y_len)});
    }
    if (!f.field_[point.y][(xx - 1 + x_len) % x_len]) {
        ret.push_back(Point{static_cast<size_t>((xx - 1 + x_len) % x_len), point.y});
    }
    if (!f.field_[point.y][(xx + 1) % x_len]) {
        ret.push_back(Point{static_cast<size_t>((xx + 1) % x_len), point.y});
    }

    return ret;
}
