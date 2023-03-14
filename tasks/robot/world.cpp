#include "world.h"

World::World(const Topology& topology, Point start, Point end)
    : topology_(topology), curr_pos_(start), start_(start), end_(end) {
}

std::unordered_map<Point, Topology::Distance, HashPoint> World::Lookup() const {
    std::unordered_map<Point, Topology::Distance, HashPoint> nbr;
    for (auto p : this->topology_.GetNeighbours(this->curr_pos_)) {
        nbr[p] = this->topology_.MeasureDistance(p, this->end_);
    }
    return nbr;
}

const Point& World::GetStart() const {
    return this->start_;
}

const Point& World::GetEnd() const {
    return this->end_;
}

const Point& World::GetCurrentPosition() const {
    return this->curr_pos_;
}

void World::Move(const Point& to) {
    auto v = topology_.GetNeighbours(curr_pos_);
    if (std::find(v.begin(), v.end(), to) != v.end()) {
        curr_pos_ = to;
    } else {
        throw IllegalMoveException();
    }
}
