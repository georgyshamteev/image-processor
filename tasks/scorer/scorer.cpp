#include "scorer.h"
#include <iostream>
#include <map>

bool EventComp(const Event* lhv, const Event* rhv) {
    return lhv->time < rhv->time;
}

void SortEvents(std::vector<const Event*>& events) {
    std::sort(events.begin(), events.end(), EventComp);
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable score_table;

    std::map<const StudentName, std::map<const TaskName, std::array<bool, 2> >> mp; // [1, 0]

    std::vector<const Event*> ptrs;

    for (const Event& event : events) {
        if (event.time <= score_time) {
            ptrs.push_back(&event);
        }
    }
    SortEvents(ptrs);

    for (const Event* event : ptrs) {
        std::cout << event->student_name << std::endl;
        std::cout << event->task_name << std::endl;
        if (event->event_type == EventType::CheckFailed) {
            std::cout << "CheckFailed" << std::endl;
            mp[event->student_name][event->task_name][0] = false;
        } else if (event->event_type == EventType::CheckSuccess) {
            std::cout << "CheckSuccess" << std::endl;

            mp[event->student_name][event->task_name][0] = true;
        } else if (event->event_type == EventType::MergeRequestOpen) {
            std::cout << "OPen" << std::endl;

            mp[event->student_name][event->task_name][1] = true;
        } else if (event->event_type == EventType::MergeRequestClosed) {
            std::cout << "Closed" << std::endl;

            mp[event->student_name][event->task_name][1] = false;
        }
    }

    for (std::pair<const StudentName, std::map<const TaskName, std::array<bool, 2>>>& student : mp) {
        std :: cout << student.first << std::endl;
        for (std::pair<const TaskName, std::array<bool, 2>>& task : student.second) {
            std::cout << task.first << std::endl;
            for (const bool& fl : task.second) {
                std::cout << fl << std::endl;
            }
            if (task.second[0] == 1 && task.second[1] == 0) {
                score_table[student.first].insert(task.first);
            }
        }
    }
    return score_table;
}
