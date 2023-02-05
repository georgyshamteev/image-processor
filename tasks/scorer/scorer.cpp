#include "scorer.h"
#include <map>

bool EventComp(const Event* lhv, const Event* rhv) {
    return lhv->time < rhv->time;
}

void SortEvents(std::vector<const Event*>& events) {
    std::sort(events.begin(), events.end(), EventComp);
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable score_table;

    std::map<const StudentName, std::map<const TaskName, std::pair<bool, bool>>> mp;  // [1, 0]

    std::vector<const Event*> ptrs;

    for (const Event& event : events) {
        if (event.time <= score_time) {
            ptrs.push_back(&event);
        }
    }
    SortEvents(ptrs);

    for (const Event* event : ptrs) {
        if (event->event_type == EventType::CheckFailed) {
            mp[event->student_name][event->task_name].first = false;
        } else if (event->event_type == EventType::CheckSuccess) {
            mp[event->student_name][event->task_name].first = true;
        } else if (event->event_type == EventType::MergeRequestOpen) {
            mp[event->student_name][event->task_name].second = true;
        } else if (event->event_type == EventType::MergeRequestClosed) {
            mp[event->student_name][event->task_name].second = false;
        }
    }

    for (std::pair<const StudentName, std::map<const TaskName, std::pair<bool, bool>>>& student : mp) {
        for (std::pair<const TaskName, std::pair<bool, bool>>& task : student.second) {
            if (task.second.first && !task.second.second) {
                score_table[student.first].insert(task.first);
            }
        }
    }
    return score_table;
}
