#include "planar_topology.h"

std::vector<Point> PlanarTopology::GetNeighbours(const Point& point) const {
    auto f = GetField();
    std::vector<Point> ret;
    int64_t y = static_cast<int64_t>(point.y);
    int64_t x = static_cast<int64_t>(point.x);
    if (y >= 1) {
        if (!f.field_[y - 1][x]) {
            ret.push_back(Point{point.x, point.y - 1});
        }
    }
    if (y + 1 < static_cast<int64_t>(f.GetSize().first)) {
        if (!f.field_[y + 1][x]) {
            ret.push_back(Point{point.x, point.y + 1});
        }
    }
    if (x >= 1) {
        if (!f.field_[y][x - 1]) {
            ret.push_back(Point{point.x - 1, point.y});
        }
    }
    if (x + 1 < static_cast<int64_t>(f.GetSize().second)) {
        if (!f.field_[y][x + 1]) {
            ret.push_back(Point{point.x + 1, point.y});
        }
    }

    return ret;
}