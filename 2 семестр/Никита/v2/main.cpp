#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

typedef struct Button // структура кнопок
{
   int x, y; // координаты центра
   char text[20];
}Button;

int cell = 60; // размер клетки
int live = 0; // количество жизней
int p = 0; // номер обробатываемого окна
int ans[9][9] = {0}; // массив правильной сетки
int pole[9][9] = {0}; // массив поставленных цифр
int all[9] = {0}; // количеств поставленных цифр
int selected = 0; // выбранная кнопка

void generation(int dif) // генератор судоку
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
         for(int j = 0; j < 4+1-dif; j++)
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

int draw_sudoku(int dif) // отрисовка поля судоку
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
   
   setfillstyle(SOLID_FILL, BLACK);// отрисовка жизней
   for(int i = 0; i < live; i++)
   {
      fillellipse(10.5*cell+25*i, 0.5*cell, 10, 10);
   }
   for(int i = live; i < 3; i++)
   {
      circle(10.5*cell+25*i, 0.5*cell, 10);
   }
   
   if(live == 0)// проигрыш
   {
      setlinestyle(SOLID_LINE, 1, 1);
      setfillstyle(SOLID_FILL, WHITE);
      bar(2.7*cell, 4.6*cell, 7.3*cell, 6.4*cell);
      rectangle(2.7*cell, 4.6*cell, 7.3*cell, 6.4*cell);
      outtextxy(5*cell, 5*cell, "Вы проиграли");
      
      if(mousex() > 2.8*cell && mousex() < 5.5*cell && mousey() > 5.5*cell && mousey() < 6.3*cell) 
      {
         if(mousebuttons()) 
         {
            generation(dif);
            while(mousebuttons());
         }
         setlinestyle(SOLID_LINE, 1, 3);
      }
      else setlinestyle(SOLID_LINE, 1, 1);
      rectangle(2.8*cell, 5.5*cell, 5.5*cell, 6.3*cell);
      outtextxy(4.15*cell, 5.9*cell, "Ещё раз");
      
      if(mousex() > 5.6*cell && mousex() < 7.2*cell && mousey() > 5.5*cell && mousey() < 6.3*cell)
      {
         if(mousebuttons()) 
         {
            while(mousebuttons());
            return 0;
         }
         setlinestyle(SOLID_LINE, 1, 3);
      }
      else setlinestyle(SOLID_LINE, 1, 1);
      rectangle(5.6*cell, 5.5*cell, 7.2*cell, 6.3*cell);
      outtextxy(6.4*cell, 5.9*cell, "Меню");
   }
   
   int count = 0;
   for(int i = 0; i < 9; i++)
   {
      if(all[i] != 9) break;
      count++;
   }
   if(count == 9)
   {
      
   }
   
   setvisualpage(p);
   delay(50);
   return 1;
}

void treat() // обработка окна судоку
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

void game(int dif) // игра
{
   while(mousebuttons());
   while(draw_sudoku(dif))
   {
      if(live != 0) treat();
   }
   while(mousebuttons());
}

void menu(char buttons[6][20], int num[2]) // меню
{
   p = 1-p;
   setactivepage(p);
   clearviewport();
   setbkcolor(WHITE);
   setcolor(BLACK);
   setlinestyle(SOLID_LINE, 1, 1);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
   
   outtextxy(350, 150, "Судоку");
   for(int i = 0; i < 3; i++)
   {
      if(num[0] == i+num[1]*3) setlinestyle(SOLID_LINE, 1, 3);
      else setlinestyle(SOLID_LINE, 1, 1);
      rectangle(200, 250+i*100, 500, 300+i*100);
      outtextxy(350, 275+i*100, buttons[i+num[1]*3]);
   }
   
   setvisualpage(p);
   delay(50);
   
   num[0] = -1;
   for(int i = 0; i < 3; i++)
   {
      if(mousex() > 200 && mousey() > 250+i*100 && mousex() < 500 && mousey() < 300+i*100) num[0] = i + num[1]*3;
   }
   if(mousebuttons() == 1 && num[0] != -1)
   {
      switch(num[0])
      {
         case 0:
         {
            num[1] = 1;
            break;
         }
         case 1:
         {
            break;
         }
         case 2:
         {
            break;
         }
         case 3:
         {
            generation(0);
            game(0);
            num[0] = 0;
            num[1] = 0;
            break;
         }
         case 4:
         {
            generation(1);
            game(1);
            num[0] = 0;
            num[1] = 0;
            break;
         }
         case 5:
         {
            num[1] = 0;
            break;
         }
      }
      while(mousebuttons());
   }
}

int main()
{
   initwindow(700, 700, "Судоку",50,50);
   srand(time(0));
   char buttons[6][20] = {"Играть", "Об игре", "Выход", "Легко", "Сложно", "Назад"};
   int num[2] = {-1, 0};
   while(1)
   {
      menu(buttons, num);
   }
}