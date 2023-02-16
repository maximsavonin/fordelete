#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <math.h>

#include "graphics.h"
int hlab = 31, wlab = 31; // размеры лабиринта
int acell = 25; // размер клеточки
int width = 800, height = 800; //размер экрана
int end[3] = {0}; // координаты конца и расстояние до него
int start[2] = {0}; // координаты начала
int p = 0; // отрисовываемая страница
int player[2]; // координаты игрока
int play = 0, exitt = 0; // в игре? и выйти?

typedef struct Button{ // Кнопка
   int x, y; // координаты 
   int w, h; // размеры 
   char text[50]; // текст
} Button;

typedef struct Cell // ячейка лабиринта
{
   int Left = 1, Bottom = 1; // левая и нижняя стена есть?
   int flag = 0; // были в ячейка?
}Cell;

Cell map[60][60]; // карта лабиринта

void drawgame(long int t, int timer) // отрисовка игры
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
   setfillstyle(1, GREEN);
   bar((1+end[0])*acell+1, height-(1+end[1])*acell-1, (2+end[0])*acell-1, height-(2+end[1])*acell+1);
   setfillstyle(1, RED);
   bar((1+start[0])*acell+1, height-(1+start[1])*acell-1, (2+start[0])*acell-1, height-(2+start[1])*acell+1);
   setfillstyle(1, MAGENTA);
   bar((1+player[0])*acell+3*acell/10, height-(1+player[1])*acell-3*acell/10, (2+player[0])*acell-3*acell/10, height-(2+player[1])*acell+3*acell/10);
   char text[3];
   sprintf(text, "%d", timer-(time(NULL)-t));
   outtextxy(width/2, 30, text);
   setvisualpage(p);
   delay(30);
}

void shift(int x, int y, int s) // генерация лабиринта
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
            //printf("%d\n", s);
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

void generatlab() // создание лабиринта
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

void control(long int &t) // управление игрой
{
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
         case KEY_ESC:
         {
            while(1)
            {
               setlinestyle(SOLID_LINE, 1, 3);
               rectangle(width/2-150, height/2-70, width/2+150, height/2+70);
               setfillstyle(SOLID_FILL, BLACK);
               bar(width/2-149, height/2-69, width/2+149, height/2+69);
               outtextxy(width/2, height/2-30, "Выйти в меню?");
               if(abs(mousex()-width/2+75) < 55 && abs(mousey()-height/2-27) < 27)
               {
                  setlinestyle(SOLID_LINE, 1, 3);
                  if(mousebuttons()) 
                  {
                     play = 0;
                     break;
                  }
               }
               else setlinestyle(SOLID_LINE, 1, 1);
               rectangle(width/2-130, height/2, width/2-20, height/2+55);
               outtextxy(width/2-75, height/2+40, "Да");
               if(abs(mousex()-width/2-75) < 55 && abs(mousey()-height/2-27) < 27)
               {
                  setlinestyle(SOLID_LINE, 1, 3);
                  if(mousebuttons()) break;
               }
               else setlinestyle(SOLID_LINE, 1, 1);
               rectangle(width/2+20, height/2, width/2+130, height/2+55);
               outtextxy(width/2+75, height/2+40, "Нет");
               delay(50);
            }
            while(mousebuttons());
            break;
         }
      }
   }
   if(player[0] == end[0] && player[1] == end[1])
   {
      start[0] = end[0];
      start[1] = end[1];
      t = time(NULL);
      generatlab();
   }
}

void drawmenu(Button buttons[7], int dif, int but) // отрисовка меню
{
   p = 1-p;
   setactivepage(p);
   clearviewport();
   setusercharsize(10, 9, 2, 1);
   outtextxy(400, 150, "Лабиринт");
   setusercharsize(2, 3, 6, 5);
   for(int i = dif*3; i < (dif+1)*3+dif; i++)
   {
      if(i == but) setlinestyle(SOLID_LINE, 1, 5);
      else setlinestyle(SOLID_LINE, 1, 1);
      rectangle(buttons[i].x-buttons[i].w, buttons[i].y-buttons[i].h, buttons[i].x+buttons[i].w, buttons[i].y+buttons[i].h);
      outtextxy(buttons[i].x, buttons[i].y+10, buttons[i].text);
   }
   setvisualpage(p);
   delay(30);
}

void controlmenu(Button buttons[7], int &dif, int &but, int &timer) // управление меню
{
   but = -1;
   for(int i = dif*3; i < (dif+1)*3+dif; i++)
   {
      if(abs(mousex()-buttons[i].x) < buttons[i].w && abs(mousey()-buttons[i].y) < buttons[i].h) but = i;
   }
   if(mousebuttons())
   {
      switch(but)
      {
         case 0:
         {
            dif = 1;
            break;
         }
         case 1:
         {
            while(1)
            {
               p = 1-p;
               setactivepage(p);
               clearviewport();
               setlinestyle(SOLID_LINE, 1, 1);
               rectangle(100, 150, 700, 650);
               setfillstyle(SOLID_FILL, BLACK);
               bar(101, 151, 699, 649);
               outtextxy(400, 190, "Цель данной игры найти выход из");
               outtextxy(400, 225, "лабиринта за отведённый срок времени.");
               outtextxy(400, 260, "Чтобы начать нужно нажать на кнопку");
               outtextxy(400, 295, "“новая игра” и выбрать удобный для вас");
               outtextxy(400, 330, "уровень сложности. Управление");
               outtextxy(400, 365, "персонажем происходит с помощью");
               outtextxy(400, 400, "стрелок на клавиатуре.");
               if(abs(mousex()-buttons[6].x) < buttons[6].w && abs(mousey()-buttons[6].y) < buttons[6].h) 
               {
                  setlinestyle(SOLID_LINE, 1, 5);
                  if(mousebuttons()) break;
               }
               rectangle(buttons[6].x-buttons[6].w, buttons[6].y-buttons[6].h, buttons[6].x+buttons[6].w, buttons[6].y+buttons[6].h);
               outtextxy(buttons[6].x, buttons[6].y+10, buttons[6].text);
               setvisualpage(p);
               delay(50);
            }
            while(mousebuttons());
            break;
         }
         case 2:
         {
            exitt = 1;
            break;
         }
         case 3:
         {
            play = 1;
            wlab = 12;
            hlab = 12;
            acell = 60;
            start[0] = 0;
            start[1] = 0;
            timer = 30;
            generatlab();
            dif = 0;
            break;
         }
         case 4:
         {
            play = 1;
            wlab = 19;
            hlab = 19;
            acell = 40;
            start[0] = 0;
            start[1] = 0;
            timer = 50;
            generatlab();
            dif = 0;
            break;
         }
         case 5:
         {
            play = 1;
            wlab = 31;
            hlab = 30;
            acell = 25;
            start[0] = 0;
            start[1] = 0;
            timer = 100;
            generatlab();
            dif = 0;
            break;
         }
         case 6:
         {
            dif = 0;
            break;
         }
      }
      while(mousebuttons());
   }
}

int main()
{
   initwindow( width, height,"Labirint",10,20);
   srand(time(0));
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(2, 3, 6, 5);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   
   // кнопки меню
   Button buttons[7] = {{width/2, 350, 120, 30, "Играть"}, {width/2, 450, 120, 30, "Об игре"}, {width/2, 550, 120, 30, "Выход"}, {width/2, 300, 120, 30, "Легкая"}, {width/2, 400, 120, 30, "Средняя"}, {width/2, 500, 120, 30, "Сложная"}, {width/2, 600, 120, 30, "Назад"}};
   int dif = 0, but = 0; // выбираем сложность? и на какую кнопку навели
   int timer = 0; // время для прохождение
   long int t = time(NULL); // время начала прохождения
   
   while(1-exitt)
   {
      if(play)
      {
         if(time(NULL)-t >= timer)
         {
            setlinestyle(SOLID_LINE, 1, 3);
            rectangle(width/2-120, height/2-35, width/2+120, height/2+35);
            setfillstyle(SOLID_FILL, BLACK);
            bar(width/2-119, height/2-34, width/2+119, height/2+34);
            outtextxy(width/2, height/2+10, "Время вышло");
            setlinestyle(SOLID_LINE, 1, 1);
            delay(2000);
            play = 0;
         }
         control(t);
         drawgame(t, timer);
      }
      else
      {
         t = time(NULL);
         controlmenu(buttons, dif, but, timer);
         drawmenu(buttons, dif, but);
      }
   }
}