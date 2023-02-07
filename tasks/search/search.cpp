#include "search.h"
#include <set>
#include <map>
#include <iostream>
#include <cmath>

struct MyComp {
    bool operator()(const std::string_view& a, const std::string_view& b) const {
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

bool ResComp(const std::pair<double, size_t>& lhs, const std::pair<double, size_t>& rhs) {
    return lhs.first > rhs.first;
}

using STRINGMAP = std::map<size_t, std::string_view>;
using QUERY = std::map<std::string_view, std::set<size_t>, MyComp>;
using MYMAP = std::map<size_t, std::pair<std::map<std::string_view, int, MyComp>, int>>;

QUERY FillQuery(std::string_view query) {
    QUERY query_set;
    std::string word;
    bool flag = true;
    size_t word_start_index = 0;
    size_t len_word = 0;
    for (size_t i = 0; i < query.size(); ++i) {
        if (std::isalpha(query[i])) {
            if (flag) {
                word_start_index = i;
                flag = false;
            }
            ++len_word;
        } else if (len_word > 0) {
            query_set[query.substr(word_start_index, len_word)];
            len_word = 0;
            flag = true;
        }
    }
    if (len_word > 0) {
        query_set[query.substr(word_start_index, len_word)];
    }
    return query_set;
}

std::pair<std::pair<MYMAP, STRINGMAP>, size_t> PrepareText(std::string_view text, QUERY& query_set) {
    STRINGMAP dict;
    MYMAP mp;
    bool word_flag = true;
    bool str_flag = true;
    size_t strings_count = 1;
    size_t str_start_index = 0;
    size_t len_str = 0;
    size_t word_start_index = 0;
    size_t len_word = 0;

    for (size_t i = 0; i < text.size(); ++i) {
        if (str_flag) {
            str_start_index = i;
            len_str = 0;
            str_flag = false;
        }

        ++len_str;

        if (std::isalpha(text[i])) {

            if (word_flag) {
                word_start_index = i;
                word_flag = false;
            }
            ++len_word;
        } else if (len_word > 0) {
            if (query_set.find(text.substr(word_start_index, len_word)) != query_set.end()) {
                ++mp[strings_count].first[text.substr(word_start_index, len_word)];
                query_set[text.substr(word_start_index, len_word)].insert(strings_count);
            }
            ++mp[strings_count].second;
            len_word = 0;
            word_flag = true;
        }
        if (text[i] == '\n') {
            str_flag = true;
            dict[strings_count] = text.substr(str_start_index, len_str - 1);
            ++strings_count;
        }
    }
    if (len_word > 0) {
        if (query_set.find(text.substr(word_start_index, len_word)) != query_set.end()) {
            ++mp[strings_count].first[text.substr(word_start_index, len_word)];
            query_set[text.substr(word_start_index, len_word)].insert(strings_count);
        }
        ++mp[strings_count].second;
    }
    dict[strings_count] = text.substr(str_start_index, len_str);
    return std::make_pair(std::make_pair(mp, dict), strings_count);
}

double CountTf(std::pair<const std::string_view, int>& table, int& total) {
    return static_cast<double>(table.second) / static_cast<double>(total);
}

double CountIdf(std::string_view word, QUERY& query, size_t& str_cnt) {
    return std::log(static_cast<double>(str_cnt) / static_cast<double>(query[word].size()));
}

std::pair<size_t, double> CountTfIdf(std::pair<size_t, std::pair<std::map<std::string_view, int, MyComp>, int>> str,
                                     QUERY& query, size_t str_cnt) {
    double sm_tf_idf = 0;
    for (auto p : str.second.first) {
        sm_tf_idf += CountTf(p, str.second.second) * CountIdf(p.first, query, str_cnt);
    }
    return std::make_pair(str.first, sm_tf_idf);
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::pair<double, size_t>> result;
    std::vector<std::string_view> final;
    QUERY query_set = FillQuery(query);
    std::pair<std::pair<MYMAP, STRINGMAP>, size_t> para = PrepareText(text, query_set);
    for (auto& row : para.first.first) {
        double tfidf = CountTfIdf(std::make_pair(row.first, row.second), query_set, para.second).second;
        if (tfidf > 0) {
            result.push_back(std::make_pair(tfidf, row.first));
        }
        std::sort(result.begin(), result.end(), ResComp);
    }
    for (size_t i = 0; i < results_count; ++i) {
        final.push_back(para.first.second[result[i].second]);
    }
    return final;
}
