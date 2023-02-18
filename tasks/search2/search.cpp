#include "search.h"

#include <iostream>
#include <cmath>

bool ResComp(const std::pair<double, size_t>& lhs, const std::pair<double, size_t>& rhs) {
    return lhs.first > rhs.first;
}

QUERY SearchEngine::FillQuery(std::string_view query) const {
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
            query_set.insert(query.substr(word_start_index, len_word));
            len_word = 0;
            flag = true;
        }
    }
    if (len_word > 0) {
        query_set.insert(query.substr(word_start_index, len_word));
    }
    return query_set;
}

void SearchEngine::BuildIndex(std::string_view text) {
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
            ++count_words_in_str_[strings_count].first[text.substr(word_start_index, len_word)];
            ++count_words_in_str_[strings_count].second;
            count_total_words_[text.substr(word_start_index, len_word)].insert(strings_count);
            len_word = 0;
            word_flag = true;
        }
        if (text[i] == '\n') {
            str_flag = true;
            num_2_str_[strings_count] = text.substr(str_start_index, len_str - 1);
            ++strings_count;
        }
    }
    if (len_word > 0) {
        ++count_words_in_str_[strings_count].first[text.substr(word_start_index, len_word)];
        ++count_words_in_str_[strings_count].second;
        count_total_words_[text.substr(word_start_index, len_word)].insert(strings_count);
    }
    num_2_str_[strings_count] = text.substr(str_start_index, len_str);
}

long double SearchEngine::CountTf(std::string_view word, size_t string_number) const {
    auto ptr = count_words_in_str_.find(string_number);
    if (ptr == count_words_in_str_.end()) {
        return 0;
    }
    auto word_ptr = ptr->second.first.find(word);
    if (word_ptr == ptr->second.first.end()) {
        return 0;
    }
    return static_cast<long double>(word_ptr->second) / static_cast<long double>(ptr->second.second);
}

long double SearchEngine::CountIdf(std::string_view word) const {
    auto ptr = count_total_words_.find(word);
    if (ptr == count_total_words_.end()) {
        return 0;
    }
    std::cout << num_2_str_.size() << std::endl;
    return std::log(static_cast<long double>(num_2_str_.size()) / static_cast<double>(ptr->second.size()));
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    std::vector<std::pair<double, size_t>> result;
    std::vector<std::string_view> final;
    QUERY query_set = FillQuery(query);
    if (num_2_str_.empty()) {
        return final;
    }

    for (auto pair : SearchEngine::num_2_str_) {
        long double sm = 0;
        for (auto word : query_set) {
            sm += CountTf(word, pair.first) * CountIdf(word);
        }
        result.push_back(std::make_pair(sm, pair.first));
    }

    std::sort(result.begin(), result.end(), ResComp);
    for (size_t i = 0; i < results_count && i < result.size(); ++i) {
        final.push_back(num_2_str_.at(result[i].second));
    }
    return final;
};