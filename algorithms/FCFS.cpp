#include "scheduler.h"

void runFCFS() {
    //Neu co process dang chay, giam remaining_time cua process do di 1 don vi thoi gian
    if (runningProcess) {
        runningProcess->remaining_time -= UNIT_MS;
        printGantt('#');
        //Neu process nay da chay xong, gan completion_time cho process do
        if (runningProcess->remaining_time == 0) {
            runningProcess->completion_time = current_time + UNIT_MS;
            runningProcess = nullptr;
        }
    }
    //Neu khong co process nao dang chay, lay process dau tien trong waitingList ra chay
    else if (!waitingList.empty()) {
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
    //Neu waitingList cung trong
    else {
        printGantt('-');
    }
}