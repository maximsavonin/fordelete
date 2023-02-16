#include "graphics.h"
#include "task.h"
#include <cmath>

using namespace std;

Square::Square() 
{
   ifstream f("Square.txt");
   f >> kolPoint >> kolSide;
   Points = new double*[kolPoint];
   for (int i = 0; i < kolPoint; i++)
   {
      Points[i] = new double[3];
      for (int j = 0; j < 3; j++)
      {
         f >> Points[i][j];
      }
   }
   Sides = new int*[kolSide];
   for (int i = 0; i < kolSide; i++)
   {
      Sides[i] = new int[4];
      for (int j = 0; j < 4; j++)
      {
         f >> Sides[i][j];
      }
   }
   f.close();
}

void Square::rote(int mode)
{
   double temp, angle  = acos(-1) / 20;
   for (int i = 0; i < kolPoint; i++)
   {
      Points[i][0] -= dir[0];
      Points[i][1] -= dir[1];
      Points[i][2] -= dir[2];
   }
   
   if(mode == 0)
   {
      for (int i = 0; i < kolPoint; i++)
      {
         temp = Points[i][0];
         Points[i][0] = Points[i][0]*cos(angle)
                           + Points[i][1]*sin(angle);
         Points[i][1] = - temp * sin(angle)
                     + Points[i][1]*cos(angle);
      }
   }
   if(mode == 1)
   {
      for (int i = 0; i < kolPoint; i++)
      {
         temp = Points[i][1];
         Points[i][1] = Points[i][1] * cos(angle)
                        + Points[i][2] * sin(angle);
         Points[i][2] = - temp * sin(angle)
                     + Points[i][2]*cos(angle);
      }
   }
   if(mode == 2)
   {
      for (int i = 0; i < kolPoint; i++)
      {
         temp = Points[i][0];
         Points[i][0] = Points[i][0]*cos(angle)
                              + Points[i][2]*sin(angle);
         Points[i][2] = - temp * sin(angle)
                        + Points[i][2]*cos(angle);
      }
   }
   for (int i = 0; i < kolPoint; i++)
   {
      Points[i][0] += dir[0];
      Points[i][1] += dir[1];
      Points[i][2] += dir[2];
   }
}

void Square::move(int mode, int direction)
{
   dir[0] += direction*px[mode];
   dir[1] += direction*py[mode];
   dir[2] += direction*pz[mode];
   for (int i = 0; i < kolPoint; i++)
   {
      Points[i][0] += direction*px[mode];
      Points[i][1] += direction*py[mode];
      Points[i][2] += direction*pz[mode];
   }
}

void Square::draw()
{
   int k;
   setcolor(WHITE);
   setlinestyle(SOLID_LINE, 0, 1);
   for(int i=0; i<kolSide; i++)
   {
      k = 0;
      for(int j=0; j<4; j++)
      {
            points[2*k] = WIDTH/2 + Points[Sides[i][j]][0];
            points[2*k+1] = HEIGHT/2 - Points[Sides[i][j]][1];
            k++;
      }
      points[2*k] = points[0];
      points[2*k+1] = points[1];
      k++;
      drawpoly(k, points);
   }
}

void save()
{
   int W, H;
   IMAGE *output;

   W = getmaxx() + 1;
   H = getmaxy() + 1;
   output = createimage(W, H);

   getimage(0, 0, W - 1, H - 1, output);
   getimage(0, 0, W - 1, H - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}
