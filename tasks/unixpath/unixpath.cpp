#include <deque>
#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::deque<std::string> abs_path;
    std::string curr;
    for (const char& ch : current_working_dir) {
        if (ch == '/') {
            if (!curr.empty()) {
                abs_path.push_back(curr);
            }
            curr = "";
        } else {
            curr.push_back(ch);
        }
    }
    if (!curr.empty()) {
        abs_path.push_back(curr);
    }
    std::string s;
    for (const char& ch : path) {
        if (ch == '/') {
            if (s == ".") {

            } else if (s == "..") {
                if (!abs_path.empty()) {
                    abs_path.pop_back();
                }
            } else if (s.empty()) {

            } else {
                abs_path.push_back(s);
            }
            s = "";
        } else if (ch == '.') {
            s.push_back(ch);
        } else {
            s.push_back(ch);
        }
    }
    if (!s.empty()) {
        if (s == ".") {

        } else if (s == "..") {
            if (!abs_path.empty()) {
                abs_path.pop_back();
            }
        } else {
            abs_path.push_back(s);
        }
    }

    std::string result;
    if (!abs_path.empty()) {
        for (std::string& str : abs_path) {
            result.push_back('/');
            result.append(str);
        }
    } else {
        result.push_back('/');
    }

    return result;
}
