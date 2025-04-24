#include "scheduler.h"

void runAlgorithm(const int choice) {
    printHeader(choice);
    while (!finishProcessing()) {
        checkArrival();
        switch(choice) {
            case 1: runFCFS(); break;
            case 2: runSJF(); break;
            case 3: runSRTF(); break;
            case 4: runRR(); break;
            case 5: runPriorityNonPreemptive(); break;
            case 6: runPriorityPreemptive(); break;
        }
        printWaitingList(waitingList);
        sleepMS(REFRESH_MS);
        current_time += UNIT_MS;
    }
    printResult();
}