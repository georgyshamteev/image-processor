#pragma once

#include <string>

class CowString {
public:
    explicit CowString(std::string_view value);
    CowString(const CowString& rhs);
    CowString(CowString&& rhs);
    CowString(){};
    ~CowString();

    class MyString {
    public:
        explicit MyString(std::string_view value);
        explicit MyString(char* ch);
        ~MyString();
        void Inc();
        void Dec();
        bool Empty() const;
        char* GetStr() const;
        void SetStr(char* ch);
        size_t GetCnt() const;

    private:
        size_t cnt_ = 0;
        char* str_;
    };

    class MyIterator {
    public:
        MyIterator(CowString& link, size_t idx);
        MyIterator& operator=(const char& ch);
        MyIterator& operator=(const char&& ch);

        class Proxy {
        public:
            Proxy(char* ch, CowString& dad);
            Proxy& operator=(const char& ch);
            char operator*() const;
            bool operator==(const char& ch) const;
            bool operator==(Proxy p) const;
            operator char() const;

        private:
            char* proxy_ch_;
            CowString& cow_link_;
        };

        Proxy operator*();
        bool operator==(const char& ch) const;
        bool operator==(MyIterator mi);
        MyIterator& operator++();

    private:
        CowString& cow_link_;
        size_t index_;
    };

    class ConstMyIterator {
    public:
        ConstMyIterator(const CowString& link, size_t idx);

        class Proxy {
        public:
            Proxy(char* ch, const CowString& dad);
            char operator*() const;
            bool operator==(const char& ch) const;
            bool operator==(Proxy p) const;
            operator char() const;

        private:
            char* proxy_ch_;
            const CowString& cow_link_;
        };

        Proxy operator*();
        bool operator==(const char& ch) const;
        bool operator==(ConstMyIterator cmi);
        ConstMyIterator& operator++();

    private:
        const CowString& cow_link_;
        size_t index_;
    };

    CowString& operator=(const CowString& rhs);
    CowString& operator=(CowString&& rhs);

    char* GetData() const;

    MyIterator operator[](size_t idx);
    MyIterator At(size_t idx);

    ConstMyIterator operator[](size_t idx) const;
    ConstMyIterator At(size_t idx) const;

    CowString operator+(const CowString& other) const;
    CowString operator+(std::string_view other) const;
    CowString& operator+=(const CowString& other);
    CowString& operator+=(std::string_view other);
    bool operator==(const CowString& other) const;
    bool operator==(std::string_view other) const;

    MyIterator begin();
    MyIterator end();

    ConstMyIterator begin() const;
    ConstMyIterator end() const;

protected:
    MyString* mystr_;
};
