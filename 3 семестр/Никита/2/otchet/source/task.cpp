#include <math.h>
#include <random>
#include <time.h>
#include "graphics.h"
#include "task.h"

Square sq[2];

void genPoint(int left, int top, int width, int height)
{
   srand(time(0));
   
   IMAGE *image;
   
   image = loadBMP("fon.bmp");
   putimage(0, 0, image, COPY_PUT);
   
   freeimage(image);
   
   setcolor(COLOR(255, 0, 0));
   for(int i = 0; i < 2; i++)
   {
      sq[i].x1 = rand()%(width-left-10)+5;
      sq[i].x2 = rand()%(width-left-10)+5;
      sq[i].y1 = rand()%(height-top-10)+5;
      sq[i].y2 = rand()%(height-top-10)+5;
      if(sq[i].x1 > sq[i].x2)
      {
         int x = sq[i].x1;
         sq[i].x1 = sq[i].x2;
         sq[i].x2 = x;
      }
      if(sq[i].y1 > sq[i].y2)
      {
         int y = sq[i].y1;
         sq[i].y1 = sq[i].y2;
         sq[i].y2 = y;
      }
      rectangle(sq[i].x1, sq[i].y1, sq[i].x2, sq[i].y2);
   }
}

void recPoint(int left, int top, int width, int height)
{
   
   int x1 = fmax(sq[0].x1, sq[1].x1);
   int x2 = fmin(sq[0].x2, sq[1].x2);
   int y1 = fmax(sq[0].y1, sq[1].y1);
   int y2 = fmin(sq[0].y2, sq[1].y2);
   if(x2-x1 <= 0 || y2-y1 <= 0) return;
   setfillstyle(SOLID_FILL, COLOR(255, 0, 0));
   floodfill((x2-x1)/2+x1, (y2-y1)/2+y1, COLOR(255, 0, 0));
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