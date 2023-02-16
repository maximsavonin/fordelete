#include <math.h>
#include <iostream>
#include "graphics.h"
#include "task.h"

using namespace std;

struct Point
{
   int x, y;
   Point *next;
};

Point *addPoint(int x, int y, Point *one)
{
   if(one == NULL)
   {
      one = new Point;
      one->x = x;
      one->y = y;
      one->next = NULL;
      return one;
   }
   one->next = addPoint(x, y, one->next);
   return one;
}

void lineVu(int x1, int y1, int x2, int y2, int col[3][2])
{
   int dx = abs(x2-x1);
   int dy = abs(y2-y1);
   int err = 0;
   int derr = 200;
   if(dx != 0) derr = 200*(dy)/(dx);
   if(derr < 200)
   {
      if(x1 > x2)
      {
         int a = x1;
         x1 = x2;
         x2 = a;
         a = y1;
         y1 = y2;
         y2 = a;
      }
      int y = y1;
      int d = dy == 0 ? 0 : (y2-y1)/dy;
      putpixel(x1, y1, COLOR(col[0][0], col[1][0], col[2][0]));
      for(int x = x1; x <= x2; x++)
      {
         putpixel(x, y, COLOR((200-err)*col[0][0]/200, (200-err)*col[1][0]/200, (200-err)*col[2][0]/200));
         if(err>2) putpixel(x, y+d, COLOR(err*col[0][0]/200, err*col[1][0]/200, err*col[2][0]/200));
         err = err+derr;
         if(err >= 200)
         {
            y += d;
            err -= 200;
         }
      }
      putpixel(x2, y2, COLOR(col[0][0], col[1][0], col[2][0]));
   }
   else
   {
      if(y1 > y2)
      {
         int a = x1;
         x1 = x2;
         x2 = a;
         a = y1;
         y1 = y2;
         y2 = a;
      }
      derr = 40000/derr;
      int x = x1;
      int d = dx == 0 ? 0 : (x2-x1)/dx;
      putpixel(x1, y1, COLOR(col[0][0], col[1][0], col[2][0]));
      for(int y = y1; y <= y2; y++)
      {
         putpixel(x, y, COLOR((200-err)*col[0][0]/200, (200-err)*col[1][0]/200, (200-err)*col[2][0]/200));
         if(err>2) putpixel(x, y+d, COLOR(err*col[0][0]/200, err*col[1][0]/200, err*col[2][0]/200));
         err = err+derr;
         if(err >= 200)
         {
            x += d;
            err -= 200;
         }
      }
      putpixel(x2, y2, COLOR(col[0][0], col[1][0], col[2][0]));
   }
}

void drawPol(int x, int y, int n, int r, int col[3][2])
{
   Point *one = NULL;
   
   for(int i = 0; i < n*2+1; i++)
   {
      int yp, xp;
      if(i%2)
      {
         xp = x+int(r*cos(i*3.14*1/n));
         yp = y+int(r*sin(i*3.14*1/n));
      }
      else
      {
         int m = (n-1)/2;
         m = m<2 ? 2 : m;
         xp = x+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*cos(i*3.14*1/n));
         yp = y+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*sin(i*3.14*1/n));
      }
      one = addPoint(xp, yp, one);
   }
   
   Point *two = one->next;
   while(two != NULL)
   {
      lineVu(one->x, one->y, two->x, two->y, col);
      one = two;
      two = one->next;
   }
}

void fill(int x, int y, int col[3][2])
{
   if(getpixel(x, y) == 0)
   {
      putpixel(x, y, COLOR(col[0][0], col[1][0], col[2][0]));
      fill(x+1, y, col);
      fill(x-1, y, col);
      fill(x, y+1, col);
      fill(x, y-1, col);
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