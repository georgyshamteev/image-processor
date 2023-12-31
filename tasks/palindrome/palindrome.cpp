#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t r = str.size() - 1;
    for (size_t l = 0; l < str.size(); ++l) {
        if (str[l] == ' ') {
            continue;
        }
        while (str[r] == ' ' && r > 0) {
            --r;
        }
        if (str[l] != str[r]) {
            return false;
        }
        --r;
    }
    return true;
}