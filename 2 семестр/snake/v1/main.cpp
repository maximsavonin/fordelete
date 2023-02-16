#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

#define CELL 40

typedef struct Snake{
   int x, y;
}Snake;

Snake all[225];
int n = 0;
int map[15][15] = {0};
int p = 0;

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
         switch(map[i][k])
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
}

void apple()
{
   while(1)
   {
      int x = rand()%15, y = rand()%15;
      if(map[y][x] == 0)
      {
         map[y][x] = 2;
         break;
      }
   }
}

void start()
{
   for(int i = 0; i < 15; i++)
   {
      for(int k = 0; k < 15; k++)
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
   
   apple();
}

void movesnake(int x, int y)
{
   if(map[all[0].y+y][all[0].x+x] == 2)
   {
      n++;
   }
   else if(map[all[0].y+y][all[0].x+x] == 1 && !(all[0].x+x == all[n-1].x && all[0].y+y == all[n-1].y))
   {
      start();
      return;
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
}

void tread()
{
   if(1 == kbhit())
   {
      int Key = getch();
      if(Key == 0) Key = getch();
      switch(Key)
      {
         case KEY_LEFT:
         {
            movesnake(-1, 0);
            break;
         }
         case KEY_RIGHT:
         {
            movesnake(1, 0);
            break;
         }
         case KEY_DOWN:
         {
            movesnake(0, 1);
            break;
         }
         case KEY_UP:
         {
            movesnake(0, -1);
            break;
         }
      }
   }
}

int main()
{
   initwindow(600, 600, "Snake",50,50);
   srand(time(0));
   start();
   
   while(1)
   {
      tread();
      drawgame();      
   }
}