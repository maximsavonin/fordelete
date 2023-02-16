#include <math.h>
#include "graphics.h"
#include "task.h"

void putp(int x, int y, int c, int a)
{
   switch(c)
   {
      case 0:
      {
         putpixel(x, y, COLOR(a, 0, 0));
         break;
      }
      case 1:
      {
         putpixel(x, y, COLOR(0, a, 0));
         break;
      }
      case 2:
      {
         putpixel(x, y, COLOR(0, a/2, a));
         break;
      }
   }
}

void fill_1(int left, int top, int width, int height, int c = 0)
{
   for(int i = 0; i < height; i++)
   {
      for(int k = 0; k < width; k++)
      {
         double a = 1.0*i/height*COLOR_MAX;
         putp(k+left, i+top, c, a);
      }
   }
}

void fill_2(int left, int top, int width, int height, int c = 0)
{
   for(int i = 0; i < height; i++)
   {
      for(int k = 0; k < width; k++)
      {
         double a = 1.0*k/width*COLOR_MAX;
         putp(k+left, i+top, c, a);
      }
   }
}

void fill_3(int left, int top, int width, int height, int c = 0)
{
   for(int i = 0; i < height; i++)
   {
      for(int k = 0; k < width; k++)
      {
         double a = (1-abs(1-i/(height/2.0)))*COLOR_MAX;
         putp(k+left, i+top, c, a);
      }
   }
}

void fill_4(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         double a = abs(1.0*i/height+1.0*k/width-1)*COLOR_MAX;
         putp(k+left, i+top, c, a);
      }
   }
}

void fill_5(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         double a = abs(2.0*i/height+2.0*(width-k)/width-2)*COLOR_MAX;
         a = a > COLOR_MAX ? COLOR_MAX-abs(a-COLOR_MAX) : a;
         putp(k+left, i+top, c, a);
      }
   }
}

void fill_6(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         double a = (1-abs(height/2.0-i)/(height/2.0)-abs(width/2.0-k)/(width/2.0))*COLOR_MAX;
         a = a < 0 ? 0 : a;
         putp(k+left, i+top, c, a);
      }
   }
}

void fill_7(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         double a = (height/2-sqrt((height/2-i)*(height/2-i)+(width/2-k)*(width/2-k)))/(height/2)*COLOR_MAX;
         a = (abs(a)+a)/2;
         putp(k+left, i+top, c, a);
      }
   }
}

void fill_8(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         double a = abs(height/2-sqrt((height/2-i)*(height/2-i)+(width/2-k)*(width/2-k)))/(height/2)*COLOR_MAX;
         putp(k+left, i+top, c, a);
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