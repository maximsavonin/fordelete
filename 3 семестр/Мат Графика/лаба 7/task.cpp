#include "graphics.h"
#include "task.h"
#include <cmath>

using namespace std;

Figure::Figure() 
{
   ifstream f("Piramida.txt");
   f >> numPoint >> numPol;
   Points = new double*[numPoint];
   for (int i = 0; i < numPoint; i++)
   {
      Points[i] = new double[3];
      for (int j = 0; j < 3; j++)
      {
         f >> Points[i][j];
      }
   }
   Pol = new int*[numPol];
   for (int i = 0; i < numPol; i++)
   {
      Pol[i] = new int[3];
      for (int j = 0; j < 3; j++)
      {
         f >> Pol[i][j];
      }
   }
   f.close();
}

void Figure::rote(int mode)
{
   double temp, angle  = acos(-1) / 20;
   for (int i = 0; i < numPoint; i++)
   {
      Points[i][0] -= dir[0];
      Points[i][1] -= dir[1];
      Points[i][2] -= dir[2];
   }
   
   if(mode == 0)
   {
      for (int i = 0; i < numPoint; i++)
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
      for (int i = 0; i < numPoint; i++)
      {
         temp = Points[i][0];
         Points[i][0] = Points[i][0]*cos(angle)
                              + Points[i][2]*sin(angle);
         Points[i][2] = - temp * sin(angle)
                        + Points[i][2]*cos(angle);
      }
   }
   if(mode == 2)
   {
      for (int i = 0; i < numPoint; i++)
      {
         temp = Points[i][1];
         Points[i][1] = Points[i][1] * cos(angle)
                        + Points[i][2] * sin(angle);
         Points[i][2] = - temp * sin(angle)
                     + Points[i][2]*cos(angle);
      }
   }
   for (int i = 0; i < numPoint; i++)
   {
      Points[i][0] += dir[0];
      Points[i][1] += dir[1];
      Points[i][2] += dir[2];
   }
}

void Figure::move(int mode, int direction)
{
   dir[0] += direction*px[mode];
   dir[1] += direction*py[mode];
   dir[2] += direction*pz[mode];
   for (int i = 0; i < numPoint; i++)
   {
      Points[i][0] += direction*px[mode];
      Points[i][1] += direction*py[mode];
      Points[i][2] += direction*pz[mode];
   }
}

void Figure::draw()
{
   int k;
   setcolor(WHITE);
   setlinestyle(SOLID_LINE, 0, 1);
   for(int i=0; i<numPol; i++)
   {
      k = 0;
      for(int j=0; j<3; j++)
      {
            figure[2*k] = WIDTH/2 + Points[Pol[i][j]][0];
            figure[2*k+1] = HEIGHT/2 - Points[Pol[i][j]][1];
            k++;
      }
      figure[2*k] = figure[0];
      figure[2*k+1] = figure[1];
      k++;
      drawpoly(k, figure);
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
