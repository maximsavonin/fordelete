#define _USE_MATH_DEFINES
#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include <vector>

#include "graphics.h"

using namespace std;

class Figure
{
   protected:
      int x0 ,y0; // базовая точка
      int color, thickness;
   public:
      Figure(int x0, int y0, int color = WHITE, int thickness = 1): x0(x0), y0(y0), color(color), thickness(thickness) {}
      void setCoord(int x0, int y0){this->x0 = x0; this->y0 = y0;}
      void setColor(int color){this->color = color;}
      void setThickness(int thickness){this->thickness = thickness;}
      virtual void draw(); // нарисовать
};

class Line: public Figure
{
   private:
      int x1, y1;
   
   public:
      Line(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){}
      Line(const Line &a): Figure(a.x0, a.y0, a.color, a.thickness), x1(a.x1), y1(a.y1){}
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;}
      void draw();
};

class Rect: public Figure
{
   private:
      int x1, y1;
   public:
      Rect(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){}
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;}
      void draw();
};

class Circl: public Figure
{
   private:
      int r;

   public:
      Circl(int x, int y, int r, int color = WHITE, int thickness = 1): Figure(x, y, color, thickness), r(r){}
      void setRadius(int r){this->r = r;}
      void draw();
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Line::draw()
{
   int dx = abs(x1-x0);
   int dy = abs(y1-y0);
   int err = 0;
   if(dy < dx)
   {
      if(x0 > x1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int d = dy == 0 ? 0 : (y1-y0)/dy;
      int y = y0;
      for(int x = x0; x <= x1; x++)
      {
         for(int i = 0; i < thickness; i++)
         {
            int yd;
            yd = (i+1)/2*pow(-1, i);
            putpixel(x, y+yd, color);
         }
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
      if(y0 > y1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int d = dx == 0 ? 0 : (x1-x0)/dx;
      int x = x0;
      for(int y = y0; y <= y1; y++)
      {
         for(int i = 0; i < thickness; i++)
         {
            int xd;
            xd = (i+1)/2*pow(-1, i);
            putpixel(x+xd, y, color);
         }
         err = err+dx;
         if(err >= dy)
         {
            x += d;
            err -= dy;
         }
      }
   }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rect::draw()
{
   Line a(x0, y0, x1, y0, color, thickness);
   a.draw();
   a.setCoord(x1, y0);
   a.setCoordEnd(x1, y1);
   a.draw();
   a.setCoord(x1, y1);
   a.setCoordEnd(x0, y1);
   a.draw();
   a.setCoord(x0, y0);
   a.setCoordEnd(x0, y1);
   a.draw();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Circl::draw()
{
   for(int i = 1; i < thickness+1; i++)
   {
      int x1 = 0;
      int y1 = r+i/2*pow(-1, i-1);
      int delta = 1-2*(r+i/2*pow(-1, i-1));
      int err = 0;
      while(y1 >= x1)
      {
         putpixel(x0+x1, y0+y1, color);
         putpixel(x0+x1, y0-y1, color);
         putpixel(x0-x1, y0+y1, color);
         putpixel(x0-x1, y0-y1, color);
         putpixel(x0+y1, y0+x1, color);
         putpixel(x0+y1, y0-x1, color);
         putpixel(x0-y1, y0+x1, color);
         putpixel(x0-y1, y0-x1, color);
         err = 2*(delta+y1)-1;
         if(delta < 0 && err <= 0)
         {
            delta += 2*++x1+1;
            continue;
         }
         if(delta > 0 && err > 0)
         {
            delta -= 2*--y1+1;
            continue;
         }
         delta += 2*(++x1- --y1);
      }
   }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void drawAll(Figure *acts[], int countFigure)
{
   setfillstyle(SOLID_FILL, BLACK);
   bar(10, 70, 1190, 800);
   for(int i = 0; i < countFigure; i++)
   {
      acts[i]->draw();
   }
}

void addLine(Figure *acts[], int &countFigure, int color)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   Line a(x, y, mousex(), mousey(), color);
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts, countFigure);
      
      a.setCoord(x, y);
      a.setCoordEnd(mousex(), mousey());
      
      a.draw();
      
      setvisualpage(p);
      delay(10);
   }
   acts[countFigure] = new Line(x, y, mousex(), mousey(), color);
   countFigure++;
}

void addRect(Figure *acts[], int &countFigure, int color)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   Rect a(x, y, mousex(), mousey(), color);
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts, countFigure);
      
      a.setCoord(x, y);
      a.setCoordEnd(mousex(), mousey());
      
      a.draw();
      
      setvisualpage(p);
      delay(10);
   }
   acts[countFigure] = new Rect(x, y, mousex(), mousey(), color);
   countFigure++;
}

void addCircle(Figure *acts[], int &countFigure, int color)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   int r = 0;
   Circl a(mousex(), mousey(), r, color);
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts, countFigure);
      
      r = fmin(abs(mousex()-x)/2, abs(mousey()-y)/2);
      a.setCoord(x+(mousex()-x)/2, y+(mousey()-y)/2);
      a.setRadius(r);

      a.draw();
      
      setvisualpage(p);
      delay(10);
   }
   
   acts[countFigure] = new Circl(x+(mousex()-x)/2, y+(mousey()-y)/2, r, color);
   countFigure++;
}

int main()
{
   setlocale(LC_ALL,"Russian");
   setlocale(LC_ALL,"rus");
   srand(time(0));
   initwindow(1200, 900);
   
   setlinestyle(SOLID_LINE, 0, 1);
   setbkcolor(WHITE);
   
   srand(time(0));
   
   IMAGE *imager;
   imager = loadBMP("Red.bmp");
   
   IMAGE *imageg;
   imageg = loadBMP("Green.bmp");
   
   IMAGE *imageb;
   imageb = loadBMP("Blue.bmp");
   
   int col[3][2] = {{255, 0}, {255, 0}, {255, 0}};
   int r = 0, wrt[2] = {0};
   int n = 5, p = 0, t = 0;
   int mode = 0;
   Figure *acts[0];
   int countFigure = 0;
   
   Figure *button[3][2];
   
   for(int i = 0; i < 3; i++)
      button[i][0] = new Rect(10+i*50, 10, 59+i*50, 60, BLACK);
   button[0][1] = new Line(20, 25, 50, 45, BLACK, 3);
   button[1][1] = new Rect(65, 20, 105, 50, BLACK);
   button[2][1] = new Circl(135, 35, 21, BLACK);
   
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      for(int i = 0; i < 3; i++)
      {
         for(int k = 0; k < 2; k ++)
         {
            button[i][k]->draw();
         }
      }
      
      drawAll(acts, countFigure);
      
      if(abs(mousey()-35) <= 25 and mousebuttons())
      {
         for(int i = 0; i < 3; i++)
            if(abs(mousex()-35-i*50) <= 25) mode = i+1;
      }
      
      if(abs(mousex()-630) <= 560 and abs(mousey()-450) <= 350 and mousebuttons() and mode != 0)
      {
         switch(mode)
         {
            case 1:
            {
               addLine(acts, countFigure, COLOR(col[0][0], col[1][0], col[2][0]));
               break;
            }
            case 2:
            {
               addRect(acts, countFigure, COLOR(col[0][0], col[1][0], col[2][0]));
               break;
            }
            case 3:
            {
               addCircle(acts, countFigure, COLOR(col[0][0], col[1][0], col[2][0]));
               break;
            }
         }
      }
      
      setvisualpage(p);
      delay(50);
   }
   return 0;
}