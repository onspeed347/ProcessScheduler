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
void printInput();
void sortProcessesByArrivalTime();
void checkArrival();
void chooseAlgorithm(int *choice);
void printGantt(char symbol);
void printWaitingList(const queue<Process*>& original);
void printHeader(int choice);
void printResult();

bool finishProcessing();

void gotoXY(int x, int y);
void clearConsole();
void sleepMS(int ms);

#endif