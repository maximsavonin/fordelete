#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

int cell = 60;
int live = 0;
int p = 0;
int ans[9][9] = {0};
int pole[9][9] = {0};
int all[9] = {0};
int selected = 0;

void draw_sudoku()
{
   p = 1-p;
   setactivepage(p);
   
   clearviewport();
   setbkcolor(WHITE);
   setcolor(BLACK);
   setlinestyle(SOLID_LINE, 1, 1);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
   for(int i = 0; i < 9; i++)
   {
      for(int k = 0; k < 9; k++)
      {
         if(pole[i][k] != 0)
         {
            if(selected == pole[i][k])
            {
               setfillstyle(SOLID_FILL, COLOR(220, 220, 220));
               bar((0.5+k)*cell, (0.5+i)*cell, (1.5+k)*cell, (1.5+i)*cell);
            }
            char a[2] = {0};
            if(live == 0) a[0]  = '0'+ans[i][k];
            else a[0]  = '0'+pole[i][k];
            outtextxy((1+k)*cell, (1+i)*cell, a);
         }
         rectangle((0.5+k)*cell, (0.5+i)*cell, (1.5+k)*cell, (1.5+i)*cell);
      }
   }
   
   for(int i = 0; i < 9; i++)
   {
      if(i == selected-1) setlinestyle(SOLID_LINE, 1, 3);
      else setlinestyle(SOLID_LINE, 1, 1);
      rectangle((0.5+i)*cell, 10*cell, (1.5+i)*cell, 11*cell);
      if(all[i] != 9)
      {
         char a[2] = {0};
         a[0]  = '0'+i+1;
         outtextxy((1+i)*cell, 10.5*cell, a);
      }
   }
   
   setlinestyle(SOLID_LINE, 1, 3);
   for(int i = 0; i < 4; i++)
   {
      line((0.5+3*i)*cell, 0.5*cell, (0.5+3*i)*cell, 9.5*cell);
   }
   for(int i = 0; i < 4; i++)
   {
      line(0.5*cell, (0.5+3*i)*cell, 9.5*cell, (0.5+3*i)*cell);
   }
   
   if(live == 0)
   {
      rectangle(3*cell, 4*cell, 7*cell, 6*cell);
      bar(3*cell, 4*cell, 7*cell, 6*cell);
   }
   
   setvisualpage(p);
   delay(50);
   if(live == 0) delay(3000);
}

void generation()
{
   live = 3;
   int mas[9];
   for(int i = 0; i < 9; i++)
   {
      all[i] = 0;
      mas[i] = i+1;
   }
   for(int i = 0; i < 20; i++)
   {
      int a = rand()%9, b = rand()%9;
      int c = mas[a];
      mas[a] = mas[b];
      mas[b] = c;
   }
   
   for(int i = 0; i < 3; i++)
   {
      for(int k = 0; k < 3; k++)
      {
         for(int j = 0; j < 9; j++)
         {
            pole[3*i+k][j] = 0;
            ans[3*i+k][j] = mas[(j+3*k+i)%9];
         }
      }
   }
   
   for(int i = 0; i < 3; i++)
   {
      for(int k = 0; k < 3; k++)
      {
         int j = rand()%3;
         if(j == k) continue;
         for(int l = 0; l < 9; l++)
         {
            int a = ans[i*3+k][l];
            ans[i*3+k][l] = ans[i*3+j][l];
            ans[i*3+j][l] = a;
         }
      }
   }
   for(int i = 0; i < 3; i++)
   {
      for(int k = 0; k < 3; k++)
      {
         int j = rand()%3;
         if(j == k) continue;
         for(int l = 0; l < 9; l++)
         {
            int a = ans[l][i*3+k];
            ans[l][i*3+k] = ans[l][i*3+j];
            ans[l][i*3+j] = a;
         }
      }
   }
   
   for(int i = 0; i < 3; i++)
   {
      for(int k = 0; k < 3; k++)
      {
         for(int j = 0; j < 4; j++)
         {
            int a = rand()%3, b = rand()%3;
            pole[a+3*i][b+3*k] = ans[a+3*i][b+3*k];
         }
      }
   }
   for(int i = 0; i < 9; i++)
   {
      for(int k = 0; k < 9; k++)
      {
         if(pole[i][k] != 0) all[pole[i][k]-1] += 1;
      }
   }
}

void treat()
{
   if(mousebuttons())
   {
      int x = (mousex()-0.5*cell)/cell, y = mousey();
      if(x >= 0 && y > 10*cell && x < 9 && y < 11*cell) selected = x+1;
      else 
      {
         y = (y-0.5*cell)/cell;
         if(x >= 0 && x < 9 && y >= 0 && y < 9 && pole[y][x] == 0 && ans[y][x] == selected)
         {
            pole[y][x] = selected;
            all[selected-1] += 1;
         }
         else live--;
      }
      while(mousebuttons());
   }
}

int main()
{
   initwindow(700, 700, "Судоку",50,50);
   srand(time(0));
   generation();
   while(1)
   {
      treat();
      draw_sudoku();
   }
}