#include <math.h>
#include <iostream>
#include "graphics.h"
#include "draw.h"

using namespace std;

struct Point
{
   int x, y;
   Point *next = NULL;
};

Point *addPoint(int x, int y, Point *root)
{
   if(root == NULL)
   {
      root = new Point;
      root->x = x;
      root->y = y;
      root->next = NULL;
      return root;
   }
   root->next = addPoint(x, y, root->next);
   return root;
}

// line ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


lineB::lineB(int x, int y, int x0, int y0)
{
   x1 = x;
   y1 = y;
   x2 = x0;
   y2 = y0;
   color = WHITE;
   width = 1;
}

lineB::lineB(int x, int y, int x0, int y0, int color0)
{
   x1 = x;
   y1 = y;
   x2 = x0;
   y2 = y0;
   color = color0;
   width = 1;
}

lineB::lineB(int x, int y, int x0, int y0, int color0, int width0)
{
   x1 = x;
   y1 = y;
   x2 = x0;
   y2 = y0;
   color = color0;
   width = width0;
}

void lineB::setColor(int color0)
{
   color = color0;
}

void lineB::setStart(int x, int y)
{
   x1 = x;
   y1 = y;
}

void lineB::setEnd(int x, int y)
{
   x2 = x;
   y2 = y;
}

void lineB::setWidth(int w)
{
   width = w;
}

void lineB::draw()
{
   int dx = abs(x2-x1);
   int dy = abs(y2-y1);
   int err = 0;
   if(dy < dx)
   {
      if(x1 > x2)
      {
         int a = x1;
         x1 = x2;
         x2 = a;
         a = y1;
         y1 = y2;
         y2 = a;
      }
      int d = dy == 0 ? 0 : (y2-y1)/dy;
      int y = y1;
      for(int x = x1; x <= x2; x++)
      {
         for(int i = 0; i < width; i++)
         {
            int y0;
            y0 = (i+1)/2*pow(-1, i);
            putpixel(x, y+y0, color);
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
      if(y1 > y2)
      {
         int a = x1;
         x1 = x2;
         x2 = a;
         a = y1;
         y1 = y2;
         y2 = a;
      }
      int d = dx == 0 ? 0 : (x2-x1)/dx;
      int x = x1;
      for(int y = y1; y <= y2; y++)
      {
         for(int i = 0; i < width; i++)
         {
            int x0;
            x0 = (i+1)/2*pow(-1, i);
            putpixel(x+x0, y, color);
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

// star ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void star::creatStar()
{
   int x0, y0;
   int m = (n-1)/2;
   m = m<2 ? 2 : m;
   x0 = x+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*cos(fi));
   y0 = y+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*sin(fi));
   for(int i = 1; i < n*2+1; i++)
   {
      int y1, x1;
      if(i%2)
      {
         x1 = x+int(r*cos(i*3.14*1/n+fi));
         y1 = y+int(r*sin(i*3.14*1/n+fi));
      }
      else
      {
         x1 = x+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*cos(i*3.14*1/n+fi));
         y1 = y+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*sin(i*3.14*1/n+fi));
      }
      lines[i-1].setWidth(1);
      lines[i-1].setStart(x0, y0);
      lines[i-1].setEnd(x1, y1);
      x0 = x1;
      y0 = y1;
   }
   lineColor();
}

void star::lineColor()
{
   for(int i = 0; i < n*2; i++)
   {
      lines[i].setColor(colorLine);
   }
}

star::star(int x0, int y0, int r0, int n0)
{
   x = x0;
   y = y0;
   r = r0;
   n = n0;
   fi = 0;
   colorLine = WHITE;
   colorFill = WHITE;
   creatStar();
}

star::star(int x0, int y0, int r0, int n0, float fi0)
{
   x = x0;
   y = y0;
   r = r0;
   n = n0;
   fi = fi0;
   colorLine = WHITE;
   colorFill = WHITE;
   creatStar();
}

star::star(int x0, int y0, int r0, int n0, float fi0, int colorLine0)
{
   x = x0;
   y = y0;
   r = r0;
   n = n0;
   fi = fi0;
   colorLine = colorLine0;
   colorFill = WHITE;
   creatStar();
}

star::star(int x0, int y0, int r0, int n0, float fi0, int colorLine0, int colorFill0)
{
   x = x0;
   y = y0;
   r = r0;
   n = n0;
   fi = fi0;
   colorLine = colorLine0;
   colorFill = colorFill0;
   creatStar();
}

star::star(const star &obj)
{
   x = obj.x;
   y = obj.y;
   r = obj.r;
   n = obj.n;
   fi = obj.fi;
   colorLine = obj.colorLine;
   colorFill = obj.colorFill;
   for(int i = 0; i < n*2; i++) lines[i] = obj.lines[i];
   creatStar();
   
}

void star::setRadius(int r0)
{
   r = r0;
   creatStar();
}

void star::setCenter(int x0, int y0)
{
   x = x0;
   y = y0; 
   creatStar();
}

void star::setNumCorners(int n0)
{
   n = n0;
   creatStar();
}

void star::setColorLine(int color0)
{
   colorLine = color0;
}

void star::setColorFill(int color0)
{
   colorFill = color0;
}

void star::setCorners(int fi0)
{
   fi = fi0;
   creatStar();
}

void star::draw()
{
   for(int i = 0; i < n*2; i++)
   {
      lines[i].draw();
   }
}

void star::fill()
{
   setfillstyle(SOLID_FILL, colorFill);
   fillIn(x, y, colorFill, getpixel(x, y));
}

// circle  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

circl::circl(int x0, int y0, int r0)
{
   x = x0;
   y = y0;
   r = r0;
   colorLine = WHITE;
   colorFill = WHITE;
}

circl::circl(int x0, int y0, int r0, int colorLine0)
{
   x = x0;
   y = y0;
   r = r0;
   colorLine = colorLine0;
   colorFill = WHITE;
}

circl::circl(int x0, int y0, int r0, int colorLine0, int colorFill0)
{
   x = x0;
   y = y0;
   r = r0;
   colorLine = colorLine0;
   colorFill = colorFill0;
}

void circl::setCenter(int x0, int y0)
{
   x = x0;
   y = y0;
}

void circl::setRadius(int r0)
{
   r = r0;
}

void circl::setColorLine(int color0)
{
   colorLine = color0;
}

void circl::setColorFill(int color0)
{
   colorFill = color0;
}

void circl::draw()
{
   int thickness = 1;
   for(int i = 1; i < thickness+1; i++)
   {
      int x1 = 0;
      int y1 = r+i/2*pow(-1, i-1);
      int delta = 1-2*(r+i/2*pow(-1, i-1));
      int err = 0;
      while(y1 >= x1)
      {
         putpixel(x+x1, y+y1, colorLine);
         putpixel(x+x1, y-y1, colorLine);
         putpixel(x-x1, y+y1, colorLine);
         putpixel(x-x1, y-y1, colorLine);
         putpixel(x+y1, y+x1, colorLine);
         putpixel(x+y1, y-x1, colorLine);
         putpixel(x-y1, y+x1, colorLine);
         putpixel(x-y1, y-x1, colorLine);
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

void circl::fill()
{
   setfillstyle(SOLID_FILL, colorFill);
   fillIn(x, y, colorFill, getpixel(x, y));
}

//------------

void lineBez::pefog(int pef[100], int k, int n)
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

lineBez::lineBez()
{
   color = WHITE;
   width = 1;
}

lineBez::lineBez(int color0)
{
   color = color0;
   width = 1;
}

lineBez::lineBez(int color0, int width0)
{
   color = color0;
   width = width0;
   
}

void lineBez::add(int x0, int y0)
{
   data[n][0] = x0;
   data[n][1] = y0;
   n++;
}

void lineBez::setColor(int color0)
{
   color = color0;
}

void lineBez::setWidth(int width0)
{
   width = width0;
}

void lineBez::setStep(double step0)
{
   step = step0;
}

void lineBez::draw()
{
   if(n>1)
   {
      int pef[100] = {0};
      pef[0] = 1;
      pef[1] = 1;
      pefog(pef, 2, n);
      Point b = {data[0][0], data[0][1]};
      for(double t = step; t <= 1; t += step)
      {
         Point a = {0, 0};
         for(int i = 0; i < n; i++)
         {
            a.x += pef[i]*pow(1-t, n-i-1)*pow(t, i)*data[i][0];
            a.y += pef[i]*pow(1-t, n-i-1)*pow(t, i)*data[i][1];
         }
         lineB c = lineB(b.x, b.y, a.x, a.y, color, width);
         c.draw();
         b = a;
      }
      lineB c = lineB(b.x, b.y, data[n-1][0], data[n-1][1], color, width);
      c.draw();
   }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Point *lineCha::chaikin(Point *root)
{
   if(root == NULL) return NULL;
   if(root->next == NULL) return root;
   Point *r = root->next;
   Point *a, *b;
   a = new Point;
   b = new Point;
   a->x = root->x+(r->x-root->x)/4;
   a->y = root->y+(r->y-root->y)/4;
   
   b->x = root->x+(r->x-root->x)*3/4;
   b->y = root->y+(r->y-root->y)*3/4;
   b->next = chaikin(r);
   a->next = b;
   return a;
}

void lineCha::drawL(Point *root)
{
   if(root == NULL) return;
   if(root->next == NULL) return;
   Point *a = root->next;
   lineB l = lineB(root->x, root->y, a->x, a->y, color, width);
   l.draw();
   drawL(a);
}

void lineCha::del(Point *tree)
{
   if(tree == NULL) return;
   del(tree->next);
   delete tree;
}

lineCha::lineCha()
{
   color = WHITE;
   width = 1;
   root = NULL;
}

lineCha::lineCha(int color0)
{
   color = color0;
   width = 1;
   root = NULL;
}

lineCha::lineCha(int color0, int width0)
{
   color = color0;
   width = width0;
   root = NULL;
}

lineCha::~lineCha()
{
   del(root);
}

void lineCha::delRoot()
{
   del(root);
   root = NULL;
}

void lineCha::add(int x, int y)
{
   root = addPoint(x, y, root);
}

void lineCha::setColor(int color0)
{
   color = color0;
}

void lineCha::setWidth(int width0)
{
   width = width0;
}

void lineCha::draw()
{
   Point *r = chaikin(root);
   r->x = root->x;
   r->y = root->y;
   for(int i = 0; i < 5; i++)
   {
      r = chaikin(r);
      r->x = root->x;
      r->y = root->y;
   }
   setcolor(WHITE);
   drawL(r);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Fill
{
   int x, y;
   int color;
};

struct act
{
   int num = 0;
   lineB lin;
   star sta;
   circl circ;
   Fill fil;
   lineBez linBz;
   lineCha lineCh;
};

void fillIn(int x, int y, int colorFill, int colorNow)
{
   if(getpixel(x, y) == colorNow)
   {
      putpixel(x, y, colorFill);
      fillIn(x+1, y, colorFill, colorNow);
      fillIn(x-1, y, colorFill, colorNow);
      fillIn(x, y+1, colorFill, colorNow);
      fillIn(x, y-1, colorFill, colorNow);
   }
}

void drawAll(act acts[1000], int countDo)
{
   setfillstyle(SOLID_FILL, BLACK);
   bar(10, 70, 1190, 800);
   for(int i = 0; i < countDo; i++)
   {
      switch(acts[i].num)
      {
         case 1: acts[i].lin.draw(); break;
         case 2: acts[i].sta.draw(); break;
         case 3: acts[i].circ.draw(); break;
         case 4: fillIn(acts[i].fil.x, acts[i].fil.y, acts[i].fil.color, getpixel(acts[i].fil.x, acts[i].fil.y)); break;
         case 5: acts[i].linBz.draw(); break;
         case 6: acts[i].lineCh.draw(); break;
      }
   }
}

void addLine(act acts[1000], int &countDo, int color)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   acts[countDo].num = 1;
   acts[countDo].lin = lineB(x, y, mousex(), mousey(), color);
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts, countDo);
      
      acts[countDo].lin.setStart(x, y);
      acts[countDo].lin.setEnd(mousex(), mousey());
      
      acts[countDo].lin.draw();
      
      setvisualpage(p);
      delay(10);
   }
   countDo++;
}

void addStar(act acts[1000], int &countDo, int color)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   acts[countDo].num = 2;
   acts[countDo].sta = star(mousex(), mousey(), 0, 5, 0, color);
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts, countDo);
      
      acts[countDo].sta.setCenter(x+(mousex()-x)/2, y+(mousey()-y)/2);
      acts[countDo].sta.setRadius(fmin(abs(mousex()-x)/2, abs(mousey()-y)/2));
      
      acts[countDo].sta.draw();
      
      setvisualpage(p);
      delay(10);
   }
   countDo++;
}

void addCircle(act acts[1000], int &countDo, int color)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   acts[countDo].num = 3;
   acts[countDo].circ = circl(mousex(), mousey(), 0, color);
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts, countDo);
      
      acts[countDo].circ.setCenter(x+(mousex()-x)/2, y+(mousey()-y)/2);
      acts[countDo].circ.setRadius(fmin(abs(mousex()-x)/2, abs(mousey()-y)/2));
      
      acts[countDo].circ.draw();
      
      setvisualpage(p);
      delay(10);
   }
   
   countDo++;
}

void addLineBez(act acts[1000], int &countDo, int color)
{
   Point all[100];
   int brea = 0, p = 0;
   int count = 0;
   int numer = -1;
   while(1)
   {
      lineBez a = lineBez(color);
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts, countDo);
      
      while(1-mousebuttons() or abs(mousex()-600) > 590 or abs(mousey()-435) > 365)
      {
         numer = -1;
         if(kbhit()) if(getch() == 13) 
         {
            brea = 1;
            break;
         }
      }
      if(brea) 
      {
         for(int i = 0; i < count; i++)
         {
            a.add(all[i].x, all[i].y);
         }
         acts[countDo].num = 5;
         acts[countDo].linBz = a;
         countDo++;
         delay(200);
         break;
      }
      for(int i = 0; i < count; i++)
      {
         if(abs(mousex()-all[i].x) <= 7 and abs(mousey()-all[i].y) <= 7)
         {
            numer = i;
            break;
         }
      }
      if(numer == -1)
      {
         all[count] = {mousex(), mousey()};
         count++;
         while(mousebuttons());
      }
      else
      {
         all[numer].x = mousex();
         all[numer].y = mousey();
      }
      for(int i = 0; i < count; i++)
      {
         circl dot = circl(all[i].x, all[i].y, 5);
         dot.draw();
         a.add(all[i].x, all[i].y);
      }
      a.draw();
      
      setvisualpage(p);
      delay(10);
   }
}

void save(int left = 0, int top = 0, int width = 0, int height = 0)
{
   IMAGE *output;
   
   if(width == 0)
   {
      width = getmaxx();
      height = getmaxy();
   }
   width++;
   height++;
   output = createimage(width-left, height-top);
   
   getimage(left, top, width-1, height-1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}