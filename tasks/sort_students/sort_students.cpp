#include "sort_students.h"
#include <tuple>

bool DateComparator(const Student &lhv, const Student &rhv) {
    return std::tie(lhv.birth_date.year, lhv.birth_date.month, lhv.birth_date.day, lhv.last_name, lhv.name) <
           std::tie(rhv.birth_date.year, rhv.birth_date.month, rhv.birth_date.day, rhv.last_name, rhv.name);
}

bool NameComparator(const Student &lhv, const Student &rhv) {
    return std::tie(lhv.last_name, lhv.name, lhv.birth_date.year, lhv.birth_date.month, lhv.birth_date.day) <
           std::tie(rhv.last_name, rhv.name, rhv.birth_date.year, rhv.birth_date.month, rhv.birth_date.day);
}

void SortStudents(std::vector<Student> &students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), DateComparator);
    } else {
        std::sort(students.begin(), students.end(), NameComparator);
    }
}
