#include "cow_string.h"

#include <iostream>
#include <cstring>

CowString::CowString(const CowString& rhs) {
    mystr_ = rhs.mystr_;
    mystr_->Inc();

    //    std::cout << "Copy constructor" << std::endl;
}

CowString::CowString(CowString&& rhs) {
    mystr_ = rhs.mystr_;
    rhs.mystr_ = nullptr;

    //    std::cout << "Move constructor" << std::endl;
}

CowString::CowString(std::string_view value) {
    mystr_ = new MyString(value);
    //    std::cout << "SV created" << std::endl;
}

CowString::~CowString() {
    mystr_->Dec();
    if (mystr_->Empty()) {
        delete mystr_;
    }
    //    std::cout << "Destroyed" << std::endl;
}

CowString& CowString::operator=(const CowString& rhs) {
    if (!mystr_->Empty()) {
        mystr_->Dec();
    }
    if (mystr_->GetCnt() < 1) {
        delete mystr_;
    }
    mystr_ = rhs.mystr_;
    mystr_->Inc();
    //    std::cout << "Copy assigned" << std::endl;
    return *this;
}

CowString& CowString::operator=(CowString&& rhs) {
    if (!mystr_->Empty()) {
        mystr_->Dec();
    }
    if (mystr_->GetCnt() < 1) {
        delete[] mystr_;
    }
    mystr_ = rhs.mystr_;
    rhs.mystr_ = nullptr;
    //    std::cout << "Move assigned" << std::endl;
    return *this;
}

char* CowString::GetData() const {
    return mystr_->GetStr();
}

CowString::MyIterator CowString::operator[](size_t idx) {
    return MyIterator(*this, idx);
}

CowString::MyIterator CowString::At(size_t idx) {
    return MyIterator(*this, idx);
}

CowString CowString::operator+(const CowString& other) const {
    //    std::cout << "cow + cow" << std::endl;
    CowString tmp_str;
    auto ln1 = strlen(mystr_->GetStr());
    auto ln2 = strlen(other.mystr_->GetStr());
    char* str = new char[ln1 + ln2 + 1];
    for (size_t i = 0; i < ln1; ++i) {
        str[i] = mystr_->GetStr()[i];
    }
    for (size_t i = 0; i <= ln2; ++i) {
        str[i + ln1] = other.mystr_->GetStr()[i];
    }
    tmp_str.mystr_ = new MyString(str);
    return tmp_str;
}

CowString& CowString::operator+=(const CowString& other) {
    //    std::cout << "cow += cow" << std::endl;
    auto ln1 = strlen(mystr_->GetStr());
    auto ln2 = strlen(other.mystr_->GetStr());
    char* str = new char[ln1 + ln2 + 1];
    for (size_t i = 0; i < ln1; ++i) {
        str[i] = mystr_->GetStr()[i];
    }
    for (size_t i = 0; i <= ln2; ++i) {
        str[i + ln1] = other.mystr_->GetStr()[i];
    }
    if (mystr_->GetCnt() == 1) {
        mystr_->SetStr(str);
    } else {
        mystr_->Dec();
        mystr_ = new MyString(str);
    }
    return *this;
}

CowString CowString::operator+(std::string_view other) const {
    //    std::cout << "cow + SV" << std::endl;
    CowString tmp_str;
    auto ln1 = strlen(mystr_->GetStr());
    char* str = new char[ln1 + other.size() + 1];
    for (size_t i = 0; i < ln1; ++i) {
        str[i] = mystr_->GetStr()[i];
    }
    for (size_t i = 0; i <= other.size(); ++i) {
        str[i + ln1] = other[i];
    }
    tmp_str.mystr_ = new MyString(str);
    return tmp_str;
}

CowString& CowString::operator+=(std::string_view other) {
    //    std::cout << "cow += SV" << std::endl;
    auto ln1 = strlen(mystr_->GetStr());
    char* str = new char[ln1 + other.size() + 1];
    for (size_t i = 0; i < ln1; ++i) {
        str[i] = mystr_->GetStr()[i];
    }
    for (size_t i = 0; i <= other.size(); ++i) {
        str[i + ln1] = other[i];
    }
    if (mystr_->GetCnt() == 1) {
        mystr_->SetStr(str);
    } else {
        mystr_->Dec();
        mystr_ = new MyString(str);
    }
    return *this;
}

bool CowString::operator==(std::string_view other) const {
    //    std::cout << "SV comparison" << std::endl;
    auto ln = strlen(mystr_->GetStr());
    if (ln != other.size()) {
        return false;
    }
    for (size_t i = 0; i < ln; ++i) {
        if (mystr_->GetStr()[i] != other[i]) {
            return false;
        }
    }
    return true;
}

bool CowString::operator==(const CowString& other) const {
    auto ln1 = strlen(mystr_->GetStr());
    auto ln2 = strlen(other.mystr_->GetStr());
    if (ln1 != ln2) {
        return false;
    }
    for (size_t i = 0; i < ln1; ++i) {
        if (mystr_->GetStr()[i] != other.mystr_->GetStr()[i]) {
            return false;
        }
    }
    return true;
}

CowString::MyIterator CowString::begin() {
    return CowString::MyIterator(*this, 0);
}

CowString::MyIterator CowString::end() {
    auto n = strlen(mystr_->GetStr());
    return CowString::MyIterator(*this, n);
}

CowString::ConstMyIterator CowString::operator[](size_t idx) const {
    return ConstMyIterator(*this, idx);
}

CowString::ConstMyIterator CowString::At(size_t idx) const {
    return ConstMyIterator(*this, idx);
}

CowString::ConstMyIterator CowString::begin() const {
    return CowString::ConstMyIterator(*this, 0);
}
CowString::ConstMyIterator CowString::end() const {
    auto n = strlen(mystr_->GetStr());
    return CowString::ConstMyIterator(*this, n);
}

//// iterators:

CowString::MyIterator::MyIterator(CowString& link, size_t idx) : cow_link_(link) {
    link.mystr_->Inc();
    cow_link_ = link;
    this->cow_link_.mystr_->Dec();
    index_ = idx;
}

CowString::MyIterator& CowString::MyIterator::operator=(const char& ch) {
    **this = ch;
    return *this;
}

CowString::MyIterator& CowString::MyIterator::operator=(const char&& ch) {
    **this = ch;
    return *this;
}

CowString::MyIterator& CowString::MyIterator::operator++() {
    ++index_;
    return *this;
}

bool CowString::MyIterator::operator==(const char& ch) const {
    auto ptr = cow_link_.mystr_->GetStr();
    for (size_t i = 0; i < index_; ++i) {
        ++ptr;
    }
    return *ptr == ch;
}

CowString::MyIterator::Proxy CowString::MyIterator::operator*() {
    auto ptr = cow_link_.mystr_->GetStr();
    for (size_t i = 0; i < index_; ++i) {
        ++ptr;
    }
    return Proxy(ptr, cow_link_);
}
bool CowString::MyIterator::operator==(CowString::MyIterator mi) {
    return **this == *mi;
}

//// const my iterator

CowString::ConstMyIterator::ConstMyIterator(const CowString& link, size_t idx) : cow_link_(link) {
    //    cow_link_ = link;
    index_ = idx;
}

CowString::ConstMyIterator::Proxy CowString::ConstMyIterator::operator*() {
    auto ptr = cow_link_.mystr_->GetStr();
    for (size_t i = 0; i < index_; ++i) {
        ++ptr;
    }
    return Proxy(ptr, cow_link_);
}

bool CowString::ConstMyIterator::operator==(const char& ch) const {
    auto ptr = cow_link_.mystr_->GetStr();
    for (size_t i = 0; i < index_; ++i) {
        ++ptr;
    }
    return *ptr == ch;
}

CowString::ConstMyIterator& CowString::ConstMyIterator::operator++() {
    ++index_;
    return *this;
}
bool CowString::ConstMyIterator::operator==(CowString::ConstMyIterator cmi) {
    return **this == *cmi;
}

//// my string

CowString::MyString::MyString(std::string_view value) {
    char* str = new char[value.size() + 1]();
    for (size_t i = 0; i < value.size(); ++i) {
        str[i] = value[i];
    }
    str[value.size()] = '\0';
    str_ = str;
    ++cnt_;
}

CowString::MyString::~MyString() {
    if (this->GetCnt() <= 1) {
        delete[] str_;
    }
}

void CowString::MyString::Inc() {
    ++cnt_;
}

void CowString::MyString::Dec() {
    --cnt_;
}

bool CowString::MyString::Empty() const {
    if (cnt_ == 0) {
        return true;
    }
    return false;
}
char* CowString::MyString::GetStr() const {
    return str_;
}

CowString::MyString::MyString(char* ch) {
    ++cnt_;
    str_ = ch;
}
size_t CowString::MyString::GetCnt() const {
    return cnt_;
}
void CowString::MyString::SetStr(char* ch) {
    delete[] str_;
    str_ = ch;
}

//// proxy

CowString::MyIterator::Proxy::Proxy(char* ch, CowString& dad) : cow_link_(dad) {
    proxy_ch_ = ch;
    dad.mystr_->Inc();
    cow_link_ = dad;
    this->cow_link_.mystr_->Dec();
}

CowString::MyIterator::Proxy& CowString::MyIterator::Proxy::operator=(const char& ch) {
    if (*proxy_ch_ == ch) {
        return *this;
    }

    if (cow_link_.mystr_->GetCnt() == 1) {
        *proxy_ch_ = ch;
    } else {
        cow_link_.mystr_->Dec();
        auto tmp_char = *proxy_ch_;
        *proxy_ch_ = ch;
        auto ln1 = strlen(cow_link_.mystr_->GetStr());
        auto new_view = new char[ln1 + 1];
        auto copy = new_view;
        auto ptr = cow_link_.mystr_->GetStr();
        while (true) {
            if (*ptr == '\0') {
                break;
            }
            *new_view = *ptr;
            ++ptr;
            ++new_view;
        }
        copy[ln1] = '\0';
        *proxy_ch_ = tmp_char;
        cow_link_.mystr_ = new MyString(copy);
    }
    return *this;
}
char CowString::MyIterator::Proxy::operator*() const {
    return *proxy_ch_;
}
bool CowString::MyIterator::Proxy::operator==(const char& ch) const {
    return *proxy_ch_ == ch;
}
CowString::MyIterator::Proxy::operator char() const {
    return *proxy_ch_;
}
bool CowString::MyIterator::Proxy::operator==(CowString::MyIterator::Proxy p) const {
    return this->proxy_ch_ == p.proxy_ch_;
}

//// const proxy

CowString::ConstMyIterator::Proxy::Proxy(char* ch, const CowString& dad) : cow_link_(dad) {
    proxy_ch_ = ch;
}
char CowString::ConstMyIterator::Proxy::operator*() const {
    return *proxy_ch_;
}
bool CowString::ConstMyIterator::Proxy::operator==(const char& ch) const {
    return *proxy_ch_ == ch;
}
CowString::ConstMyIterator::Proxy::operator char() const {
    return *proxy_ch_;
}
bool CowString::ConstMyIterator::Proxy::operator==(CowString::ConstMyIterator::Proxy p) const {
    return this->proxy_ch_ == p.proxy_ch_;
}
