#include "unixpath.h"

std::string UnixPath::ProcessPath(std::string_view str) {
    std::string s;
    std::string curr;
    std::string result;

    for (const char& ch : str) {
        if (ch == '/') {
            if (s == ".") {

            } else if (s == "..") {
                if (!initial_dir_.empty()) {
                    initial_dir_.pop_back();
                }
            } else if (s.empty()) {

            } else {
                initial_dir_.push_back(s);
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
            if (!initial_dir_.empty()) {
                initial_dir_.pop_back();
            }
        } else {
            initial_dir_.push_back(s);
        }
    }

    if (!initial_dir_.empty()) {
        for (std::string& str1 : initial_dir_) {
            result.push_back('/');
            result.append(str1);
        }
    } else {
        result.push_back('/');
    }
    return result;
}

void UnixPath::ProcessChanged(std::string_view str) {
    changed_dir_.clear();
    std::string s;
    std::string curr;
    std::string result;

    for (const char& ch : str) {
        if (ch == '/') {
            if (s == ".") {

            } else if (s == "..") {
                if (!changed_dir_.empty()) {
                    changed_dir_.pop_back();
                }
            } else if (s.empty()) {

            } else {
                changed_dir_.push_back(s);
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
            if (!changed_dir_.empty()) {
                changed_dir_.pop_back();
            }
        } else {
            changed_dir_.push_back(s);
        }
    }
}

UnixPath::UnixPath(std::string_view initial_dir) {
    curr_dir_ = ProcessPath(initial_dir);
}

std::string NormalizePath(std::string current_working_dir, std::string path) {
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

void UnixPath::ChangeDirectory(std::string_view path) {
    std::string path_new = static_cast<std::string>(path);
    curr_dir_ = NormalizePath(curr_dir_, path_new);
    ProcessChanged(curr_dir_);
}
std::string UnixPath::GetAbsolutePath() const {
    return curr_dir_;
}
std::string UnixPath::GetRelativePath() const {
    size_t ptr = 0;
    std::string result;
    while (ptr < initial_dir_.size()) {
        if (initial_dir_[ptr] != changed_dir_[ptr]) {
            break;
        }
        ++ptr;
    }
    size_t diff = initial_dir_.size() - ptr;

    if (diff == 0) {
        result.push_back('.');
    } else {
        for (size_t i = 0; i < diff; ++i) {
            result += ("..");
        }
    }
    for (size_t i = ptr; i < changed_dir_.size(); ++i) {
        result.push_back('/');
        result += (changed_dir_[i]);
    }

    return result;
}
