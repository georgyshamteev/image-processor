#include "topology.h"
#include <deque>
#include <unordered_set>

struct HashPoint {
    auto operator()(const Point& p) const {
        return std::hash<size_t>{}(p.y) ^ std::hash<size_t>{}(p.x);
    }
};

Topology::Field::Field(std::vector<std::vector<bool>> field) {
    field_ = field;
}

Topology::Distance Topology::MeasureDistance(const Point& from, const Point& to) const {
    if (to == from) {
        return 0;
    }
    std::unordered_set<Point, HashPoint> used;
    std::deque<std::pair<Point, size_t>> curr;
    curr.push_back({from, 0});
    used.insert(from);
    while (!curr.empty()) {
        if (curr[0].first == to) {
            return static_cast<Distance>(curr[0].second);
        }
        auto nbr = GetNeighbours(curr[0].first);
        for (auto p : nbr) {
            auto tmp = used.find(p);
            if (tmp == used.end()) {
                used.insert(p);
                curr.push_back({p, curr[0].second + 1});
            }
        }
        curr.pop_front();
    }

    return Topology::UNREACHABLE;
}
