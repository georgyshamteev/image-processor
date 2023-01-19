#include "password.h"

bool ValidatePassword(const std::string& password) {
    const int lower_bound = 8;
    const int upper_bound = 14;
    int lower = 0;
    int upper = 0;
    int nums = 0;
    int other = 0;
    const int lowerchar = 33;
    const int upperchar = 126;

    if (lower_bound > password.size() || password.size() > upper_bound) {
        return false;
    }

    for (uint64_t i = 0; i < password.size(); ++i) {
        if (password[i] < lowerchar || password[i] > upperchar) {
            return false;
        }
        if (islower(password[i])) {
            lower = 1;
        } else if (isupper(password[i])) {
            upper = 1;
        } else if (isdigit(password[i])) {
            nums = 1;
        } else {
            other = 1;
        }
    }
    if (lower + upper + nums + other < 3) {
        return false;
    }

    return true;
}
