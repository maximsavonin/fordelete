#include <math.h>
#include "graphics.h"
#include "task.h"

void fill_1(int left, int top, int width, int height)
{
   for(int y = top; y < height; y++)
   {
      int c = int(1.0*y/height*COLOR_MAX);
      for(int x = left; x < width; x++)
      {
         putpixel(x+left, y+top, COLOR(0, c/2, c));
      }
   }
}

void fill_2(int left, int top, int width, int height)
{
   for(int x = left; x < width; x++)
   {
      int c = int(1.0*x/width*COLOR_MAX);
      for(int y = top; y < height; y++)
      {
         putpixel(x+left, y+top, COLOR(0, c/2, c));
      }
   }
}

void fill_3(int left, int top, int width, int height)
{
   for(int y = top; y < height; y++)
   {
      int c = int((1-abs(y*2.0/height-1))*COLOR_MAX);
      for(int x = left; x < width; x++)
      {
         putpixel(x+left, y+top, COLOR(0, c/2, c));
      }
   }
}

void fill_4(int left, int top, int width, int height)
{
   for(int y = top; y < height; y++)
   {
      for(int x = left; x < width; x++)
      {
         int c = int(abs(1.0*x/width+1.0*y/height-1)*COLOR_MAX);
         putpixel(x+left, y+top, COLOR(0, c/2, c));
      }
   }
}

void fill_5(int left, int top, int width, int height)
{
   for(int y = top; y < height; y++)
   {
      for(int x = left; x < width; x++)
      {
         int c = int(abs(abs(abs(x*2.0/width-y*2.0/height)-1)-1)*COLOR_MAX);
         putpixel(x+left, y+top, COLOR(0, c/2, c));
      }
   }
}

void fill_6(int left, int top, int width, int height)
{
   for(int y = top; y < height; y++)
   {
      for(int x = left; x < width; x++)
      {
         int c = int((1-abs(2.0*x/width-1)-abs(2.0*y/height-1))*COLOR_MAX);
         c = c < 0 ? 0 : c;
         putpixel(x+left, y+top, COLOR(0, c/2, c));
      }
   }
}

void fill_7(int left, int top, int width, int height)
{
   double x, y, d, r;
   int c;
   
   r = (width > height ? height : width) / 2;
   
   for (x = 0; x < width; x++)
   {
      for (y = 0; y < height; y++)
      {
         d = sqrt((x - width / 2) * (x - width / 2) +
                  (y - height / 2) * (y - height / 2)) / r;
         c = d < 1 ? (1 - d) * COLOR_MAX : 0;
         putpixel(left + x, top + y, COLOR(0, c / 2, c));
      }
   }
}

void fill_8(int left, int top, int width, int height)
{
   double x, y, d, r;
   int c;
   
   r = (width > height ? height : width) / 2;
   
   for (x = 0; x < width; x++)
   {
      for (y = 0; y < height; y++)
      {
         d = sqrt((x - width / 2) * (x - width / 2) +
                  (y - height / 2) * (y - height / 2)) / r;
         c = abs(1 - d) * COLOR_MAX;
         putpixel(left + x, top + y, COLOR(0, c / 2, c));
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