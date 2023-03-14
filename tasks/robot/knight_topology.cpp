#include "knight_topology.h"

std::vector<Point> KnightTopology::GetNeighbours(const Point& point) const {
    auto f = GetField();
    std::vector<Point> ret;
    auto y_len = game_field_.GetSize().first;
    auto x_len = game_field_.GetSize().second;

    std::vector<int> v1{1, 2, -1, 2, 1, -2, -1, -2};
    std::vector<int> v2{2, 1, 2, -1, -2, 1, -2, -1};

    for (size_t i = 0; i < v1.size(); ++i) {
        if ((static_cast<int64_t>(point.x) >= v1[i] &&
             static_cast<int64_t>(point.x) < static_cast<int64_t>(v1[i] + x_len)) &&
            (static_cast<int64_t>(point.y) >= v2[i] &&
             static_cast<int64_t>(point.y) < static_cast<int64_t>(v2[i] + y_len))) {
            if (!f.field_[point.y - v2[i]][point.x - v1[i]]) {
                ret.push_back(Point{point.x - v1[i], point.y - v2[i]});
            }
        }
    }
    return ret;
}
