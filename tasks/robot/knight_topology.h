#pragma once

#include "topology.h"

class KnightTopology : public Topology {
public:
    explicit KnightTopology(std::vector<std::vector<bool>> v) : Topology(v), game_field_(v) {
        game_field_ = Field(v);
    }
    std::vector<Point> GetNeighbours(const Point& point) const;

private:
    Field game_field_;
};
