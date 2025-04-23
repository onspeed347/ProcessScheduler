#include "process.h"
#include "utils.h"
#include "algorithms/scheduler.h" 

int main() {
    clearConsole();
    readInput("input.txt");               
    runFCFS();         
    system("pause");
    return 0;
}
