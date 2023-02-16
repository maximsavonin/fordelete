#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graphics.h"
#define hlab 15
#define wlab 15

int width = 800, height = 800; //размер экрана
int end[3] = {0};
int p = 0;

typedef struct Cell
{
   int Left = 1, Bottom = 1;
   int flag = 0;
}Cell;

Cell map[hlab][wlab];

void drawgame()
{
   p = 1-p;
   setactivepage(p);
   
   clearviewport();
   for(int i = 0; i < hlab; i++)
   {
      for(int k = 0; k < wlab; k++)
      {
         if(map[i][k].Left) line((1+k)*50, height-(1+i)*50, (1+k)*50, height-(2+i)*50);
         if(map[i][k].Bottom) line((1+k)*50, height-(1+i)*50, (2+k)*50, height-(1+i)*50);
      }
   }
   setfillstyle(1, GREEN);
   bar((1+end[0])*50+1, height-(1+end[1])*50-1, (2+end[0])*50-1, height-(2+end[1])*50+1);
   setfillstyle(1, RED);
   bar(51, height-51, 99, height-99);
   setvisualpage(p);
   delay(100);
}

void shift(int x, int y, int s)
{
   while(1)
   {
      drawgame();
      int em[4] = {0};
      int n = 0;
      for(int i = 0; i < 4; i++)
      {
         if(i%2) if(i/2)
            {
               if(y+1 < hlab-1 && 1-map[y+1][x].flag) 
               {
                  em[n] = i;
                  n++;
               }
            }
            else
            {
               if(y-1 > -1 && 1-map[y-1][x].flag) 
               {
                  em[n] = i;
                  n++;
               }
            }
         else if(i/2)
            {
               if(x+1 < wlab-1 && 1-map[y][x+1].flag) 
               {
                  em[n] = i;
                  n++;
               }
            }
            else
            {
               if(x-1 > -1 && 1-map[y][x-1].flag) 
               {
                  em[n] = i;
                  n++;
               }
            }
      }
      
      if(n == 0)
      {
         if(end[2] < s)
         {
            end[0] = x;
            end[1] = y;
            end[2] = s;
         }
         return;
      }
      
      int r = em[rand()%n];
      if(r%2) if(r/2)
         {
            map[y+1][x].flag = 1;
            map[y+1][x].Bottom = 0;
            shift(x, y+1, s+1);
         }
         else
         {
            map[y-1][x].flag = 1;
            map[y][x].Bottom = 0;
            shift(x, y-1, s+1);
         }
      else if(r/2)
         {
            map[y][x+1].flag = 1;
            map[y][x+1].Left = 0;
            shift(x+1, y, s+1);
         }
         else
         {
            map[y][x-1].flag = 1;
            map[y][x].Left = 0;
            shift(x-1, y, s+1);
         }
   }
}

int main()
{
   initwindow( width, height,"Labirint",10,20);
   srand(time(0));
   
   for(int i = 0; i < hlab; i++)
   {
      for(int k = 0; k < wlab; k++)
      {
         if(i+1 == hlab) map[i][k].Left = 0;
         if(k+1 == wlab) map[i][k].Bottom = 0;
      }
   }
   
   map[0][0].flag = 1;
   shift(0, 0, 1);
   
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      
      clearviewport();
      for(int i = 0; i < hlab; i++)
      {
         for(int k = 0; k < wlab; k++)
         {
            if(map[i][k].Left) line((1+k)*50, height-(1+i)*50, (1+k)*50, height-(2+i)*50);
            if(map[i][k].Bottom) line((1+k)*50, height-(1+i)*50, (2+k)*50, height-(1+i)*50);
         }
      }
      setfillstyle(1, GREEN);
      bar((1+end[0])*50+1, height-(1+end[1])*50-1, (2+end[0])*50-1, height-(2+end[1])*50+1);
      setfillstyle(1, RED);
      bar(51, height-51, 99, height-99);
      setvisualpage(p);
      delay(100);
   }
}