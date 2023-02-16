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
   Point *next = NULL;
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
   lineCha lineCh;
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
   
   lineBez but5 = lineBez(BLACK, 2);
   but5.add(220, 20);
   but5.add(250, 20);
   but5.add(220, 50);
   but5.add(250, 50);
   but5.setStep(0.02);
   
   lineCha but6 = lineCha(BLACK, 2);
   but6.add(270, 20);
   but6.add(300, 20);
   but6.add(270, 50);
   but6.add(300, 50);
         
   lineB butsave[18] = {lineB(1150, 20, 1177, 20, BLACK, 1),
                                  lineB(1177, 20, 1180, 23, BLACK, 1),
                                  lineB(1180, 23, 1180, 50, BLACK, 1),
                                  lineB(1180, 50, 1150, 50, BLACK, 1),
                                  lineB(1150, 50, 1150, 20, BLACK, 1),
                                  lineB(1155, 20, 1155, 28, BLACK, 1),
                                  lineB(1155, 28, 1175, 28, BLACK, 1),
                                  lineB(1175, 28, 1175, 20, BLACK, 1),
                                  lineB(1170, 22, 1173, 22, BLACK, 1),
                                  lineB(1173, 22, 1173, 26, BLACK, 1),
                                  lineB(1173, 26, 1170, 26, BLACK, 1),
                                  lineB(1170, 26, 1170, 22, BLACK, 1),
                                  lineB(1155, 50, 1155, 31, BLACK, 1),
                                  lineB(1155, 31, 1175, 31, BLACK, 1),
                                  lineB(1175, 31, 1175, 50, BLACK, 1),
                                  lineB(1157, 35, 1173, 35, BLACK, 1),
                                  lineB(1157, 40, 1173, 40, BLACK, 1),
                                  lineB(1157, 45, 1173, 45, BLACK, 1)};
                                 
   lineB butclear[13] = {lineB(1130, 20, 1115, 35, BLACK, 5),
                                 lineB(1116, 36, 1099, 49, BLACK, 1),
                                 lineB(1114, 34, 1101, 51, BLACK, 1),
                                 lineB(1116, 36, 1098, 48, BLACK, 1),
                                 lineB(1114, 34, 1102, 52, BLACK, 1),
                                 lineB(1117, 37, 1097, 47, BLACK, 1),
                                 lineB(1113, 33, 1103, 53, BLACK, 1),
                                 lineB(1117, 37, 1096, 46, BLACK, 1),
                                 lineB(1113, 33, 1104, 54, BLACK, 1),
                                 lineB(1118, 38, 1095, 45, BLACK, 1),
                                 lineB(1112, 32, 1105, 55, BLACK, 1),
                                 lineB(1118, 38, 1094, 44, BLACK, 1),
                                 lineB(1112, 32, 1106, 56, BLACK, 1)};
   
   lineB butback[3] = {lineB(1080, 35, 1050, 35, BLACK, 3),
                                 lineB(1050, 35, 1065, 20, BLACK, 3),
                                 lineB(1050, 35, 1065, 50, BLACK, 3)};
   act acts[1000];
   int countDo = 0;
   int start[2] = {0}, end[2] = {0};
   
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      drawAll(acts, countDo);
      
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
      rectangle(260, 10, 310, 60);
      but6.draw();
      
      setcolor(BLACK);
      rectangle(1140, 10, 1190, 60);
      for(int i = 0; i < 18; i++)
      {
         butsave[i].draw();
      }
      
      setcolor(BLACK);
      rectangle(1090, 10, 1140, 60);
      for(int i = 0; i < 13; i++)
      {
         butclear[i].draw();
      }
      
      setcolor(BLACK);
      rectangle(1040, 10, 1090, 60);
      for(int i = 0; i < 3; i++)
      {
         butback[i].draw();
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
         if(abs(mousex()-285) <= 25)
         {
            mode = 6;
         }
      }
      
      if(abs(mousex()-630) <= 560 and abs(mousey()-450) <= 350 and mousebuttons() and mode != 0)
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
            case 6:
            {
               Point all[100];
               int brea = 0;
               int count = 0;
               int numer = -1;
               int mousepos[2];
               acts[countDo].num = 6;
               acts[countDo].lineCh = lineCha(COLOR(col[0][0], col[1][0], col[2][0]));
               while(1)
               {
                  p = 1-p;
                  setactivepage(p);
                  
                  drawAll(acts, countDo);
                  mousepos[0] = mousex();
                  mousepos[1] = mousey();
                  while(1-mousebuttons() or abs(mousepos[0]-600) > 590 or abs(mousepos[1]-435) > 365)
                  {
                     mousepos[0] = mousex();
                     mousepos[1] = mousey();
                     numer = -1;
                     if(kbhit()) if(getch() == 13) 
                     {
                        brea = 1;
                        break;
                     }
                  }
                  if(brea) 
                  {
                     countDo++;
                     delay(200);
                     break;
                  }
                  for(int i = 0; i < count; i++)
                  {
                     if(abs(mousepos[0]-all[i].x) <= 7 and abs(mousepos[1]-all[i].y) <= 7)
                     {
                        numer = i;
                        break;
                     }
                  }
                  if(numer == -1)
                  {
                     all[count] = {mousepos[0], mousepos[1]};
                     count++;
                     while(mousebuttons());
                  }
                  else
                  {
                     all[numer].x = mousepos[0];
                     all[numer].y = mousepos[1];
                  }
                  acts[countDo].lineCh.delRoot();
                  for(int i = 0; i < count; i++)
                  {
                     circl dot = circl(all[i].x, all[i].y, 5);
                     dot.draw();
                     acts[countDo].lineCh.add(all[i].x, all[i].y);
                  }
                  acts[countDo].lineCh.draw();
                  setvisualpage(p);
                  delay(10);
               }
            }
         }
      }
      t = t+1;
      t = t%8;
      
      setvisualpage(p);
      if(abs(mousey()-35) <= 25 and mousebuttons())
      {
         if(abs(mousex()-1165) <= 25)
         {
            save(10, 70, 1190, 800);
         }
         if(abs(mousex()-1115) <= 25)
         {
            countDo = 0;
         }
         if(abs(mousex()-1065) <= 25 and countDo > 0)
         {
            countDo = countDo-1;
            while(mousebuttons());
         }
      }
      delay(10);
   }
   
   getch();
}