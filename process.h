#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Process {
    string pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int start_time;
    int completion_time;
    int time_in_waiting_list;
};

extern vector<Process> processes;
extern queue<Process*> waitingList;
extern Process* runningProcess;
extern int current_time;
extern int prevWaitingSize;
extern int NUMBER_OF_PROCESS;

extern const int REFRESH_MS;
extern const int UNIT_MS;
extern const int quantum;

#endif