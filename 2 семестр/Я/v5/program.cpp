#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

#include "graphics.h"

using namespace std;

bool ingame = false; //в игре или в меню
int h = 40, score = 0;  // длинна стороны квадрата и счёт
int s_y = 100, s_x = 100; // начало сетки
int x_d = 0, y_d = 0; // место нахождение падающей колонны
int n_y = 15, n_x = 9; // размер сетки поля
int p = 0; // номер отоброжаемой страницы
int map[9][15]; //карта
int obj[2][3]; //падающая и следующа колонна

void new_game() //обнуление игры
{
   score = 0;
   for(int i = 0; i < 2; i++)
   {
      for(int k = 0; k < 3; k++)
      {
         obj[i][k] = rand()%6+1;
      }
   }
    
   for(int i = 0; i < n_x; i++)
   {
      for(int k = 0; k < n_y; k++)
      {
         map[i][k] = 0;
      }
   }
   
   map[5][0] = obj[0][0];
   map[5][1] = obj[0][1];
   map[5][2] = obj[0][2];
   y_d = 2;
   x_d = 5;
}

void draw(int x, int y, int col) // отрисовка квадрата определённого цвета
{
   switch(col)
   {
      case 0:
      {
         setfillstyle(1,BLACK);
         break;
      }
      case 1:
      {
         setfillstyle(1,GREEN);
         break;
      }
      case 2:
      {
         setfillstyle(1,RED);
         break;
      }
      case 3:
      {
         setfillstyle(1,BLUE);
         break;
      }
      case 4:
      {
         setfillstyle(1,YELLOW);
         break;
      }
      case 5:
      {
         setfillstyle(1, COLOR(255, 140, 0));
         break;
      }
      case 6:
      {
         setfillstyle(1, COLOR(164, 94, 229));
         break;
      }
      default:
      {
         setfillstyle(1, BLACK);
         break;
      }
   }
   bar(x+1,y+1,x+h-1,y+h-1);
   setcolor(WHITE);
   rectangle(x, y, x+h, y+h);
}

void draw_game() // отрисовка игры
{
   clearviewport();
   setcolor(WHITE);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   char text[10];
   sprintf(text, "%d", score);
   outtextxy(s_x+h*n_x+h+50, s_y+(n_y-3)*h-100, text);
   for(int i = 0; i < n_x; i++)
   {
      for(int k = 0; k < n_y-3; k++)
      {
         draw(s_x+i*h, s_y+k*h, map[i][k+3]);
      }
   }
   for(int i = 0; i < 3; i++)
   {
      draw(s_x+(n_x+2)*h, s_y+(i+1)*h, obj[1][i]);
   }
}

int down() // падение квадратиков
{
   int falling = 0;
   for(int i = n_x-1; i > -1; i--)
   {
      for(int k = n_y-1; k > -1; k--)
      {
         if(k+1 < n_y && map[i][k+1] == 0 && map[i][k] != 0)
         {
            if(i == x_d and k == y_d)
            {
               y_d += 1;
            }
            map[i][k+1] = map[i][k];
            map[i][k] = 0;
            falling += 1;
         }
      }
   }
   return falling; 
}

void move_line(int turn) // смещение колонны в сторону
{
   if(x_d+turn > -1 && x_d+turn < n_x && map[x_d+turn][y_d] == 0 && map[x_d+turn][y_d-1] == 0 && map[x_d+turn][y_d-2] == 0)
   {
      map[x_d+turn][y_d] = map[x_d][y_d];
      map[x_d+turn][y_d-1] = map[x_d][y_d-1];
      map[x_d+turn][y_d-2] = map[x_d][y_d-2];
      map[x_d][y_d] = 0;
      map[x_d][y_d-1] = 0;
      map[x_d][y_d-2] = 0;
      x_d += turn;
   }
}

void checking(int &kol) // проверка 3 в ряд и отрисовка падения клеток
{
   int again = 1, max_n = 0;
   while(again == 1)
   {
      for(int i = 0; i < kol; i++)
      {
         p = 1-p;
         setactivepage(p);
         down();
         draw_game();
         setvisualpage(p);
         delay(100);
      }
      
      again = 0;
      int delmap[11][16] = {0};
      for(int i = 0; i < n_x; i++)
      {
         for(int k = 0; k < n_y; k++)
         {
            max_n = 1;
            if(map[i][k] != 0)
            {
               for(int l = 1; i+l<n_x; l++) // вправо
               {
                  if(map[i][k] != map[i+l][k]) break;
                  max_n++;
               }
               if(max_n > 2)
               {
                  kol = fmax(kol, max_n);
                  for(int l = 0; l < max_n; l++)
                  {
                     delmap[i+l][k] = 1;
                  }
                  again = 1;
               }
               max_n = 1;
               
               for(int l = 1; i+l<n_x && k+l < n_y; l++) // по диагонали вверх в право
               {
                  if(map[i][k] != map[i+l][k+l]) break;
                  max_n++;
               }
               if(max_n > 2)
               {
                  kol = fmax(kol, max_n);
                  for(int l = 0; l < max_n; l++)
                  {
                     delmap[i+l][k+l] = 1;
                  }
                  again = 1;
               }
               max_n = 1;
               
               for(int l = 1; k+l<n_y; l++) // вверх
               {
                  if(map[i][k] != map[i][k+l]) break;
                  max_n++;
               }
               if(max_n > 2)
               {
                  kol = fmax(kol, max_n);
                  for(int l = 0; l < max_n; l++)
                  {
                     delmap[i][k+l] = 1;
                  }
                  again = 1; 
               }
               max_n = 1;
               
               for(int l = 1; i-l >= 0 && k+l < n_y; l++) // по диагонали вверх влево
               {
                  if(map[i][k] != map[i-l][k+l]) break;
                  max_n++;
               }
               if(max_n > 2)
               {
                  kol = fmax(kol, max_n);
                  for(int l = 0; l < max_n; l++)
                  {
                     delmap[i-l][k+l] = 1;
                  }
                  again = 1;
               }
            }
         }
      }
      
      for(int i = 0; i < n_x; i++)
      {
         for(int k = 0; k < n_y; k++)
         {
            if(delmap[i][k] == 1) 
            {
               map[i][k] = 0;
               score += 50;
            }
         }
      }
   }
}

void draw_menu(int &numbut) // отрисовка меню
{
   clearviewport();
   
   rectangle(275, 280, 525, 350);
   rectangle(275, 390, 525, 460);
   rectangle(275, 500, 525, 570);
   rectangle(270, 275+numbut*110, 530, 355+numbut*110);
   
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(290, 150, "Columns");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(310, 310, "Новая игра");
   outtextxy(335, 420, "Об игре");
   outtextxy(360, 530, "Выход");   
}

void aboute_game() // отрисовка об игре
{
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(290, 150, "Columns");
   outtextxy(290, 200, "Об игре");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(90, 260, "сверху вниз падает столбец в котором");
   outtextxy(100, 280, "цвета меняются циклично по пробелу");
   outtextxy(95, 300, "его можно сдвигать во время падения");
   outtextxy(105, 320, "с помощью стрелочек на клавиатуре");
   outtextxy(105, 340, "если собирается 3 одинаковых цвета");
   outtextxy(100, 360, "в ряд, в столбец или по диагонали, то");
   outtextxy(270, 380, "они удаляются");
   rectangle(275, 560, 525, 630);
   rectangle(270, 555, 530, 635);
   outtextxy(360, 590, "Назад");   
   int Key = getch();
   if(Key == 0) Key = getch();
   while(Key != KEY_ENTER)
   {
      int Key = getch();
      if(Key == 0) Key = getch();
   }
}

void menu_manager(int &numbut) // обработка меню
{
   int Key = getch();
   if(Key == 0) Key = getch();
   switch(Key)
   {
      case KEY_DOWN:
      {
         numbut += 1;
         break;
      }
      case KEY_UP:
      {
         numbut -= 1;
         break;
      }
      case KEY_ENTER:
      {
         switch(numbut)
         {
            case 0:
            {
               ingame = true;
               new_game();
               break;
            }
            case 1:
            {
               aboute_game();
               break;
            }
            case 2:
            {
               exit(0);
            }
         }
         break;
      }
   }
   numbut = (numbut + 3) % 3;
}

void menu(int &numbut) // меню
{
   draw_menu(numbut);
   menu_manager(numbut);
}

void new_column()// появлеие следующей колонны
{
   for(int i = 0; i < n_x; i++)
   {
      if(map[i][2] != 0)
      {
         ingame = false;
         settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
         outtextxy(300, 320, "Конец игры");   
         setvisualpage(p);
         delay(1500);
         return;
      }
   }
   obj[0][0]    = obj[1][0];
   obj[0][1] = obj[1][1];
   obj[0][2] = obj[1][2];
   map[5][0] = obj[0][0];
   map[5][1] = obj[0][1];
   map[5][2] = obj[0][2];
   obj[1][0] = rand()%6+1;
   obj[1][1] = rand()%6+1;
   obj[1][2] = rand()%6+1;
   y_d = 2;
   x_d = 5;
}

void clik(int &del, int &kol) // обработка нажатия клавиш
{
   int Key = getch();
   if(Key == 0) Key = getch();
   switch(Key)
   {
      case KEY_LEFT:
      {
         move_line(-1);
         del = 300;
         kol++;
         break;
      }
      case KEY_RIGHT:
      {
         move_line(1);
         del=300;
         kol++;
         break;
      }
      case KEY_DOWN:
      {
         del = 50;
         break;
      }
      case 32:
      {
         map[x_d][y_d] = obj[0][1];
         map[x_d][y_d-1] = obj[0][0];
         map[x_d][y_d-2] = obj[0][2];
         obj[0][0] = map[x_d][y_d-2];
         obj[0][1] = map[x_d][y_d-1];
         obj[0][2] = map[x_d][y_d];
         del = 150;
         kol++;
         break;
      }
   }
}

int main()
{
   int del = 200, falling = 0; //задержка между кадрами и падают ли что-либо в предыдущем кадре
   int numbut = 0; // номер кнопки в меню
   srand(time(0));
   initwindow( 800, 700,"Columns",10,20);
   
   while(1)
   {
      if(ingame)
      {
         p = 1-p;
         setactivepage(p);
         del = 200;
         int kol = 0;
         
         if(1 == kbhit())
         {
            clik(del, kol);
         }
         
         if(kol == 0 && down() == 0)
         {
            checking(kol);
            new_column();
         }
         
         draw_game();
         setvisualpage(p);
         delay(del);
      }
      else
      {
         menu(numbut);
      }
   }
   closegraph();
}