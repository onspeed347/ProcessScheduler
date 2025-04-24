#include "process.h"
#include "utils.h"
#include "algorithms/scheduler.h" 

int main() {
    clearConsole();
    readInput("input.txt");  
    sortProcessesByArrivalTime();
    printInput();
    int choice;
    chooseAlgorithm(&choice);
    clearConsole();
    runAlgorithm(choice);
    system("pause");
    return 0;
}
