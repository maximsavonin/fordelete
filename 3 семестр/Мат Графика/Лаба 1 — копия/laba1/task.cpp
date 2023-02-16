#define _USE_MATH_DEFINES 
#include <math.h>
#include <time.h>
#include "graphics.h"
#include "task.h"

void drawLine(int x0, int y0, int x1, int y1)
{
   int deltax, deltay, x, y, color = getcolor();
   double error, deltaerr;
   deltax = abs(x1 - x0);
   deltay = abs(y1 - y0);
   error = 0;
   if(deltax > deltay)
   {
      deltaerr = 1.0*deltay/deltax;
      if(x0 > x1)
      {
         x = x1;
         x1 = x0;
         x0 = x;
         y = y1;
         y1 = y0;
         y0 = y;
      }
      y = y0;
      int diry = y1 - y0;
      if (diry > 0) diry = 1;
      if (diry < 0) diry = -1;
      putpixel(x0, y0, color);
      putpixel(x1, y1, color);
      for(x = x0; x <= x1; x++)
      {
         putpixel(x, y, color);
         error += deltaerr;
         if(error >= 1)
         {
            y += diry;
            error--;
         }
      }
   }
   else
   {
      deltaerr = 1.0*deltax/deltay ;
      if(y0 > y1)
      {
         x = x1;
         x1 = x0;
         x0 = x;
         y = y1;
         y1 = y0;
         y0 = y;
      }
      x = x0;
      int dirx = x1 - x0;
      if (dirx > 0) dirx = 1;
      if (dirx < 0) dirx = -1;
      putpixel(x0, y0, color);
      putpixel(x1, y1, color);
      for(y = y0; y <= y1; y++)
      {
         putpixel(x, y, color);
         error += deltaerr;
         if(error >= 1)
         {
            x += dirx;
            error--;
         }
      }
   }
}

void drawStar(int x, int y, int radiusBig, int n)
{
   double radiusSmall = (radiusBig * cos(2*M_PI/n))/cos(M_PI/n);
   int x1, y1;
   x1 = int(x+radiusBig*cos(0));
   y1 = int(y+radiusBig*sin(0));
   for(int i = 1; i < 2 * n+1; i++)
   {
      int k = i%2 == 0 ? radiusBig : radiusSmall;
      int x2 = int(x+k * cos(i*M_PI/n));
      int y2 = int(y+k*sin(i*M_PI/n));
      drawLine(x1 , y1, x2, y2);
      x1 = x2;
      y1 = y2;
   }
   delay(10);
   setfillstyle(SOLID_FILL, getcolor());
   floodfill(x, y, getcolor());
}

void save()
{
    int width, height;
    IMAGE *output;
    
    width = getmaxx() + 1;
    height = getmaxy() + 1;
    output = createimage(width, height);
    
    getimage(0, 0, width - 1, height - 1, output);

    saveBMP("output.bmp", output);
    freeimage(output);
}