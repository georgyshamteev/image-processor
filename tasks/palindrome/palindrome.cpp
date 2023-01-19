#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    uint64_t r = str.size() - 1;
    for (uint64_t l = 0; l < str.size(); ++l) {
        if (str[l] == ' ') {
            continue;
        }
        while (str[r] == ' ' and r > 0) {
            --r;
        }
        if (str[l] != str[r]) {
            return false;
        }
        --r;
    }
    return true;
}
