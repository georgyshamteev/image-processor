#pragma once

#include <set>
#include <map>
#include <string_view>
#include <vector>
#include <iostream>

struct MyComp {
    bool operator()(std::string_view a, std::string_view b) const {
        size_t n = std::min(a.size(), b.size());
        for (size_t i = 0; i < n; ++i) {
            if (tolower(a[i]) == tolower(b[i])) {
                continue;
            } else {
                return tolower(a[i]) < tolower(b[i]);
            }
        }
        return a.size() < b.size();
    }
};

using QUERY = std::set<std::string_view, MyComp>;

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;

private:
    std::map<size_t, std::string_view> num_2_str_;
    std::map<size_t, std::pair<std::map<std::string_view, int64_t, MyComp>, int64_t>> count_words_in_str_;
    std::map<std::string_view, std::set<size_t>, MyComp> count_total_words_;
    QUERY FillQuery(std::string_view query) const;
    long double CountTf(std::string_view word, size_t string_number) const;
    long double CountIdf(std::string_view word) const;
};
