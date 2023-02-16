#define _USE_MATH_DEFINES
#include <math.h>
#include "graphics.h"
#include "task.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

Point *points;

void create_points(int left,int top,int width,int height)
{
   IMAGE * image;
   image = loadBMP ("fon.jpg");
   putimage (0,0,image,COPY_PUT);
   freeimage(image);
   
   int n = 4;
   delete[] points;
   points = new Point[n]; 
   delay(200);
   for(int i=0; i<n; i++)
   {
      while (mousebuttons() != 1);
      points[i].x=mousex();
      points[i].y=mousey();
      if (points[i].y<550)
      {
         setcolor(COLOR(0, 255, 0));
         circle(points[i].x,points[i].y,4);
         setfillstyle(SOLID_FILL,COLOR(0, 255, 0));
         floodfill(points[i].x,points[i].y,COLOR(0, 255, 0));
         while(mousebuttons());
      }
      else i--;      
   }
}

void bezier()
{
   double x, y, step = 0.001;
   setcolor (YELLOW);
   moveto(points[0].x, points[0].y);
   for (double z = step; z < 1; z+=step){
      x = (1-z)*(1-z)*(1-z)* points[0].x + 3 * (1-z)*(1-z)*z* points[1].x + 3 * (1-z) * z * z* points[2].x + z*z*z*points[3].x;
      y = (1-z)*(1-z)*(1-z)* points[0].y + 3 * (1-z)*(1-z)*z* points[1].y + 3 * (1-z) * z * z* points[2].y + z*z*z*points[3].y;
      lineto(x, y);
   }
   lineto(points[3].x, points[3].y);
}

void chaikina()
{
   int n = 4;
   Point *points_chaikin;
   Point *points_copy;
   points_copy = new Point[n];
   for(int i = 0; i < n; i++)
   {
      points_copy[i] = points[i];
   }
   for (int i = 0; i < 6; i++)
   {
      delete[] points_chaikin;
      points_chaikin = new Point[2*n-2];
      points_chaikin[0].x = points_copy[0].x;
      points_chaikin[0].y = points_copy[0].y;
      points_chaikin[1].x = 0.25 * points_copy[0].x + 0.75 * points_copy[1].x;
      points_chaikin[1].y = 0.25 * points_copy[0].y + 0.75 * points_copy[1].y;

      for(int k = 1;k < n-2;k++)
      {
         points_chaikin[2*k].x = 0.75 * points_copy[k].x + 0.25 * points_copy[k+1].x;
         points_chaikin[2*k].y = 0.75 * points_copy[k].y + 0.25 * points_copy[k+1].y;
         points_chaikin[2*k + 1].x = 0.25 * points_copy[k].x + 0.75 * points_copy[k+1].x;
         points_chaikin[2*k + 1].y = 0.25 * points_copy[k].y + 0.75 * points_copy[k+1].y;
      }
      
      points_chaikin[2 * n - 4].x = 0.75 * points_copy[n-2].x + 0.25 * points_copy[n-1].x;
      points_chaikin[2 * n - 4].y = 0.75 * points_copy[n-2].y + 0.25 * points_copy[n-1].y;
      points_chaikin[2 * n - 3].x = points_copy[n-1].x;
      points_chaikin[2 * n - 3].y = points_copy[n-1].y;
      n = 2 * n-2;
      delete[] points_copy;
      points_copy = new Point[n];
      for(int k = 0;k < n;k++)
      {
         points_copy[k].x = points_chaikin[k].x;
         points_copy[k].y = points_chaikin[k].y;
      }
   }
   moveto(points_copy[0].x, points_copy[0].y);
   setcolor(COLOR(0, 255, 0));
   for (int i = 1; i < n; i++)
   lineto(points_copy[i].x,points_copy[i].y);
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