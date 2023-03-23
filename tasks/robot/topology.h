#pragma once

#include "point.h"
#include <vector>

class Topology {
public:
    using Distance = ssize_t;

    virtual std::vector<Point> GetNeighbours(const Point& point) const = 0;
    Distance MeasureDistance(const Point& from, const Point& to) const;

    constexpr static const Distance UNREACHABLE = -1;

    class Field {
    public:
        explicit Field(std::vector<std::vector<bool>> field);
        std::pair<size_t, size_t> GetSize() const {
            return {field_.size(), field_[0].size()};
        }

    public:
        std::vector<std::vector<bool>> field_;
    };

    explicit Topology(std::vector<std::vector<bool>> v) : game_field_(Field(v)) {
        game_field_ = Field(v);
    }

    Field GetField() const {
        return game_field_;
    }

private:
    Field game_field_;
};
