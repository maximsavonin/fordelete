#include <math.h>
#include "graphics.h"
#include "task.h"

void fill_1(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         double a = i/height*COLOR_MAX;
         switch(c)
         {
            case 0:
            {
               putpixel(k, i, COLOR(a, 0, 0));
               break;
            }
            case 1:
            {
               putpixel(k, i, COLOR(0, a, 0));
               break;
            }
            case 2:
            {
               putpixel(k, i, COLOR(0, 0, a));
               break;
            }
         }
      }
   }
}

void fill_2(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         double a = k/width*COLOR_MAX;
         switch(c)
         {
            case 0:
            {
               putpixel(k, i, COLOR(a, 0, 0));
               break;
            }
            case 1:
            {
               putpixel(k, i, COLOR(0, a, 0));
               break;
            }
            case 2:
            {
               putpixel(k, i, COLOR(0, 0, a));
               break;
            }
         }
      }
   }
}

void fill_3(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         double a = 255-abs(height/2-i)*255/(height/2);
         switch(c)
         {
            case 0:
            {
               putpixel(k, i, COLOR(a, 0, 0));
               break;
            }
            case 1:
            {
               putpixel(k, i, COLOR(0, a, 0));
               break;
            }
            case 2:
            {
               putpixel(k, i, COLOR(0, 0, a));
               break;
            }
         }
      }
   }
}

void fill_4(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         int a = int(abs(1.0*i/height+1.0*k/width-1)*255);
         switch(c)
         {
            case 0:
            {
               putpixel(k, i, COLOR(a, 0, 0));
               break;
            }
            case 1:
            {
               putpixel(k, i, COLOR(0, a, 0));
               break;
            }
            case 2:
            {
               putpixel(k, i, COLOR(0, 0, a));
               break;
            }
         }
      }
   }
}

void fill_5(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         int a = int(abs(2.0*i/height+2.0*(width-k)/width-2)*255);
         if(a > 255) a = 255-abs(a-255);
         switch(c)
         {
            case 0:
            {
               putpixel(k, i, COLOR(a, 0, 0));
               break;
            }
            case 1:
            {
               putpixel(k, i, COLOR(0, a, 0));
               break;
            }
            case 2:
            {
               putpixel(k, i, COLOR(0, 0, a));
               break;
            }
         }
      }
   }
}

void fill_6(int left, int top, int width, int height, int c = 0)
{
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         int a = (255-abs(height/2-i)*255/(width/2)-abs(width/2-k)*255/(width/2))/2;
         if(a < 0) a = 0;
         switch(c)
         {
            case 0:
            {
               putpixel(k, i, COLOR(a, 0, 0));
               break;
            }
            case 1:
            {
               putpixel(k, i, COLOR(0, a, 0));
               break;
            }
            case 2:
            {
               putpixel(k, i, COLOR(0, 0, a));
               break;
            }
         }
      }
   }
}

void fill_7(int left, int top, int width, int height, int c = 0)
{
   int a;
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         a = (height/2-sqrt((height/2-i)*(height/2-i)+(width/2-k)*(width/2-k)))*255/(height/2);
         a = (abs(a)+a)/2;
         switch(c)
         {
            case 0:
            {
               putpixel(k, i, COLOR(a, 0, 0));
               break;
            }
            case 1:
            {
               putpixel(k, i, COLOR(0, a, 0));
               break;
            }
            case 2:
            {
               putpixel(k, i, COLOR(0, 0, a));
               break;
            }
         }
      }
   }
}

void fill_8(int left, int top, int width, int height, int c = 0)
{
   int a;
   for(int i = top; i < height; i++)
   {
      for(int k = left; k < width; k++)
      {
         a = abs(height/2-sqrt((height/2-i)*(height/2-i)+(width/2-k)*(width/2-k)))*255/(width/2);
         a = a > 255 ? 255-(a-255) : a;
         switch(c)
         {
            case 0:
            {
               putpixel(k, i, COLOR(a, 0, 0));
               break;
            }
            case 1:
            {
               putpixel(k, i, COLOR(0, a, 0));
               break;
            }
            case 2:
            {
               putpixel(k, i, COLOR(0, 0, a));
               break;
            }
         }
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