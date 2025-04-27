#include "utils.h"

void clearConsole() {
    cout << "\033[2J\033[1;1H"; // Xoá và đưa con trỏ về đầu
}

void sleepMS(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void gotoXY(int x, int y) {
    cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}


void readInput(const string &filename) {
    ifstream inFile(filename);
    inFile >> NUMBER_OF_PROCESS;
    processes.resize(NUMBER_OF_PROCESS);
    for (int i = 0; i < NUMBER_OF_PROCESS; i++) {
        inFile >> processes[i].pid >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
    }
    inFile.close();
}

void printInput() {
    cout << "PID  Arrival  Burst  Priority\n";
    cout << "-----------------------------\n";
    for (const auto& p : processes) {
        printf("%-5s%7d%7d%10d\n", p.pid.c_str(), p.arrival_time, p.burst_time, p.priority);
    }
    cout << "-----------------------------\n";
    cout << "Total processes: " << NUMBER_OF_PROCESS << "\n";
}

void sortProcessesByArrivalTime() {
    sort(processes.begin(), processes.end(), [](const Process & a, const Process & b) {
        return a.arrival_time < b.arrival_time;
    });
}

void chooseAlgorithm(int *choice) {
    cout << "-----------------------------\n";
    cout << "Choose an algorithm:\n";
    cout << "1. First Come First Serve\n";
    cout << "2. Shortest Job First\n";
    cout << "3. Shortest Remaining Time First\n";
    cout << "4. Round Robin\n";
    cout << "5. Priority Non-Preemptive\n";
    cout << "6. Priority Pre-emptive\n";
    cin >> *choice;
}

void checkArrival() {
    //Vao thoi diem current_time, dua tat ca processes co arrival_time <= current_time vao waitingList
    while (idx < NUMBER_OF_PROCESS && processes[idx].arrival_time <= current_time) {
        processes[idx].time_in_waiting_list = current_time;
        waitingList.push(&processes[idx]);
        idx++;
    }
}

void printGantt(char symbol) {
    gotoXY(current_time, 4);
    cout << symbol;
    if (symbol == '|') {
        gotoXY(current_time, 3);
        cout << runningProcess->pid;
        gotoXY(current_time, 5);
        cout << current_time;
    }
}

void printWaitingList() {
    queue<Process*> tempList = waitingList;
    int currentWaitingSize = (int) waitingList.size();
    if (currentWaitingSize < prevWaitingSize) {
        for (int i = currentWaitingSize; i < prevWaitingSize; i++) {
            gotoXY(0, 10 + i);
            cout << "                                 ";
        }
    }

    gotoXY(0, 10);
    while(!tempList.empty()) {
        Process* p = tempList.front();
        printf("%-5s%6d%10d%11d\n", p->pid.c_str() , p->time_in_waiting_list, p->priority, p->remaining_time);
        tempList.pop();
    }
    prevWaitingSize = currentWaitingSize;
}

void printHeader(int choice) {
    switch(choice) {
        case 1: cout << "First Come First Serve\n"; break;
        case 2: cout << "Shortest Job First\n"; break;
        case 3: cout << "Shortest Remaining Time First\n"; break;
        case 4: cout << "Round Robin\n"; break;
        case 5: cout << "Priority Non-Preemptive\n"; break;
        case 6: cout << "Priority Pre-emptive\n"; break;
    }
    cout << "----------------------\nGantt Chart";
    gotoXY(0, 7);
    cout << "Waiting List\n";
    cout << "PID  TimeIn  Priority  Remaining\n";
    cout << "--------------------------------\n";
}

void printResult() {
    gotoXY(0, 7);
    cout << "PID  Arrival  Burst  Priority  Response  Waiting\n";
    cout << "------------------------------------------------\n";
    int total_waiting_time = 0;
    for (const auto& p : processes) {
        printf("%-5s%7d%7d%10d%8dms%7dms\n", p.pid.c_str(), p.arrival_time, p.burst_time, p.priority, p.start_time - p.arrival_time, p.completion_time - p.arrival_time - p.burst_time);
        total_waiting_time += p.completion_time - p.arrival_time - p.burst_time;
    }
    int average_waiting_time = total_waiting_time / processes.size();
    cout << "Average waiting time ---------------------- " << average_waiting_time << "ms\n";
}

bool finishProcessing() {
    return (idx >= NUMBER_OF_PROCESS && waitingList.empty() && !runningProcess);
}
