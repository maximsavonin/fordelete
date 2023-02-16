#include <vector>
#include <fstream>
#ifndef TASK_H
#define TASK_H
#define WIDTH 700
#define HEIGHT 588

using namespace std;

class Square
{
private:
   int px[3] = {20, 0, 0};
   int py[3] = {0, 20, 0};
   int pz[3] = {0, 0, 20};
   int [30];
   int kolPoint, kolSide;
   int dir[3] = {0, 0, 0};
   double **Points;
   int **Sides;
public:
   Square();
   void rote(int);
   void move(int, int);
   void draw();
};

void save();

#endif