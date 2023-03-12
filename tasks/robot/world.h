#pragma once

#include "point.h"
#include "topology.h"

#include <exception>
#include <unordered_map>

struct HashPoint {
    auto operator()(const Point& p) const {
        return std::hash<size_t>{}(p.y) ^ std::hash<size_t>{}(p.x);
    }
};

class World {
public:
    class IllegalMoveException : public std::exception {};

    World(const Topology& topology, Point start, Point end);

    std::unordered_map<Point, Topology::Distance, HashPoint> Lookup() const;

    const Point& GetStart() const;
    const Point& GetEnd() const;
    const Point& GetCurrentPosition() const;

    void Move(const Point& to);

private:
    const Topology& topology_;
    Point curr_pos_;
    Point start_;
    Point end_;
};
