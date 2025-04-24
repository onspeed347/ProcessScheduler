#include "scheduler.h"

void runPriorityNonPreemptive() {
    // Nếu có tiến trình đang chạy
    if (runningProcess) {
        runningProcess->remaining_time -= UNIT_MS;
        printGantt('#');
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    }
    // Nếu không có tiến trình chạy, chọn tiến trình có priority nhỏ nhất
    else if (!waitingList.empty()) {
        vector<Process*> temp;
        while (!waitingList.empty()) {
            temp.push_back(waitingList.front());
            waitingList.pop();
        }

        // Chọn tiến trình có priority nhỏ nhất
        auto bestIt = min_element(temp.begin(), temp.end(), [](Process* a, Process* b) {
            if (a->priority != b->priority)
                return a->priority < b->priority;
            return a->arrival_time < b->arrival_time;
        });

        runningProcess = *bestIt;
        temp.erase(bestIt);

        for (Process* p : temp) {
            waitingList.push(p);
        }

        if (runningProcess->start_time == -1) {
            runningProcess->start_time = current_time;
        }

        runningProcess->remaining_time -= UNIT_MS;
        printGantt('|');

        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    }
    else {
        printGantt('-');
    }
}
