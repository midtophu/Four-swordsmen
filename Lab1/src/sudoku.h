#ifndef SUDOKU_H
#define SUDOKU_H

#include "SDK.h"
const bool DEBUG_MODE = false;
enum { ROW=9, COL=9, N = 81, NEIGHBOR = 20 };
const int NUM = 9;
const int IN_THREADNUM=1;
const int OUT_THREADNUM=1;
const int WORK_THREADNUM=2;



extern int neighbors[N][NEIGHBOR];
extern int spaces[N];
extern int nspaces;
extern int (*chess)[COL];

void init_neighbors();
void input(SDK*sdk);
bool available(int guess, int cell);
bool solve_sudoku_dancing_links(SDK *sdk);
bool solved();
#endif
