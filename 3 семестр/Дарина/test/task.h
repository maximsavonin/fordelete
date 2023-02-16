#include <vector>
#include <fstream>
#include <string>
#ifndef TASK_H
#define TASK_H
#define WIDTH 900
#define HEIGHT 620

using namespace std;

class Figure
{
private:
   int dx[3] = {10, 0, 0};
   int dy[3] = {0, 10, 0};
   int dz[3] = {0, 0, 10};
   int p[30];
   int VertexNum, FaceNum;
   double cx, cy, cz;
   vector<vector<double>> vertices;
   vector<vector<int>> faces;
public:
   Figure();
   void rotate(int);
   void move(int, int);
   void draw(int);
};

void save();

#endif