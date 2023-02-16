#ifndef TASK_H
#define TASK_H

struct Point;

Point *addPoint(int, int, Point*);
void lineVu(int, int, int, int, int[3][2]);
void drawPol(int, int, int, int, int[3][2]);
void fill(int, int, int[3][2]);
void save();

#endif