#include "scheduler.h"

static int timeSlice = 0; // Đếm thời gian tiến trình đã chạy trong lượt này

void runRR() {
    // Nếu hết quantum
    if (timeSlice == quantum) {
        runningProcess->time_in_waiting_list = current_time; // Cập nhật thời gian vào hàng đợi
        waitingList.push(runningProcess); // Đưa lại vào cuối hàng đợi
        runningProcess = nullptr;
        timeSlice = 0;
    }
    // Nếu đang có tiến trình chạy
    if (runningProcess) {
        runningProcess->remaining_time -= UNIT_MS;
        timeSlice += UNIT_MS;
        printGantt('#');

        // Nếu tiến trình đã xong
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
            timeSlice = 0;
        }
    }

    // Nếu không có tiến trình đang chạy, chọn tiến trình mới
    else if (!runningProcess && !waitingList.empty()) {
        runningProcess = waitingList.front();
        waitingList.pop();
        if (runningProcess->start_time == -1) {
            runningProcess->start_time = current_time;
        }

        runningProcess->remaining_time -= UNIT_MS;
        timeSlice = UNIT_MS; 
        printGantt('|');

        // Nếu tiến trình xong ngay
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
            timeSlice = 0;
        }
    }
    // Nếu không có gì đang chạy và danh sách chờ rỗng
    else {
        printGantt('-');
    }
}
