#include <math.h>
#include "graphics.h"
#include "task.h"



void lineB(int x0, int y0, int x1, int y1)
{
   int color = getcolor();
   int deltax = abs(x1-x0);
   int deltay = abs(y1-y0);
   double error = 0;
   double deltaerr = 0;
   if(deltay > deltax)
   {
      if(deltay != 0) deltaerr = 1.0*deltax/deltay;
      if(y0 > y1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int x = x0;
      int dir = x1-x0;
      if(dir > 0)
      {
         dir = 1;
      }
      else
      {
         dir = -1;
      }
      for(int y = y0; y <= y1; y++)
      {
         putpixel(x, y, color);
         error += deltaerr;
         if(error >= 1)
         {
            x += dir;
            error--;
         }
      }
   }
   else
   {
      if(deltax != 0) deltaerr = 1.0*deltay/deltax;
      if(x0 > x1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int y = y0;
      int dir = y1-y0;
      if(dir > 0)
      {
         dir = 1;
      }
      else
      {
         dir = -1;
      }
      for(int x = x0; x <= x1; x++)
      {
         putpixel(x, y, color);
         error += deltaerr;
         if(error >= 1)
         {
            y += dir;
            error--;
         }
      }
   }
}

void star(int x, int y, int n, int r)
{
   Point *points;
   points = new Point[2*n];
   for(int i = 0; i < n*2; i++)
   {
      Point point;
      if(i%2)
      {
         point.x = x+int(r*cos(i*3.14/n));
         point.y = y+int(r*sin(i*3.14/n));
      }
      else
      {
         point.x = x+int(r*(cos(3.14/n*2)/cos(3.14/n))*cos(i*3.14/n));
         point.y = y+int(r*(cos(3.14/n*2)/cos(3.14/n))*sin(i*3.14/n));
      }
      points[i].x = point.x;
      points[i].y = point.y;
   }
   
   for(int i = 1; i < n*2; i++) lineB(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
   
   lineB(points[2*n-1].x, points[2*n-1].y, points[0].x, points[0].y);
   
   setfillstyle(SOLID_FILL, getcolor());
   floodfill(x, y, getcolor());
   
   delete[] points;
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