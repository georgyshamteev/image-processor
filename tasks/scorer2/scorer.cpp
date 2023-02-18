#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName &student_name, const TaskName &task_name) {
    map_of_students_[student_name][task_name].first = false;
}

void Scorer::OnCheckSuccess(const StudentName &student_name, const TaskName &task_name) {
    map_of_students_[student_name][task_name].first = true;
}

void Scorer::OnMergeRequestOpen(const StudentName &student_name, const TaskName &task_name) {
    map_of_students_[student_name][task_name].second = true;
}

void Scorer::OnMergeRequestClosed(const StudentName &student_name, const TaskName &task_name) {
    map_of_students_[student_name][task_name].second = false;
}

void Scorer::Reset() {
    map_of_students_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    ScoreTable score_table;
    for (const auto &student : map_of_students_) {
        for (const auto &task : student.second) {
            if (task.second.first && !task.second.second) {
                score_table[student.first].insert(task.first);
            }
        }
    }
    return score_table;
}