#include "password.h"

const int LOWER_BOUND = 8;
const int UPPER_BOUND = 14;
const int LOWERCHAR = 33;
const int UPPERCHAR = 126;

bool ValidatePassword(const std::string& password) {
    bool lower = false;
    bool upper = false;
    bool nums = false;
    bool other = false;

    if (LOWER_BOUND > password.size() || password.size() > UPPER_BOUND) {
        return false;
    }

    for (size_t i = 0; i < password.size(); ++i) {
        if (password[i] < LOWERCHAR || password[i] > UPPERCHAR) {
            return false;
        }
        if (islower(password[i])) {
            lower = true;
        } else if (isupper(password[i])) {
            upper = true;
        } else if (isdigit(password[i])) {
            nums = true;
        } else {
            other = true;
        }
    }
    if (lower + upper + nums + other < 3) {
        return false;
    }

    return true;
}
