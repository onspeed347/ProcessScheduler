#ifndef UTILS_H
#define UTILS_H

#include "process.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <thread>
#include <chrono>

void readInput(const string &filename);
void printGantt(char symbol);
void printWaitingList(const queue<Process*>& original);
void sortProcessesByArrivalTime();
void printHeader(string header);
void printResult();
void gotoXY(int x, int y);
void clearConsole();
void sleepMS(int ms);

#endif