#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <math.h>

#include "graphics.h"

int map[10][7] = {0};
int cx, cy;

bool down()
{
   bool fal = false;
   for(int i = 8; i >= 0; i--)
   {
      for(int k = 0; k < 7; k++)
      {
         if(map[i][k] != 0 && map[i+1][k] == 0)
         {
            if(i == cy && k == cx) cy++;
            map[i+1][k] = map[i][k];
            map[i][k] = 0;
            fal = true;
         }
      }
   }
   return fal;
}

bool chek()
{
   bool del = false;
   int delmap[10][7] = {0};
   for(int y = 9; y >= 0; y--)
   {
      for(int x = 0; x < 7; x++)
      {
         if(map[y][x] != 0)
         {
            int n = map[y][x];
            for(int i = 1; x+i < 7; i++)
            {
               n += map[y][x+i];
               if(map[y][x+i] == 0 || n > 9) break;
            }
            if(n % 10 == 0)
            {
               del = true;
               for(int i = 0, n = 0; n != 10; n+= map[y][x+i], i++)
               {
                  delmap[y][x+i] = 1;
               }
            }
            
            n = map[y][x];
            for(int i = 1; y+i < 10; i++)
            {
               n += map[y+i][x];
               if(map[y+i][x] == 0 || n > 9) break;
            }
            if(n % 10 == 0)
            {
               del = true;
               for(int i = 0, n = 0; n != 10; n+= map[y+i][x], i++)
               {
                  delmap[y+i][x] = 1;
               }
            }
         }
      }
   }
   for(int y = 0; y < 10; y++)
   {
      for(int x = 0; x < 7; x++)
      {
         map[y][x] *= (1-delmap[y][x]);
      }
   }
   return del;
}

void draw()
{
   int acell = 50;
   for(int y = 0; y < 10; y++)
   {
      for(int x = 0; x < 7; x++)
      {
         //color[9] = {COLOR(255, 0, 0), }
         setfillstyle(SOLID_FILL, map[y][x]);
         bar((x+1)*acell, (y+1)*acell, (x+2)*acell, (y+2)*acell);
         rectangle((x+1)*acell, (y+1)*acell, (x+2)*acell, (y+2)*acell);
         if(map[y][x] != 0)
         {
            char text[2] = {0};
            sprintf(text,"%d",map[y][x]);
            outtextxy((x+1)*acell+20, (y+1)*acell+20, text);
         }
      }
   }
}

bool clik()
{
   bool cl = false;
   if(kbhit())
   {
      cl = true;
      int key = getch();
      switch(key)
      {
         case 75:
         {
            if(cx > 0 && map[cy][cx-1] == 0)
            {
               map[cy][cx-1] = map[cy][cx];
               map[cy][cx] = 0;
               cx -= 1;
            }
            break;
         }
         case 77:
         {
            if(cx < 9 && map[cy][cx+1] == 0)
            {
               map[cy][cx+1] = map[cy][cx];
               map[cy][cx] = 0;
               cx += 1;
            }
            break;
         }
      }
   }
   return cl;
}

int main()
{
   initwindow(1000, 800, "Math tetris", 100, 10);
   srand(time(0));
   int p = 0;
   cy = 0;
   cx = rand()%7;
   map[cy][cx] = rand()%9+1;
   
   while(1)
   {
      p = 1-p;
      if(!clik() && !down() && !chek())
      {
         for(int i = 0; i < 7; i++)
         {
            if(map[0][i] != 0) return 0;
         }
         cy = 0;
         cx = rand()%7;
         map[cy][cx] = rand()%9+1;
      }
      setactivepage(p);
      clearviewport();
      draw();
      setvisualpage(p);
      delay(200);
   }
}