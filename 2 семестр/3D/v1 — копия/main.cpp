//overleaf.com
#include <stdio.h>
#include <math.h>
#include <random>
#include <ctime>

#include "graphics.h"

#define W 1800
#define H 900

typedef struct Button
{
   int x, y;
   char text[20] = {0};
}Button;

void fill_1(int c)
{
   for(int i = 0; i < H; i++)
   {
      for(int k = 0; k < W; k++)
      {
         int a = i*255/H;
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

void fill_2(int c)
{
   for(int i = 0; i < H; i++)
   {
      for(int k = 0; k < W; k++)
      {
         int a = k*255/W;
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

void fill_3(int c)
{
   for(int i = 0; i < H; i++)
   {
      for(int k = 0; k < W; k++)
      {
         int a = 255-abs(H/2-i)*255/(H/2);
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

void fill_4(int c)
{
   for(int i = 0; i < H; i++)
   {
      for(int k = 0; k < W; k++)
      {
         int a = int(abs(1.0*i/H+1.0*k/W-1)*255);
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

void fill_5(int c)
{
   for(int i = 0; i < H; i++)
   {
      for(int k = 0; k < W; k++)
      {
         int a = int(abs(2.0*i/H+2.0*(W-k)/W-2)*255);
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

void fill_6(int c)
{
   for(int i = 0; i < H; i++)
   {
      for(int k = 0; k < W; k++)
      {
         int a = (255-abs(H/2-i)*255/(H/2)-abs(W/2-k)*255/(W/2))/2;
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

void fill_7(int c)
{
   int a;
   for(int i = 0; i < H; i++)
   {
      for(int k = 0; k < W; k++)
      {
         a = (H/2-sqrt((H/2-i)*(H/2-i)+(W/2-k)*(W/2-k)))*255/(H/2);
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

void fill_8(int c)
{
   int a;
   for(int i = 0; i < H; i++)
   {
      for(int k = 0; k < W; k++)
      {
         a = abs(H/2-sqrt((H/2-i)*(H/2-i)+(W/2-k)*(W/2-k)))*255/(H/2);
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

int main()
{
   initwindow(W, H, "Win", 0, 40);
   Button btns[12] = {{500, 300, "1"}, {800, 300, "2"}, {1100, 300, "3"}, {1400, 300, "4"}, {500, 500, "5"}, {800, 500, "6"}, {1100, 500, "7"}, {1400, 500, "8"}, {650, 400, "Red"}, {950, 400, "Green"}, {1250, 400, "Blue"}, {0, 0, "Save"}};
   int p = 0, num = -1;
   int h = 30, w = 70;
   int c = -1;
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   setusercharsize(1, 1, 3, 2);
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      if(num == -1)
      {
         for(int i = 0; i < 8; i++)
         {
            if(abs(mousex()-btns[i].x) < w && abs(mousey()-btns[i].y) < h)
            {
               if(mousebuttons()) num = i;
               setlinestyle(SOLID_LINE, 1, 3);
            }
            else setlinestyle(SOLID_LINE, 1, 1);
            rectangle(btns[i].x-w, btns[i].y-h, btns[i].x+w, btns[i].y+h);
            outtextxy(btns[i].x, btns[i].y+10, btns[i].text);
         }
      }
      else
      {
         for(int i = 8; i < 11; i++)
         {
            if(abs(mousex()-btns[i].x) < w && abs(mousey()-btns[i].y) < h)
            {
               if(mousebuttons()) c = i-8;
               setlinestyle(SOLID_LINE, 1, 3);
            }
            else setlinestyle(SOLID_LINE, 1, 1);
            rectangle(btns[i].x-w, btns[i].y-h, btns[i].x+w, btns[i].y+h);
            outtextxy(btns[i].x, btns[i].y+10, btns[i].text);
         }
      }
      
      if(c != -1)
      {
         clearviewport();
         switch(num)
         {
            case 0:
            {
               fill_1(c);
               break;
            }
            case 1:
            {
               fill_2(c);
               break;
            }
            case 2:
            {
               fill_3(c);
               break;
            }
            case 3:
            {
               fill_4(c);
               break;
            }
            case 4:
            {
               fill_5(c);
               break;
            }
            case 5:
            {
               fill_6(c);
               break;
            }
            case 6:
            {
               fill_7(c);
               break;
            }
            case 7:
            {
               fill_8(c);
               break;
            }
         }
         setvisualpage(p);
         num = -1;
         c = -1;
         while(1-mousebuttons());
         while(mousebuttons());
      }
      
      setvisualpage(p);
      delay(50);
   }
   save();
   getchar();
}