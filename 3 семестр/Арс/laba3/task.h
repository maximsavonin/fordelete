#ifndef TASK_H
#define TASK_H

#define COLOR_MAX 255

struct Point
{
   int x, y;
   Point *next;
};

Point *newPoint(int, int, Point*);
void linebrez(int, int, int, int);
void star(int, int, int, int);
void save();

#endif