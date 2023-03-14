#include "checkers_topology.h"
#include <unordered_set>
#include <deque>

struct HashPoint {
    auto operator()(const Point& p) const {
        return std::hash<size_t>{}(p.y) ^ std::hash<size_t>{}(p.x);
    }
};

std::vector<Point> CheckersTopology::GetNeighbours(const Point& point) const {
    auto f = GetField();
    std::vector<Point> ret;
    std::unordered_set<Point, HashPoint> used;
    std::deque<Point> curr;
    auto y_len = game_field_.GetSize().first;
    auto x_len = game_field_.GetSize().second;

    std::vector<int> v1{-1, -1, 1, 1};
    std::vector<int> v2{-1, 1, -1, 1};

    for (size_t i = 0; i < v1.size(); ++i) {
        if ((static_cast<int64_t>(point.x) >= v1[i] &&
             static_cast<int64_t>(point.x) < static_cast<int64_t>(x_len + v1[i])) &&
            (static_cast<int64_t>(point.y) >= v2[i] &&
             static_cast<int64_t>(point.y) < static_cast<int64_t>(y_len + v2[i]))) {

            if (!f.field_[point.y - v2[i]][point.x - v1[i]]) {
                ret.push_back(Point{point.x - v1[i], point.y - v2[i]});
            } else {
                if ((static_cast<int64_t>(point.x) >= v1[i] * 2 &&
                     static_cast<int64_t>(point.x) < static_cast<int64_t>(v1[i] * 2 + x_len)) &&
                    (static_cast<int64_t>(point.y) >= v2[i] * 2 &&
                     static_cast<int64_t>(point.y) < static_cast<int64_t>(v2[i] * 2 + y_len)) &&
                    (!f.field_[point.y - v2[i] * 2][point.x - v1[i] * 2])) {
                    used.insert(Point{point.x - v1[i] * 2, point.y - v2[i] * 2});
                    curr.push_back(Point{point.x - v1[i] * 2, point.y - v2[i] * 2});
                    while (!curr.empty()) {
                        for (size_t j = 0; j < v1.size(); ++j) {
                            if ((static_cast<int64_t>(curr[0].x) >= v1[j] * 2 &&
                                 static_cast<int64_t>(curr[0].x) < static_cast<int64_t>(v1[j] * 2 + x_len)) &&
                                (static_cast<int64_t>(curr[0].y) >= v2[j] * 2 &&
                                 static_cast<int64_t>(curr[0].y) < static_cast<int64_t>(v2[j] * 2 + y_len)) &&
                                (used.find(Point{curr[0].x - v1[j] * 2, curr[0].y - v2[j] * 2}) == used.end()) &&
                                (f.field_[curr[0].y - v2[j]][curr[0].x - v1[j]]) &&
                                (!f.field_[curr[0].y - v2[j] * 2][curr[0].x - v1[j] * 2])) {

                                used.insert(Point{curr[0].x - v1[j] * 2, curr[0].y - v2[j] * 2});
                                curr.push_back(Point{curr[0].x - v1[j] * 2, curr[0].y - v2[j] * 2});
                            }
                        }
                        ret.push_back(curr[0]);
                        curr.pop_front();
                    }
                }
            }
        }
    }
    return ret;
}