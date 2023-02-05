#include <deque>
#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string s;
    std::string curr;
    std::deque<std::string> abs_path;
    std::string result;

    if (path[0] == '/') {
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
