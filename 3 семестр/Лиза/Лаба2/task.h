#ifndef TASK_H
#define TASK_H

#define COLOR_MAX 255
#define N_POINT 15

struct Point
{
   int x, y;
};

void genPoint(int, int, int, int);
void recPoint(int, int, int, int);
void save();

#endif