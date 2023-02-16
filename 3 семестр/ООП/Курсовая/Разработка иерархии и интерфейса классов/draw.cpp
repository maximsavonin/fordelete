#define _USE_MATH_DEFINES

#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include <vector>

#include "graphics.h"
#include "draw.h"

using namespace std;

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

void FillRec::draw()
{
   Rect::draw();
   setfillstyle(SOLID_FILL, fillColor);
   floodfill((x1-x0)/2+x0, (y1-y0)/2+y0, color);
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

void FillCircl::draw()
{
   Circl::draw();
   setfillstyle(SOLID_FILL, fillColor);
   floodfill(x0, y0, color);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Curve::pefog(int pef[100], int k, int n)
{
   if(n <= k) return;
   int a[100] = {0};
   for(int i = 0; i < k; i++) a[i] = pef[i];
   for(int i = 1; i < k+1; i++)
   {
      pef[i] = a[i-1]+a[i];
   }
   pefog(pef, k+1, n);
}

void Curve::setPoints(vector<vector<int>> data)
{
   for(int i = 0; i < data.size(); i++)
   {
      this->data.push_back({0, 0});
      this->data[i][0] = data[i][0];
      this->data[i][1] = data[i][1];
   }
}

void Curve::draw()
{
   if(data.size()>1)
   {
      int pef[100] = {0};
      pef[0] = 1;
      pef[1] = 1;
      pefog(pef, 2, data.size());
      Point b = {data[0][0], data[0][1]};
      for(double t = step; t <= 1; t += step)
      {
         Point a = {0, 0};
         for(int i = 0; i < data.size(); i++)
         {
            a.x += pef[i]*pow(1-t, data.size()-i-1)*pow(t, i)*data[i][0];
            a.y += pef[i]*pow(1-t, data.size()-i-1)*pow(t, i)*data[i][1];
         }
         Line c = Line(b.x, b.y, a.x, a.y, color, thickness);
         c.draw();
         b = a;
      }
      Line c = Line(b.x, b.y, data[data.size()-1][0], data[data.size()-1][1], color, thickness);
      c.draw();
   }
   if(data.size() == 1) for(int i = 0; i < thickness; i++)
   {
      putpixel(data[0][0]+i, data[0][1], color);
      putpixel(data[0][0], data[0][1]+i, color);
      putpixel(data[0][0]-i, data[0][1], color);
      putpixel(data[0][0], data[0][1]-i, color);
   }
}

void outcoord()
{
   if(mousex() >= 10 and mousex() <= 1190 and mousey() >= 70 and mousey() <= 800)
   {
      string str = '(' + to_string(mousex()-10) + ';' + to_string(mousey()-70) + ')';
      outtextxy(1150, 880, str.c_str());
   }
}

void drawAll(vector<Figure*> acts)
{
   setfillstyle(SOLID_FILL, BLACK);
   bar(10, 70, 1190, 800);
   for(int i = 0; i < acts.size(); i++)
   {
      acts[i]->draw();
   }
   outcoord();
}