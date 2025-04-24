#include "scheduler.h"

void runSJF() {
    // Nếu đang có tiến trình chạy
    if (runningProcess) {
        runningProcess->remaining_time -= UNIT_MS;
        printGantt('#');
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    }
    // Nếu không có tiến trình nào đang chạy, chọn tiến trình có burst_time nhỏ nhất
    else if (!waitingList.empty()) {
        // Đưa tất cả tiến trình trong hàng đợi vào một vector tạm
        vector<Process*> temp;
        while (!waitingList.empty()) {
            temp.push_back(waitingList.front());
            waitingList.pop();
        }

        // Tìm tiến trình có burst_time nhỏ nhất
        auto shortestIt = min_element(temp.begin(), temp.end(), [](Process* a, Process* b) {
            return a->burst_time < b->burst_time;
        });

        // Đưa tiến trình được chọn ra khỏi vector và quay lại hàng đợi
        runningProcess = *shortestIt;
        temp.erase(shortestIt);

        for (Process* p : temp) {
            waitingList.push(p);
        }

        // Bắt đầu chạy tiến trình được chọn
        runningProcess->remaining_time -= UNIT_MS;
        printGantt('|');
        if (runningProcess->start_time == -1) {
            runningProcess->start_time = current_time;
        }
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    }
    // Không có tiến trình chạy và waitingList rỗng
    else {
        printGantt('-');
    }
}
