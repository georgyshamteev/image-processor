#pragma once

#include <string>
#include <string_view>
#include <deque>

class UnixPath {
public:
    UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::deque<std::string> initial_dir_;
    std::string curr_dir_;
    std::deque<std::string> changed_dir_;
    std::string ProcessPath(std::string_view str);
    void ProcessChanged(std::string_view str);
};
