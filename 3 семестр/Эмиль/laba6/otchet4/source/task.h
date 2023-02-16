#ifndef TASK_H
#define TASK_H

struct Point
{
   int x, y;
};

void draw(Point, Point*);
void scale(Point*, double);
void spin(Point*, double);
void save();
#endif