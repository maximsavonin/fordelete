#define _USE_MATH_DEFINES
#include <math.h>
#include "graphics.h"
#include "task.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

Point *points;

void algoritm_chaikina()
{
   int n = 4;
   Point *points_ch;
   Point *points_copy;
   points_copy = new Point[n];
   for(int i = 0; i < n; i++)
   {
      points_copy[i] = points[i];
   }
   for (int i = 0; i < 10; i++)
   {
      delete[] points_ch;
      points_ch = new Point[2*n-2];
      points_ch[0].x = points_copy[0].x;
      points_ch[0].y = points_copy[0].y;
      points_ch[1].x = 0.25 * points_copy[0].x + 0.75 * points_copy[1].x;
      points_ch[1].y = 0.25 * points_copy[0].y + 0.75 * points_copy[1].y;

      for(int k = 1;k < n-2;k++)
      {
         points_ch[2*k].x = 0.75 * points_copy[k].x + 0.25 * points_copy[k+1].x;
         points_ch[2*k].y = 0.75 * points_copy[k].y + 0.25 * points_copy[k+1].y;
         points_ch[2*k + 1].x = 0.25 * points_copy[k].x + 0.75 * points_copy[k+1].x;
         points_ch[2*k + 1].y = 0.25 * points_copy[k].y + 0.75 * points_copy[k+1].y;
      }
      
      points_ch[2 * n - 4].x = 0.75 * points_copy[n-2].x + 0.25 * points_copy[n-1].x;
      points_ch[2 * n - 4].y = 0.75 * points_copy[n-2].y + 0.25 * points_copy[n-1].y;
      points_ch[2 * n - 3].x = points_copy[n-1].x;
      points_ch[2 * n - 3].y = points_copy[n-1].y;
      n = 2 * n-2;
      delete[] points_copy;
      points_copy = new Point[n];
      for(int k = 0;k < n;k++)
      {
         points_copy[k].x = points_ch[k].x;
         points_copy[k].y = points_ch[k].y;
      }
   }
   moveto(points_copy[0].x, points_copy[0].y);
   setcolor(WHITE);
   for (int i = 1; i < n; i++)
   lineto(points_copy[i].x,points_copy[i].y);
}



void curve_bezier()
{
   double x_line, y_line, z_step = 0.001;
   setcolor (YELLOW);
   moveto(points[0].x, points[0].y);
   for (double z = z_step; z < 1; z+=z_step){
      x_line = (1-z)*(1-z)*(1-z)* points[0].x + 3 * (1-z)*(1-z)*z* points[1].x + 3 * (1-z) * z * z* points[2].x + z*z*z*points[3].x;
      y_line = (1-z)*(1-z)*(1-z)* points[0].y + 3 * (1-z)*(1-z)*z* points[1].y + 3 * (1-z) * z * z* points[2].y + z*z*z*points[3].y;
      lineto(x_line, y_line);
   }
   lineto(points[3].x, points[3].y);
}



void take_dots(int left,int top,int width,int height)
{
   int n = 4;
   delete[] points;
   points = new Point[n];  
   char coordinates[10];
   delay(150);
   for(int i=0; i<n; i++)
   {
      while (mousebuttons() != 1);
      points[i].x=mousex();
      points[i].y=mousey();
      if (points[i].y<540)
      {
         setcolor(WHITE);
         circle(points[i].x,points[i].y,3);
         setfillstyle(SOLID_FILL,WHITE);
         floodfill(points[i].x,points[i].y,WHITE);
         sprintf(coordinates, "%.0lf %.0lf",points[i].x,points[i].y);
         outtextxy(820,550,coordinates);
         while(mousebuttons());
      }
      else i--;      
   }
}



void save()
{
   int width, height;
   IMAGE *output;
   
   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);
   
   getimage(0, 0, width - 1, height - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}