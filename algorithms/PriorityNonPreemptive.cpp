#include "scheduler.h"

void runPriorityNonPreemptive() {
    sortProcessesByArrivalTime();
    int idx = 0;
    bool justStarted = false;
    runningProcess = nullptr;

    while (true) {
        // Đưa tiến trình mới vào hàng đợi
        while (idx < processes.size() && processes[idx].arrival_time <= current_time) {
            processes[idx].time_in_waiting_list = current_time;
            waitingList.push(&processes[idx]);
            idx++;
        }

        // Nếu không có tiến trình đang chạy, chọn tiến trình có priority cao nhất
        if (runningProcess == nullptr && !waitingList.empty()) {
            Process* selected = nullptr;
            vector<Process*> temp;

            // Tìm tiến trình có priority nhỏ nhất
            while (!waitingList.empty()) {
                Process* p = waitingList.front(); waitingList.pop();
                temp.push_back(p);
                if (selected == nullptr || p->priority < selected->priority) {
                    selected = p;
                }
            }

            // Đưa lại các tiến trình (trừ tiến trình được chọn) vào hàng đợi
            for (Process* p : temp) {
                if (p != selected) waitingList.push(p);
            }

            runningProcess = selected;
            if (runningProcess->start_time == -1) {
                runningProcess->start_time = current_time;
            }
            justStarted = true;
        }

        // Thực thi tiến trình hiện tại
        if (runningProcess != nullptr) {
            printGantt(justStarted ? '|' : '#');
            justStarted = false;

            runningProcess->remaining_time -= UNIT_MS;
            if (runningProcess->remaining_time <= 0) {
                runningProcess->completion_time = current_time + UNIT_MS;
                runningProcess = nullptr;
            }
        } else {
            printGantt('-');
        }

        printWaitingList(waitingList);
        sleepMS(REFRESH_MS);
        current_time += UNIT_MS;

        if (idx >= processes.size() && waitingList.empty() && runningProcess == nullptr) break;
    }
}