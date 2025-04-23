#include "scheduler.h"

void processFCFS(int current_time, int *idx) {
    //Vao thoi diem current_time, dua tat ca processes co arrival_time <= current_time vao waitingList
    while (*idx < processes.size() && processes[*idx].arrival_time <= current_time) {
        processes[*idx].time_in_waiting_list = current_time;
        waitingList.push(&processes[*idx]);
        (*idx)++;
    }

    //Neu khong co process nao dang chay, lay process dau tien trong waitingList ra chay
    if (runningProcess == nullptr && !waitingList.empty()) {
        runningProcess = waitingList.front();
        waitingList.pop();
        runningProcess->remaining_time -= UNIT_MS;
        printGantt('|');
       
        //Neu process nay chua bat dau chay, gan start_time cho process do
        if (runningProcess->start_time == -1) {
            runningProcess->start_time = current_time;
        }
        //Neu process nay da chay xong, gan completion_time cho process do
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    }
    //Neu co process dang chay, giam remaining_time cua process do di 1 don vi thoi gian
    else if (runningProcess != nullptr) {
        runningProcess->remaining_time -= UNIT_MS;
        printGantt('#');
        //Neu process nay da chay xong, gan completion_time cho process do
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    }
    else {
        printGantt('-');
    }
}

void runFCFS() {
    printHeader("First Come First Serve");
    sortProcessesByArrivalTime();
    int idx = 0;
    while (idx < processes.size() || !waitingList.empty() || runningProcess != nullptr) {
        processFCFS(current_time, &idx);
        printWaitingList(waitingList);
        sleepMS(REFRESH_MS);
        current_time += UNIT_MS;
    }
    printResult();
}