#ifndef TASK_H
#define TASK_H

#define COLOR_MAX 255

struct Circ
{
   int x = 0, y = 0, r = 0;
};

void creatPoint(Circ[2], int, int, int, int);
void draw(double, double);
void treat(Circ[2]);
void save();

#endif