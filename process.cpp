#include "process.h"

vector<Process> processes;
queue<Process*> waitingList;
Process* runningProcess = nullptr;
int current_time = 0;
int prevWaitingSize = 0;
int NUMBER_OF_PROCESS;

const int REFRESH_MS = 500;
const int UNIT_MS = 1;
const int quantum = 3;