#ifndef TASK_H
#define TASK_H

#define COLOR_MAX 255

struct Point
{
   int x = 0, y = 0;
};

void creatPoint(Point[15], int, int, int, int);
void treat(Point[15]);
void save();

#endif