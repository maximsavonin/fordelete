#define _USE_MATH_DEFINES 
#include <math.h>
#include <time.h>
#include "graphics.h"
#include "task.h"

void drawCircle(int X1, int Y1, int R)
{
   int color = getcolor();
   int x = 0;
   int y = R;
   int delta = 1-2*R;
   int error = 0;
   while(y >= x)
   {
      putpixel(X1+x, Y1+y, color);
      putpixel(X1+x, Y1-y, color);
      putpixel(X1-x, Y1+y, color);
      putpixel(X1-x, Y1-y, color);
      putpixel(X1+y, Y1+x, color);
      putpixel(X1+y, Y1-x, color);
      putpixel(X1-y, Y1+x, color);
      putpixel(X1-y, Y1-x, color);
      error = 2*(delta+y)-1;
      if(delta < 0 && error <= 0)
      {
         delta += 2* ++x+1;
         continue;
      }
      if(delta > 0 && error > 0)
      {
         delta -= 2* --y+1;
         continue;
      }
      delta += 2*(++x - --y);
   }
}

void drawAllCircle()
{
   setcolor(COLOR(77, 255, 0));
   drawCircle(450, 270, 100);
   drawCircle(550, 270, 100);
   drawCircle(350, 270, 100);
   drawCircle(450, 170, 100);
   drawCircle(450, 370, 100);
   
   drawCircle(500, 357, 100);
   drawCircle(500, 183, 100);
   drawCircle(400, 357, 100);
   drawCircle(400, 183, 100);
   
   drawCircle(537, 320, 100);
   drawCircle(537, 220, 100);
   drawCircle(363, 320, 100);
   drawCircle(363, 220, 100);
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