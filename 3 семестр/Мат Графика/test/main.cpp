#include <iostream>
#include <math.h>
#include "graphics.h"

using namespace std;

struct Point
{
   int x, y;
};

void change_figure(Point romb[5], Point &param, int i, double &fi)
{
   if(i < 5)
   {
      int x0 = romb[i].x, y0 = romb[i].y;
      double a = asin(y0 / pow(x0*x0 + y0*y0, 1.0/2));
      if(x0 < 0)
      {
         a = acos(-1) - a;
      }
      a+=fi;
      int x = cos(a)*abs(param.x*x0+param.y*y0);
      int y = sin(a)*abs(param.x*x0+param.y*y0);
      int del = sqrt(pow(romb[0].x+x-mousex(), 2)+pow(romb[0].y+y-mousey(), 2));
      switch(i)
      {
         case 1:
         {
            del /= 2;
            param.y += del*sin(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            romb[0].y += del*sin(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            param.x += del*cos(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            romb[0].x += del*cos(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            break;
         }
         case 2:
         {
            del /= 2;
            param.y += del*sin(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            romb[0].y += del*sin(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            param.x += del*cos(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            romb[0].x += del*cos(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            break;
         }
         case 3:
         {
            del /= 2;
            param.y += del*sin(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            romb[0].y += del*sin(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            param.x += del*cos(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            romb[0].x += del*cos(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            break;
         }
         case 4:
         {
            del /= 2;
            param.y += del*sin(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            romb[0].y += del*sin(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            param.x += del*cos(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            romb[0].x += del*cos(a)*(romb[0].x+x-mousex())/abs(romb[0].x+x-mousex());
            break;
         }
      }
   }
   {
      int x = mousex() - romb[0].x;
      int y = mousey() - romb[0].y;
      fi = asin(y / pow(x*x + y*y, 1.0/2));
      if(x < 0)
      {
         fi = acos(-1) - fi;
      }
   }
}

int main()
{
   initwindow(600, 400);
   Point romb[5] = {{300, 200}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}};
   Point param = {50, 50};
   double fi = 0;
   int p = 0;
   int topull = 0;
   
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      
      setfillstyle(SOLID_FILL, BLACK);
      bar(0, 0, 600, 400);
      setcolor(WHITE);
      for(int i = 1; i < 4; i++)
      {
         int x0 = romb[i].x, y0 = romb[i].y, x1 = romb[i+1].x, y1 = romb[i+1].y;
         double a = asin(y0 / pow(x0*x0 + y0*y0, 1.0/2));
         double b = asin(y1 / pow(x1*x1 + y1*y1, 1.0/2));
         if(x0 < 0)
         {
            a = acos(-1) - a;
         }
         if(x1 < 0)
         {
            b = acos(-1) - b;
         }
         a+=fi;
         b+=fi;
         line(romb[0].x+cos(a)*abs(param.x*x0+param.y*y0), romb[0].y+sin(a)*abs(param.x*x0+param.y*y0), romb[0].x+cos(b)*abs(param.x*x1+param.y*y1), romb[0].y+sin(b)*abs(param.x*x1+param.y*y1));
         circle(romb[0].x+romb[i].x*(param.x+20), romb[0].y+romb[i].y*(param.y+20), 6);
      }
      int x0 = romb[4].x, y0 = romb[4].y, x1 = romb[1].x, y1 = romb[1].y;
      double a = asin(y0 / pow(x0*x0 + y0*y0, 1.0/2));
      double b = asin(y1 / pow(x1*x1 + y1*y1, 1.0/2));
      if(x0 < 0)
      {
         a = acos(-1) - a;
      }
      if(x1 < 0)
      {
         b = acos(-1) - b;
      }
      a+=fi;
      b+=fi;
      line(romb[0].x+cos(a)*abs(param.x*x0+param.y*y0), romb[0].y+sin(a)*abs(param.x*x0+param.y*y0), romb[0].x+cos(b)*abs(param.x*x1+param.y*y1), romb[0].y+sin(b)*abs(param.x*x1+param.y*y1));
      circle(romb[0].x+romb[4].x*(param.x+20), romb[0].y+romb[4].y*(param.y+20), 6);
      
      circle(romb[0].x+(param.x+8)*cos(fi), romb[0].y+(param.x+8)*sin(fi), 5);
      if(topull != 0 and mousebuttons())
      {
         change_figure(romb, param, topull, fi);
      }
      else
      {
         topull = 0;
         for(int i = 1; i < 5; i++)
         {
            if(abs(mousex()-(romb[0].x+romb[i].x*param.x)) < 7 and abs(mousey()-(romb[0].y+romb[i].y*param.y)) < 7 and mousebuttons())
            {
               topull = i;
               change_figure(romb, param, i, fi);
            }
         }
         if(abs(mousex()-(romb[0].x+(param.x+8)*cos(fi))) < 6 and abs(mousey()-(romb[0].y+(param.x+8)*sin(fi))) < 6 and mousebuttons())
         {
            topull = 5;
            change_figure(romb, param, 5, fi);
         }
      }      
      setvisualpage(p);
      delay(50);
   }
}