#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graphics.h"
int hlab = 31, wlab = 31;
int acell = 25;
int width = 800, height = 800; //размер экрана
int end[3] = {0};
int start[2] = {0};
int p = 0;
int player[2];

typedef struct Cell
{
   int Left = 1, Bottom = 1;
   int flag = 0;
}Cell;

Cell map[50][50];

void drawgame()
{
   p = 1-p;
   setactivepage(p);
   
   clearviewport();
   for(int i = 0; i < hlab; i++)
   {
      for(int k = 0; k < wlab; k++)
      {
         if(map[i][k].Left) line((1+k)*acell, height-(1+i)*acell, (1+k)*acell, height-(2+i)*acell);
         if(map[i][k].Bottom) line((1+k)*acell, height-(1+i)*acell, (2+k)*acell, height-(1+i)*acell);
      }
   }
   setvisualpage(p);
   delay(100);
}

void shift(int x, int y, int s)
{
   while(1)
   {
      
      int em[4] = {0};
      int n = 0;
      for(int i = 0; i < 4; i++)
      {
         if(i%2) if(i/2)
            {
               if(y+1 < hlab-1 && (1-map[y+1][x].flag || rand() % 300 == 0)) 
               {
                  em[n] = i;
                  n++;
               }
            }
            else
            {
               if(y-1 > -1 && (1-map[y-1][x].flag || rand() % 300 == 0)) 
               {
                  em[n] = i;
                  n++;
               }
            }
         else if(i/2)
            {
               if(x+1 < wlab-1 && (1-map[y][x+1].flag || rand() % 300 == 0)) 
               {
                  em[n] = i;
                  n++;
               }
            }
            else
            {
               if(x-1 > -1 && (1-map[y][x-1].flag || rand() % 300 == 0)) 
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

void generatlab()
{
   for(int i = 0; i < hlab; i++)
   {
      for(int k = 0; k < wlab; k++)
      {
         map[i][k].flag = 0;
         if(i+1 == hlab) map[i][k].Left = 0;
         else map[i][k].Left = 1;
         if(k+1 == wlab) map[i][k].Bottom = 0;
         else map[i][k].Bottom = 1;
      }
   }
   
   map[start[1]][start[0]].flag = 1;
   shift(start[0], start[1], 1);
   player[0] = start[0];
   player[1] = start[1];
   end[2] = 0;
}

int main()
{
   initwindow( width, height,"Labirint",10,20);
   srand(time(0));
   
   start[0] = 0;
   start[1] = 0;
   generatlab();
   
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      
      if(1 == kbhit())
      {
         int Key = getch();
         if(Key == 0) Key = getch();
         switch(Key)
         {
            case KEY_LEFT:
            {
               if(map[player[1]][player[0]].Left == 0) player[0] -= 1;
               break;
            }
            case KEY_RIGHT:
            {
               if(map[player[1]][player[0]+1].Left == 0) player[0] += 1;
               break;
            }
            case KEY_DOWN:
            {
               if(map[player[1]][player[0]].Bottom == 0) player[1] -= 1;
               break;
            }
            case KEY_UP:
            {
               if(map[player[1]+1][player[0]].Bottom == 0) player[1] += 1;
               break;
            }
         }
      }
      if(player[0] == end[0] && player[1] == end[1])
      {
         start[0] = end[0];
         start[1] = end[1];
         generatlab();
      }
      
      clearviewport();
      for(int i = 0; i < hlab; i++)
      {
         for(int k = 0; k < wlab; k++)
         {
            if(map[i][k].Left) line((1+k)*acell, height-(1+i)*acell, (1+k)*acell, height-(2+i)*acell);
            if(map[i][k].Bottom) line((1+k)*acell, height-(1+i)*acell, (2+k)*acell, height-(1+i)*acell);
         }
      }
      setfillstyle(1, GREEN);
      bar((1+end[0])*acell+1, height-(1+end[1])*acell-1, (2+end[0])*acell-1, height-(2+end[1])*acell+1);
      setfillstyle(1, RED);
      bar((1+start[0])*acell+1, height-(1+start[1])*acell-1, (2+start[0])*acell-1, height-(2+start[1])*acell+1);
      setfillstyle(1, MAGENTA);
      bar((1+player[0])*acell+3*acell/10, height-(1+player[1])*acell-3*acell/10, (2+player[0])*acell-3*acell/10, height-(2+player[1])*acell+3*acell/10);
      setvisualpage(p);
      delay(100);
   }
}