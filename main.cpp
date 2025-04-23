#include "process.h"
#include "utils.h"
#include "algorithms/scheduler.h" 

int main() {
    clearConsole();
    readInput("input.txt");      
    printHeader("PRIORITY NON-PREEMPTIVE");               
    runPriorityNonPreemptive();  
    printResult();                
    return 0;
}
