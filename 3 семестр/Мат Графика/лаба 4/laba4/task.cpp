#include <math.h>
#include <iostream>
#include "graphics.h"
#include "task.h"

using namespace std;

void circleBre(int x1, int y1, int r, int thickness)
{
   int color = getcolor();
   for(int i = 1; i < thickness+1; i++)
   {
      int x = 0;
      int y = r+i/2*pow(-1, i-1);
      int delta = 1-2*(r+i/2*pow(-1, i-1));
      int err = 0;
      while(y >= x)
      {
         putpixel(x1+x, y1+y, color);
         putpixel(x1+x, y1-y, color);
         putpixel(x1-x, y1+y, color);
         putpixel(x1-x, y1-y, color);
         putpixel(x1+y, y1+x, color);
         putpixel(x1+y, y1-x, color);
         putpixel(x1-y, y1+x, color);
         putpixel(x1-y, y1-x, color);
         err = 2*(delta+y)-1;
         if(delta < 0 && err <= 0)
         {
            delta += 2*++x+1;
            continue;
         }
         if(delta > 0 && err > 0)
         {
            delta -= 2*--y+1;
            continue;
         }
         delta += 2*(++x- --y);
      }
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