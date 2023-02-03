#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> dq;
    std::vector<std::string> result;
    for (const StudentAction& student : student_actions) {
        if (student.side == Side::Top) {
            dq.push_front(student.name);
        } else {
            dq.push_back(student.name);
        }
    }
    for (const size_t& query : queries) {
        result.push_back(dq[query - 1]);
    }
    return result;
}
