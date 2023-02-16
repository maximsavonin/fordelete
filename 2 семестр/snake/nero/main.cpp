#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

#define CELL 40

typedef struct Snake{
   int x, y;
}Snake;

int d = 50, num = 0;
Snake all[225];
int n = 0;
int map[17][17] = {0};
int p = 0;
int Q[3][3][3][3][15][15][4] = {0}, ap[2] = {0};

void drawgame()
{
   p = 1-p;
   setactivepage(p);
   clearviewport();
   
   setbkcolor(BLACK);
   setcolor(WHITE);
   for(int i = 0; i < 15; i++)
   {
      for(int k = 0; k < 15; k++)
      {
         rectangle(k*CELL, i*CELL, (k+1)*CELL, (i+1)*CELL);
         switch(map[i+1][k+1])
         {
            case 1:
            {
               setfillstyle(SOLID_FILL, GREEN);
               bar((k+0.1)*CELL, (i+0.1)*CELL, (k+0.9)*CELL, (i+0.9)*CELL);
               break;
            }
            case 2:
            {
               setfillstyle(SOLID_FILL, RED);
               bar((k+0.2)*CELL, (i+0.2)*CELL, (k+0.8)*CELL, (i+0.8)*CELL);
               break;
            }
         }
      }
   }
   
   setvisualpage(p);
   delay(d      );
}

void apple()
{
   while(1)
   {
      int x = rand()%15+1, y = rand()%15+1;
      if(map[y][x] == 0)
      {
         map[y][x] = 2;
         ap[0] = x;
         ap[1] = y;
         break;
      }
   }
}

void start()
{
   for(int i = 1; i < 16; i++)
   {
      for(int k = 1; k < 16; k++)
      {
         map[i][k] = 0;
      }
   }
   
   all[0].x = 3;
   all[0].y = 1;
   all[1].x = 2;
   all[1].y = 1;
   all[2].x = 1;
   all[2].y = 1;
   n = 3;
   
   map[1][1] = 1;
   map[1][2] = 1;
   map[1][3] = 1;
   num++;
   printf("%d\n", num);
   apple();
}

int movesnake(int x, int y)
{
   int a = -1;
   if(map[all[0].y+y][all[0].x+x] == 2)
   {
      n++;
      a = 30;
   }
   else if(map[all[0].y+y][all[0].x+x] == 1 && !(all[0].x+x == all[n-1].x && all[0].y+y == all[n-1].y))
   {
      start();
      a = -50;
      return a;
   }
   else map[all[n-1].y][all[n-1].x] = 0;
   for(int i = n-1; i > 0; i--)
   {
      all[i].x = all[i-1].x;
      all[i].y = all[i-1].y;
   }
   all[0].x += x;
   all[0].y += y;
   if(map[all[0].y][all[0].x] == 2) apple();
   map[all[0].y][all[0].x] = 1;
   return a;
}

void tread()
{
   int a[5] = {-1000000, 0, 0, 0, 0}, kol = 0, x = all[0].x, y = all[0].y;
   for(int i = 0; i < 4; i++)
   {
      if(Q[map[y][x-1]][map[y-1][x]][map[y][x+1]][map[y+1][x]][ap[0]][ap[1]][i] > a[0])
      {
         a[0] = Q[map[y][x-1]][map[y-1][x]][map[y][x+1]][map[y+1][x]][ap[0]][ap[1]][i];
         a[1] = i;
         kol = 1;
      }
      else if(Q[map[y][x-1]][map[y-1][x]][map[y][x+1]][map[y+1][x]][ap[0]][ap[1]][i] == a[0])
      {
         a[kol] = i;
         kol++;
      }
   }
   
   if(kol > 1) a[1] = a[1+rand()%kol];
   
   switch(a[1])
   {
      case 0:
      {
         Q[map[y][x-1]][map[y-1][x]][map[y][x+1]][map[y+1][x]][ap[0]][ap[1]][0] += movesnake(-1, 0);
         break;
      }
      case 2:
      {
         Q[map[y][x-1]][map[y-1][x]][map[y][x+1]][map[y+1][x]][ap[0]][ap[1]][2] += movesnake(1, 0);
         break;
      }
      case 3:
      {
         Q[map[y][x-1]][map[y-1][x]][map[y][x+1]][map[y+1][x]][ap[0]][ap[1]][3] += movesnake(0, 1);
         break;
      }
      case 1:
      {
         Q[map[y][x-1]][map[y-1][x]][map[y][x+1]][map[y+1][x]][ap[0]][ap[1]][1] += movesnake(0, -1);
         break;
      }
   }
}

int main()
{
   initwindow(600, 600, "Snake",50,50);
   srand(time(0));
   for(int i = 0; i < 17; i++)
   {
      for(int k = 0; k < 17; k++)
      {
         map[i][k] = 1;
      }
   }
   start();
   
   while(1)
   {
      if(mousebuttons())
      {
         d = 50-d;
         while(mousebuttons());
      }
      tread();
      drawgame();      
   }
}