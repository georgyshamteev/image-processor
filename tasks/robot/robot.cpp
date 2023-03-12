#include "robot.h"
#include <unordered_set>
#include <deque>

Point Minimum(std::unordered_map<Point, Topology::Distance, HashPoint> mp) {
    Point result;
    const ssize_t high = 1000000000000000000;
    ssize_t min_value = high;
    for (auto i : mp) {
        if (i.second < min_value && i.second > -1) {
            result = i.first;
            min_value = i.second;
        }
    }
    return result;
}

robot::Path robot::FindPath(World& world) {
    auto from = world.GetStart();
    auto to = world.GetEnd();
    std::unordered_set<Point, HashPoint> used;
    std::deque<std::pair<Point, size_t>> curr;
    Path result;
    result.push_back(from);
    while (world.GetCurrentPosition() != to) {
        auto nbrs = world.Lookup();

        bool unr_flag = true;
        for (auto i : nbrs) {
            if (i.second != -1) {
                unr_flag = false;
            }
        }
        if (unr_flag) {
            return {};
        }

        auto key_point = Minimum(nbrs);
        result.push_back(key_point);
        world.Move(key_point);
    }
    return result;
}