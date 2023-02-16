#include <math.h>
#include <random>
#include <time.h>
#include "graphics.h"
#include "task.h"

void creatPoint(Point points[15], int left, int top, int width, int height)
{
   IMAGE *image;
   
   image = loadBMP("Map.bmp");
   putimage(left, top, image, COPY_PUT);
   
   freeimage(image);
   srand(time(0));
   
   left += 50;
   top += 50;
   width -= 50;
   height -= 50;
   for(int i = 0; i < 15; i++)
   {
      points[i].x = rand()%(width-left)+left;
      points[i].y = rand()%(height-top)+top;
      if(points[i].x < 250 && points[i].y > 260 || points[i].x < 230 && points[i].x > 85 && points[i].y > 130)
      {
         i--;
         continue;
      }
      
      setfillstyle(SOLID_FILL, BLACK);
      setcolor(BLACK);
      fillellipse(points[i].x, points[i].y, 4, 4);
   }
}

void treat(Point points[15])
{
   double l_max = 0, l;
   int twoPoint[2];
   for(int i = 0; i < 15; i++)
   {
      for(int k = i; k < 15; k++)
      {
         int x = points[i].x-points[k].x;
         int y = points[i].y-points[k].y;
         l = sqrt(x*x+y*y);
         if(l > l_max)
         {
            l_max = l;
            twoPoint[0] = i;
            twoPoint[1] = k;
         }
      }
   }
   line(points[twoPoint[0]].x, points[twoPoint[0]].y, points[twoPoint[1]].x, points[twoPoint[1]].y);
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