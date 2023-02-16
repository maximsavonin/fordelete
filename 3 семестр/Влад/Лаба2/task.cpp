#include <math.h>
#include <random>
#include <time.h>
#include "graphics.h"
#include "task.h"

Point points[NP];

void genPoint(int left, int top, int width, int height)
{
   srand(time(0));
   setfillstyle(SOLID_FILL, COLOR(100, 255, 255));
   bar(left, top, width, height);
   
   IMAGE *image;
   image = loadBMP("iglu.bmp");
   for(int i = 0; i < NP; i++)
   {
      points[i].x = rand()%(width-30)+15;
      points[i].y = rand()%(height-30)+15;
      
      putimage(points[i].x-15, points[i].y-15, image, XOR_PUT);
   }
   freeimage(image);
}

void recPoint(int left, int top, int width, int height)
{
   int xMin = width, yMin =  height, xMax = left, yMax = top;
   
   for(int i = 0; i < NP; i++)
   {
      if(points[i].x > xMax){
         xMax = points[i].x;
      }
      if(points[i].y > yMax){
         yMax = points[i].y;
      }
      if(points[i].x < xMin){
         xMin = points[i].x;
      }
      if(points[i].y < yMin){
         yMin = points[i].y;
      }
   }
   setcolor(BLACK);
   rectangle(xMin-15, yMin-15, xMax+15, yMax+15);
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