#include <math.h>
#include "graphics.h"
#include "task.h"

Point *newPoint(int x, int y, Point *root)
{
   if(root == NULL)
   {
      root = new Point;
      root->x = x;
      root->y = y;
      root->next = NULL;
      return root;
   }
   root->next = newPoint(x, y, root->next);
   return root;
}

void linebrez(int x0, int y0, int x1, int y1)
{
   int color = getcolor();
   int deltax = abs(x1-x0);
   int deltay = abs(y1-y0);
   double error = 0;
   double deltaerr = 0;
   if(deltax > deltay)
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
   else
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
}

void star(int x, int y, int n, int r)
{
   setcolor(WHITE);
   Point *root = NULL;
   for(int i = 0; i < n*2; i++)
   {
      int yp, xp;
      if(i%2)
      {
         xp = x+int(r*cos(i*3.14/n));
         yp = y+int(r*sin(i*3.14/n));
      }
      else
      {
         xp = x+int(r*(cos(3.14/n*2)/cos(3.14/n))*cos(i*3.14/n));
         yp = y+int(r*(cos(3.14/n*2)/cos(3.14/n))*sin(i*3.14/n));
      }
      root = newPoint(xp, yp, root);
   }
   
   Point *branch1 = root;
   Point *branch2 = NULL;
   if(branch1 != NULL) 
   {
      branch2 = branch1->next;
   }
   while(branch2 != NULL)
   {
      linebrez(branch1->x, branch1->y, branch2->x, branch2->y);
      branch1 = branch2;
      branch2 = branch1->next;
   }
   linebrez(branch1->x, branch1->y, root->x, root->y);
   setfillstyle(SOLID_FILL, getcolor());
   floodfill(x, y, getcolor());
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