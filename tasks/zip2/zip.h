#pragma once

#include <iterator>

template <typename Iterator1, typename Iterator2>
class Zipped {
public:
    Zipped(Iterator1 iter1_begin, Iterator2 iter2_begin, Iterator1 iter1_end, Iterator2 iter2_end) {
        seq1_begin_ = iter1_begin;
        seq2_begin_ = iter2_begin;
        auto it1 = iter1_begin;
        auto it2 = iter2_begin;
        while ((it1 != iter1_end) && (it2 != iter2_end)) {
            ++it1;
            ++it2;
        }
        seq1_end_ = it1;
        seq2_end_ = it2;
    }

    class Iter {
    public:
        Iter(Iterator1 it1, Iterator2 it2) {
            it1_ = it1;
            it2_ = it2;
        }
        auto operator*() const {
            return make_pair(*it1_, *it2_);
        }

        void operator++() {
            ++it1_;
            ++it2_;
        }

        bool operator!=(const Iter& other) const {
            if ((this->it1_ != other.it1_) || (this->it2_ != other.it2_)) {
                return true;
            }
            return false;
        }

    private:
        Iterator1 it1_;
        Iterator2 it2_;
    };

    Iter begin() const {
        return Iter(seq1_begin_, seq2_begin_);
    }

    Iter end() const {
        return Iter(seq1_end_, seq2_end_);
    }

private:
    Iterator1 seq1_begin_;
    Iterator1 seq1_end_;
    Iterator2 seq2_begin_;
    Iterator2 seq2_end_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Zipped(std::begin(sequence1), std::begin(sequence2), std::end(sequence1), std::end(sequence2));
}
