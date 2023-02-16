#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graphics.h"
#define startx 150
#define starty 200
#define cell 90

int p = 0, w = 5, h = 4;
int map[4][5];
int bord[4] = {0, 0, 4, 3};

void new_game()
{
   for(int i = 0; i < 4; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         map[i][j] = 1;
      }
   }
   map[1][2] = 2;
}

void draw_game(int l[2], int point[8])
{
   p = 1-p;
   setactivepage(p);
   clearviewport();
   
   setlinestyle(SOLID_LINE, 1, 4);
   for(int i = 0; i < 4; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         if(map[i][j] != 0)
         {
            setfillstyle(1, COLOR(190, 100, 20));
            bar(startx+j*cell, starty+i*cell, startx+(1+j)*cell, starty+(1+i)*cell);
            setcolor(COLOR(130, 60, 0));
            rectangle(startx+j*cell, starty+i*cell, startx+(1+j)*cell, starty+(1+i)*cell);
            rectangle(startx+j*cell+20, starty+i*cell+20, startx+(1+j)*cell-20, starty+(1+i)*cell-20);
         }
         if(map[i][j] == 2)
         {
            setcolor(RED);
            line(startx+j*cell+20, starty+i*cell+20, startx+(1+j)*cell-20, starty+(1+i)*cell-20);
            line(startx+j*cell+20, starty+(1+i)*cell-20, startx+(1+j)*cell-20, starty+i*cell+20);
         }
      }
   }
   if(l[1] == -1)
   {
      if(l[0] != -1)
      {
         setlinestyle(SOLID_LINE, 1, 5);
         setcolor(COLOR(0, 200, 0));
         rectangle(startx+point[l[0]*2]*cell, starty+point[l[0]*2+1]*cell, startx+(1+point[l[0]*2])*cell, starty+(1+point[l[0]*2+1])*cell);
      }
   }
   else
   {
      setlinestyle(SOLID_LINE, 1, 5);
      setcolor(COLOR(0, 200, 0));
      rectangle(startx+point[l[0]*2]*cell, starty+point[l[0]*2+1]*cell, startx+(1+point[l[1]*2])*cell, starty+(1+point[l[1]*2+1])*cell);
   }
   
   setvisualpage(p);
}

int main()
{
   int mou[2];
   int l[2] = {-1};
   initwindow(1000, 800,"Ним",10,20);
   setbkcolor(WHITE);
   srand(time(0));
   new_game();
   while(1)
   {
      int point[8] = {bord[0], bord[1], bord[2], bord[1], bord[2],bord[3], bord[0], bord[3]};
      mou[0] = (mousex()-startx)/cell;
      mou[1] = (mousey()-starty)/cell;
      if(l[1] == -1)
      {
         for(int i = 0; i < 4; i++)
         {
            if(mou[0] == point[i*2] && mou[1] == point[i*2+1])
            {
               l[0] = i;
            }
         }
         if(mousebuttons())
         {
            for(int i = 0; i < 4; i++)
            {
               if(mou[i%2] == point[i*2+i%2])
               {
                  l[1] = i;
               }
            }
         }
      }
      else
      {
         for(int i = 0; i < 4; i++)
         {
            if(mou[i%2] == point[i*2+i%2])
            {
               l[1] = i;
            }
         }
         if(mousebuttons())
         {
            l[1] = -1;
         }
      }
      draw_game(l, point);
   }
}