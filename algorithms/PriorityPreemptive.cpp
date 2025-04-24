#include "scheduler.h"

void runPriorityPreemptive() {
    Process* selected = nullptr; // Để trỏ đến tiến trình được chọn từ waitingList
    
    if (!waitingList.empty()) { // Nếu có tiến trình trong hàng đợi
        vector<Process*> temp;
        // Đưa toàn bộ hàng đợi vào vector để chọn
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
        selected = *bestIt;
        temp.erase(bestIt);
        // Trả lại các tiến trình còn lại vào hàng đợi
        for (Process* p : temp) {
            waitingList.push(p);
        }
    }
    if (!runningProcess) {  // Nếu không có tiến trình nào đang chạy
        if (selected) {     // Nhưng có tiến trình mới đến
            runningProcess = selected;
            if (runningProcess->start_time == -1) {
                runningProcess->start_time = current_time;
            }
            runningProcess->remaining_time -= UNIT_MS;
            printGantt('|'); // Tiến trình mới bắt đầu chạy
            if (runningProcess->remaining_time == 0) {
                runningProcess->completion_time = current_time + UNIT_MS;
                runningProcess = nullptr;
            }
        }
        else {              // Không có gì trong waitingList và runningProcess
            printGantt('-'); // Không có gì để chạy
        }
    }
    else if (selected && selected->priority < runningProcess->priority) {
        // Hoặc có tiến trình đang chạy nhưng có tiến trình mới đến có priority nhỏ hơn
        runningProcess->time_in_waiting_list = current_time; // Cập nhật thời gian vào hàng đợi
        waitingList.push(runningProcess); // Trả lại tiến trình cũ vào hàng đợi
        runningProcess = selected; // Chọn tiến trình mới
        if (runningProcess->start_time == -1) {
            runningProcess->start_time = current_time;
        }
        runningProcess->remaining_time -= UNIT_MS;
        printGantt('|'); // Tiến trình mới bắt đầu chạy
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    } 
    else {
        // Tiến trình đang chạy, không có tiến trình mới đến hoặc tiến trình mới có priority lớn hơn
        if (selected) {
            waitingList.push(selected);
        } // Trả lại tiến trình mới vào hàng đợi
        runningProcess->remaining_time -= UNIT_MS;
        printGantt('#');

        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    }
}
