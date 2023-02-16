#define _USE_MATH_DEFINES
#include <iostream>
#include <random>
#include <time.h>
#include <math.h>

#include "graphics.h"
#include "control.h"
#include "draw.h"

using namespace std;

struct Point
{
   int x, y;
};

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
};

void pefog(int pef[100], int k, int n)
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
   
   lineB but1 = lineB(20, 25, 50, 45, BLACK, 3);
   star but2 = star(85, 35, 24, 5, 0, BLACK);
   circl but3 = circl(135, 35, 21, BLACK);
   lineB but4[5];
   but4[0].setStart(160, 43);
   but4[0].setEnd(177, 60);
   but4[0].setColor(BLACK);
   but4[0].setWidth(2);
   but4[1].setStart(160, 27);
   but4[1].setEnd(193, 60);
   but4[1].setColor(BLACK);
   but4[1].setWidth(2);
   but4[2].setStart(160, 10);
   but4[2].setEnd(210, 60);
   but4[2].setColor(BLACK);
   but4[2].setWidth(2);
   but4[3].setStart(177, 10);
   but4[3].setEnd(210, 43);
   but4[3].setColor(BLACK);
   but4[3].setWidth(2);
   but4[4].setStart(193, 10);
   but4[4].setEnd(210, 26);
   but4[4].setColor(BLACK);
   but4[4].setWidth(2);
   lineBez but5 = lineBez(BLACK, 3);
   but5.add(220, 20);
   but5.add(250, 20);
   but5.add(220, 50);
   but5.add(250, 50);
   but5.setStep(0.02);
         
   lineB butsave[18] = {lineB(1150, 20, 1177, 20, BLACK, 1),
                                  lineB(1177, 20, 1180, 23, BLACK, 1),
                                  lineB(1180, 23, 1180, 50, BLACK, 1),
                                  lineB(1180, 50, 1150, 50, BLACK, 1),
                                  lineB(1150, 50, 1150, 20, BLACK, 1), // рамка
                                  lineB(1155, 20, 1155, 28, BLACK, 1),
                                  lineB(1155, 28, 1175, 28, BLACK, 1),
                                  lineB(1175, 28, 1175, 20, BLACK, 1),
                                  lineB(1170, 22, 1173, 22, BLACK, 1),
                                  lineB(1173, 22, 1173, 26, BLACK, 1),
                                  lineB(1173, 26, 1170, 26, BLACK, 1),
                                  lineB(1170, 26, 1170, 22, BLACK, 1), //
                                  lineB(1155, 50, 1155, 31, BLACK, 1),
                                  lineB(1155, 31, 1175, 31, BLACK, 1),
                                  lineB(1175, 31, 1175, 50, BLACK, 1), //
                                  lineB(1157, 35, 1173, 35, BLACK, 1),
                                  lineB(1157, 40, 1173, 40, BLACK, 1),
                                  lineB(1157, 45, 1173, 45, BLACK, 1)};
   
   act acts[1000];
   int countDo = 0;
   int start[2] = {0}, end[2] = {0};
   
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
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
         }
      }
      
      setcolor(BLACK);
      rectangle(10, 10, 60, 60);
      but1.draw();
      
      setcolor(BLACK);
      rectangle(60, 10, 110, 60);
      but2.draw();
      
      setcolor(BLACK);
      rectangle(110, 10, 160, 60);
      but3.draw();

      setcolor(BLACK);
      rectangle(160, 10, 210, 60);
      for(int i = 0; i < 5; i++) but4[i].draw();
      
      setcolor(BLACK);
      rectangle(210, 10, 260, 60);
      but5.draw();
      
      setcolor(BLACK);
      rectangle(1140, 10, 1190, 60);
      for(int i = 0; i < 18; i++)
      {
         butsave[i].draw();
      }
      
      lineColor(10, 810, col, 0, imager);
      lineColor(10, 840, col, 1, imageg);
      lineColor(10, 870, col, 2, imageb);

      if(abs(mousey()-35) <= 25 and mousebuttons())
      {
         if(abs(mousex()-35) <= 25)
         {
            mode = 1;
         }
         if(abs(mousex()-85) <= 25)
         {
            mode = 2;
         }
         if(abs(mousex()-135) <= 25)
         {
            mode = 3;
         }
         if(abs(mousex()-185) <= 25)
         {
            mode = 4;
         }
         if(abs(mousex()-235) <= 25)
         {
            mode = 5;
         }
      }
      
      if(abs(mousex()-630-r) <= 560 and abs(mousey()-450-r) <= 350 and mousebuttons() and mode != 0)
      {
         switch(mode)
         {
            case 1:
            {
               addLine(acts, countDo, COLOR(col[0][0], col[1][0], col[2][0]));
               break;
            }
            case 2:
            {
               addStar(acts, countDo, COLOR(col[0][0], col[1][0], col[2][0]));
               break;
            }
            case 3:
            {
               addCircle(acts, countDo, COLOR(col[0][0], col[1][0], col[2][0]));
               break;
            }
            case 4:
            {
               int x = mousex();
               int y = mousey();
               fillIn(x, y, COLOR(col[0][0], col[1][0], col[2][0]), getpixel(x, y));
               while(mousebuttons());
               acts[countDo].num = 4;
               acts[countDo].fil.x = x;
               acts[countDo].fil.y = y;
               acts[countDo].fil.color = COLOR(col[0][0], col[1][0], col[2][0]);
               countDo++;
               break;
            }
            case 5:
            {
               addLineBez(acts, countDo, COLOR(col[0][0], col[1][0], col[2][0]));
            }
         }
      }
      /*
      if(mousebuttons() && abs(95-mousex()) < 65 && abs(560-mousey()) < 15) 
      {
         for(int i = 0; i < 2; i++) wrt[i] = 0;
         wrt[0] = 1;
      }
      if(mousebuttons() && abs(677-mousex()) < 92 && abs(560-mousey()) < 15)
      {
         for(int i = 0; i < 2; i++) wrt[i] = 0;
         wrt[1] = 1;
      }
      
      r = pole(30, 550, 125, 25, "Радиус: ", r, wrt[0], t);
      n = pole(590, 550, 180, 25, "количество углов: ", n, wrt[1], t);
      
      lineColor(7, col, 0, imager);
      lineColor(270, col, 1, imageg);
      lineColor(533, col, 2, imageb);
      if(butSave(650, 0)) save();
      */
      t = t+1;
      t = t%8;
      
      setvisualpage(p);
      if(abs(mousex()-1165) <= 25 and abs(mousey()-35) <= 25 and mousebuttons())
      {
         save(10, 70, 1190, 800);
      }
      delay(10);
   }
   
   getch();
}