#include "poly.h"
#include <cmath>
#include <sstream>

Poly::Poly(std::initializer_list<int64_t> lst) {
    size_t cnt = 0;
    for (auto item : lst) {
        if (item > 0) {
            coefs_[cnt] = item;
        }
        ++cnt;
    }
}

Poly::Poly(std::initializer_list<std::pair<size_t, int64_t>> lst) {
    for (auto item : lst) {
        if (item.second != 0) {
            coefs_[item.first] = item.second;
        }
    }
}

Poly::Poly() {
}

int64_t Poly::operator()(int64_t num) const {
    int64_t res = 0;
    for (auto i : coefs_) {
        res += i.second * static_cast<int64_t>(std::pow(num, i.first));
    }
    return res;
}

bool Poly::operator==(const Poly& other) const {
    if (this->coefs_.size() != other.coefs_.size()) {
        return false;
    }
    for (auto i : this->coefs_) {
        auto a = other.coefs_.find(i.first);
        if (a == other.coefs_.end() or a->second != i.second) {
            return false;
        }
    }
    return true;
}

Poly Poly::operator-() const {
    Poly temp_pol;
    for (auto i : coefs_) {
        temp_pol.coefs_[i.first] = -i.second;
    }
    return temp_pol;
}

Poly Poly::operator-(const Poly& other) const {
    Poly temp_pol;
    temp_pol.coefs_ = this->coefs_;
    for (auto i : other.coefs_) {
        temp_pol.coefs_[i.first] -= i.second;
        if (temp_pol.coefs_[i.first] == 0) {
            temp_pol.coefs_.erase(i.first);
        }
    }
    return temp_pol;
}
void Poly::operator=(const Poly& other) {
    this->coefs_ = other.coefs_;
}

Poly Poly::operator+(const Poly& other) const {
    Poly temp_pol;
    temp_pol.coefs_ = this->coefs_;
    for (auto i : other.coefs_) {
        temp_pol.coefs_[i.first] += i.second;
        if (temp_pol.coefs_[i.first] == 0) {
            temp_pol.coefs_.erase(i.first);
        }
    }
    return temp_pol;
}

Poly Poly::operator+=(const Poly& other) {
    for (auto i : other.coefs_) {
        this->coefs_[i.first] += i.second;
        if (this->coefs_[i.first] == 0) {
            this->coefs_.erase(i.first);
        }
    }
    return *this;
}

Poly Poly::operator-=(const Poly& other) {
    for (auto i : other.coefs_) {
        this->coefs_[i.first] -= i.second;
        if (this->coefs_[i.first] == 0) {
            this->coefs_.erase(i.first);
        }
    }
    return *this;
}

Poly Poly::operator*(const Poly& other) const {
    Poly temp_poly;
    for (auto i : this->coefs_) {
        for (auto j : other.coefs_) {
            temp_poly.coefs_[i.first + j.first] += i.second * j.second;
            if (temp_poly.coefs_[i.first + j.first] == 0) {
                temp_poly.coefs_.erase(i.first + j.first);
            }
        }
    }
    return temp_poly;
}

Poly Poly::operator*=(const Poly& other) {
    for (auto i : this->coefs_) {
        for (auto j : other.coefs_) {
            this->coefs_[i.first + j.first] += i.second * j.second;
            if (this->coefs_[i.first + j.first] == 0) {
                this->coefs_.erase(i.first + j.first);
            }
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Poly& poly) {
    std::string str;
    if (poly.coefs_.empty()) {
        out << "y = 0";
    } else {
        out << "y = ";
        out << std::to_string(poly.coefs_.begin()->second);
        if (poly.coefs_.begin()->first > 0) {
            out << "x^" << std::to_string(poly.coefs_.begin()->first);
        }

        for (auto it = ++poly.coefs_.begin(); it != poly.coefs_.end(); ++it) {
            if (it->second > 0) {
                out << " + " << std::to_string(it->second);
                if (it->first > 0) {
                    out << "x^" << std::to_string(it->first);
                }
            } else {
                out << " - " << std::to_string(-it->second);
                if (it->first > 0) {
                    out << "x^" << std::to_string(it->first);
                }
            }
        }
    }

    return out;
}
