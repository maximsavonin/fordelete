#ifndef TASK_H
#define TASK_H
#define MAX_SIZE 66 

struct Point
{
   double x,y;
};

void mark_points(int,int,int,int);
void bezier_curve();
void chaikin_alg();
void save();

#endif