#include "word2vec.h"

#include <map>
#include <vector>

int64_t DotProduct(const std::vector<int>& a, const std::vector<int>& b) {
    int64_t sm = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sm += static_cast<int64_t>(a[i]) * static_cast<int64_t>(b[i]);
    }
    return sm;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> result;
    if (words.size() < 2) {
        return result;
    }
    int64_t maximum = DotProduct(vectors[0], vectors[1]);
    std::map<std::string, std::int64_t> mp;

    for (size_t i = 1; i < words.size(); ++i) {
        int64_t dot_prod = DotProduct(vectors[0], vectors[i]);
        mp[words[i]] = dot_prod;
        if (dot_prod > maximum) {
            maximum = dot_prod;
        }
    }
    for (const auto& item : mp) {
        if (item.second == maximum) {
            result.push_back(item.first);
        }
    }

    return result;
}
