#include <map>

#include "admission.h"

bool MyComparator(const Applicant*& lhv, const Applicant*& rhv) {
    return std::tie(rhv->points, lhv->student.birth_date.year, lhv->student.birth_date.month,
                    lhv->student.birth_date.day, lhv->student.name) <
           std::tie(lhv->points, rhv->student.birth_date.year, rhv->student.birth_date.month,
                    rhv->student.birth_date.day, rhv->student.name);
}

void SortStudents(std::vector<const Applicant*>& students) {
    std::sort(students.begin(), students.end(), MyComparator);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    AdmissionTable result;
    std::vector<const Applicant*> students;
    for (const Applicant& app : applicants) {
        students.push_back(&app);
    }
    SortStudents(students);
    std::map<std::string, size_t> universities_map;
    for (const University& item : universities) {
        universities_map[item.name] = item.max_students;
    }
    for (const Applicant*& pupil : students) {
        const Student* p = &pupil->student;
        for (const std::string& vuz : pupil->wish_list) {
            if (universities_map[vuz] > 0) {
                result[vuz].push_back(p);
                universities_map[vuz] -= 1;
                break;
            }
        }
    }
    return result;
}
