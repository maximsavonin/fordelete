#include <iostream>
#include "graphics.h"
#include <random>
#include <time.h>
#include <math.h>

using namespace std;

int col[3][2] = {{100, 0}, {100, 0}, {100, 0}};

struct Point
{
   int x, y;
   Point *next;
};

int t = 0, p = 0;

Point *addPoint(int x, int y, Point *one)
{
   if(one == NULL)
   {
      one = new Point;
      one->x = x;
      one->y = y;
      one->next = NULL;
      return one;
   }
   one->next = addPoint(x, y, one->next);
   return one;
}

void lineb(Point a, Point b)
{
   int dx = abs(b.x-a.x);
   int dy = abs(b.y-a.y);
   int err = 0;
   if(dy < dx)
   {
      if(a.x > b.x)
      {
         Point c = a;
         a = b;
         b = c;
      }
      int d = dy == 0 ? 0 : (b.y-a.y)/dy;
      int y = a.y;
      for(int x = a.x; x <= b.x; x++)
      {
         putpixel(x, y, WHITE);
         err = err+dy;
         if(err >= dx)
         {
            y += d;
            err -= dx;
         }
      }
   }
   else
   {
      if(a.y > b.y)
      {
         Point c = a;
         a = b;
         b = c;
      }
      int d = dx == 0 ? 0 : (b.x-a.x)/dx;
      int x = a.x;
      for(int y = a.y; y <= b.y; y++)
      {
         putpixel(x, y, WHITE);
         err = err+dx;
         if(err >= dy)
         {
            x += d;
            err -= dy;
         }
      }
   }
}

void linev(Point *a, Point *b)
{
   int dx = abs(b->x-a->x);
   int dy = abs(b->y-a->y);
   int err = 0;
   int derr = 100;
   if(dx != 0) derr = 100*(dy)/(dx);
   if(derr < 100)
   {
      if(a->x > b->x)
      {
         Point *c = a;
         a = b;
         b = c;
      }
      int y = a->y;
      int d = dy == 0 ? 0 : (b->y-a->y)/dy;
      for(int x = a->x; x <= b->x; x++)
      {
         int color = err*255/100;
         putpixel(x, y, COLOR((255-err)*col[0][0]/255, (255-err)*col[1][0]/255, (255-err)*col[2][0]/255));
         putpixel(x, y+1, COLOR(err*col[0][0]/255, err*col[1][0]/255, err*col[2][0]/255));
         err = err+derr;
         if(err >= 100)
         {
            y += d;
            err -= 100;
         }
      }
   }
   else
   {
      if(a->y > b->y)
      {
         Point *c = a;
         a = b;
         b = c;
      }
      derr = 10000/derr;
      int x = a->x;
      int d = dx == 0 ? 0 : (b->x-a->x)/dx;
      for(int y = a->y; y <= b->y; y++)
      {
         int color = err*255/100;
         putpixel(x, y, COLOR((255-err)*col[0][0]/255, (255-err)*col[1][0]/255, (255-err)*col[2][0]/255));
         putpixel(x+1, y, COLOR(err*col[0][0]/255, err*col[1][0]/255, err*col[2][0]/255));
         err = err+derr;
         if(err >= 100)
         {
            x += d;
            err -= 100;
         }
      }
   }
}

void drawpol(int x, int y, int n, int r)
{
   Point *one = NULL;
   
   for(int i = 0; i < n*2+1; i++)
   {
      int yp, xp;
      if(i%2)
      {
         xp = x+int(r*cos(i*3.14*1/n));
         yp = y+int(r*sin(i*3.14*1/n));
      }
      else
      {
         int m = (n-1)/2;
         m = m<2 ? 2 : m;
         xp = x+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*cos(i*3.14*1/n));
         yp = y+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*sin(i*3.14*1/n));
      }
      one = addPoint(xp, yp, one);
   }
   
   Point *two = one->next;
   while(two != NULL)
   {
      linev(one, two);
      one = two;
      two = one->next;
   }
}

int pole(int left, int top, int widht, int height, string Text, int data, int &wrt)
{
   if(wrt)
   {
      if(kbhit())
      {
         int key = getch();
         if(key == 13) wrt = 0;
         if(key == 8) data = data/10;
         if(key > 47 && key < 58) data = data*10+key-48;
      }
      
      setfillstyle(SOLID_FILL, WHITE);
      bar(left-5, top-5, left+widht, top+height);
      setcolor(BLACK);
      if(t > 3)
      {
         char text[30];
         sprintf(text, "%s%d", Text.c_str(), data);
         outtextxy(left, top, text);
      }
      else
      {
         char text[30];
         sprintf(text, "%s%d|", Text.c_str(), data);
         outtextxy(left, top, text);
      }
   }
   else
   {
      setfillstyle(SOLID_FILL, WHITE);
      bar(left-5, top-5, left+widht, top+height);
      setcolor(BLACK);
      char text[30];
      sprintf(text, "%s%d", Text.c_str(), data);
      outtextxy(left, top, text);
   }
   return data;
}

void fill(int x, int y)
{
   if(getpixel(x, y) == 0)
   {
      putpixel(x, y, WHITE);
      fill(x+1, y);
      fill(x-1, y);
      fill(x, y+1);
      fill(x, y-1);
   }
}

int main()
{
   setlocale(LC_ALL,"Russian");
   setlocale(LC_ALL,"rus");
   srand(time(0));
   initwindow(800, 600);
   
   setbkcolor(WHITE);
   
   IMAGE *imager;
   imager = loadBMP("Red.bmp");
   
   IMAGE *imageg;
   imageg = loadBMP("Green.bmp");
   
   IMAGE *imageb;
   imageb = loadBMP("Blue.bmp");
   
   
   int r = 100, wrt[4] = {0};
   int x = 400, y = 200;
   int n = 6;
   
   while(1)
   {
      p = 1-p;
      //setactivepage(p);
      
      setfillstyle(SOLID_FILL, BLACK);
      setcolor(WHITE);
      rectangle(-1, -1, 801, 601);
      bar(0, 0, 800, 600);
      
      if(mousebuttons() && abs(95-mousex()) < 65 && abs(560-mousey()) < 15) 
      {
         for(int i = 0; i < 4; i++) wrt[i] = 0;
         wrt[0] = 1;
      }
      if(mousebuttons() && abs(270-mousex()) < 85 && abs(560-mousey()) < 15)
      {
         for(int i = 0; i < 4; i++) wrt[i] = 0;
         wrt[1] = 1;
      }
      if(mousebuttons() && abs(470-mousex()) < 85 && abs(560-mousey()) < 15)
      {
         for(int i = 0; i < 4; i++) wrt[i] = 0;
         wrt[2] = 1;
      }
      if(mousebuttons() && abs(677-mousex()) < 92 && abs(560-mousey()) < 15)
      {
         for(int i = 0; i < 4; i++) wrt[i] = 0;
         wrt[3] = 1;
      }
      
      r = pole(30, 550, 125, 25, "Радиус: ", r, wrt[0]);
      x = pole(190, 550, 165, 25, "X координата: ", x, wrt[1]);
      y = pole(390, 550, 165, 25, "Y координата: ", y, wrt[2]);
      n = pole(590, 550, 180, 25, "количество углов: ", n, wrt[3]);
      
      putimage(7, 500, imager, COPY_PUT);
      putimage(270, 500, imageg, COPY_PUT);
      putimage(533, 500, imageb, COPY_PUT);
      
      setfillstyle(SOLID_FILL, WHITE);
      bar(col[0][0]+4, 500, col[0][0]+10, 529);
      bar(col[1][0]+267, 500, col[1][0]+273, 529);
      bar(col[2][0]+530, 500, col[2][0]+536, 529);
      
      if(mousebuttons())
      {
         if(abs(mousex()-col[0][0]-7) < 4 and abs(mousey() - 515) < 15 and col[1][1] != 1 and col[2][1] != 1)
         {
            col[0][1] = 1;
         }
         if(abs(mousex()-col[1][0]-270) < 4 and abs(mousey() - 515) < 15 and col[0][1] != 1 and col[2][1] != 1)
         {
            col[1][1] = 1;
         }
         if(abs(mousex()-col[2][0]-533) < 4 and abs(mousey() - 515) < 15 and col[0][1] != 1 and col[1][1] != 1)
         {
            col[2][1] = 1;
         }
      }
      else
      {
         col[0][1] = 0;
         col[1][1] = 0;
         col[2][1] = 0;
      }
      
      if(col[0][1]) 
      {
         col[0][0] = mousex()-7;
         col[0][0] = (col[0][0]+abs(col[0][0]))/2;
         if(col[0][0] > 255) col[0][0] = 255;
      }
      if(col[1][1]) 
      {
         col[1][0] = mousex()-270;
         col[1][0] = (col[1][0]+abs(col[1][0]))/2;
         if(col[1][0] > 255) col[1][0] = 255;
      }
      if(col[2][1]) 
      {
         col[2][0] = mousex()-533;
         col[2][0] = (col[2][0]+abs(col[2][0]))/2;
         if(col[2][0] > 255) col[2][0] = 255;
      }
      
      t = t+1;
      t = t%8;
      
      
      drawpol(x, y, n, r);
      fill(x, y);
      
      //setvisualpage(p);
      delay(50);
   }
   
   getch();
}