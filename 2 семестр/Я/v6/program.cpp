#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

#include "graphics.h"

using namespace std;

#define h 40 //длинна стороны квадрата
#define s_y 100 // начало сетки
#define s_x 100
#define n_y 15 // размер сетки пол€
#define n_x 9

bool ingame = false; //в игре или в меню
int score = 0;  // счЄт
int x_d = 0, y_d = 0; // место нахождение падающей колонны
int p = 0; // номер отоброжаемой страницы
int map[9][15]; //карта
int obj[2][3]; //падающа€ и следующа колонна

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

void draw(int x, int y, int col) // отрисовка квадрата определЄнного цвета
{
   int color[7] = {BLACK, GREEN, RED, BLUE, YELLOW, COLOR(255, 140, 0), COLOR(164, 94, 229)};
   setfillstyle(1,color[col]);
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
   int 
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

int vec(int x, int y, int vx, int vy, int delmap[9][15])
{
   int n = 0;
   for(int k = 0, i = 0; y+k < n_y && y+k > -1 && x+i < n_x && x+i > -1; k += vy, i += vx)
   {
      if(map[x][y] != map[x+i][y+k]) break;
      n++;
   }
   if(n > 2)
   {
      for(int i = 0, k = 0; i*vx < n && k*vy < n; i+=vx, k += vy)
      {
         delmap[x+i][y+k] = 1;
      }
   }
   return n;
}

void checking(int &kol) // проверка 3 в р€д и отрисовка падени€ клеток
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
      int delmap[9][15] = {0};
      for(int i = 0; i < n_x; i++)
      {
         for(int k = 0; k < n_y; k++)
         {
            if(map[i][k] != 0)
            {
               for(int nap = 0; nap < 4; nap++)
               {
                  max_n = vec(i, k, (3-nap)/2-nap/3, (nap+2)/3, delmap); // вправо
                  if(max_n > 2)
                  {
                     kol = fmax(kol, max_n);
                     again = 1;
                  }
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
   outtextxy(310, 310, "Ќова€ игра");
   outtextxy(335, 420, "ќб игре");
   outtextxy(360, 530, "¬ыход");   
}

void aboute_game() // отрисовка об игре
{
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(290, 150, "Columns");
   outtextxy(290, 200, "ќб игре");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(90, 260, "сверху вниз падает столбец в котором");
   outtextxy(100, 280, "цвета мен€ютс€ циклично по пробелу");
   outtextxy(95, 300, "его можно сдвигать во врем€ падени€");
   outtextxy(105, 320, "с помощью стрелочек на клавиатуре");
   outtextxy(105, 340, "если собираетс€ 3 одинаковых цвета");
   outtextxy(100, 360, "в р€д, в столбец или по диагонали, то");
   outtextxy(270, 380, "они удал€ютс€");
   rectangle(275, 560, 525, 630);
   rectangle(270, 555, 530, 635);
   outtextxy(360, 590, "Ќазад");   
   int Key = getch();
   while(Key != KEY_ENTER)
   {
      Key = getch();
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

void new_column()// по€влеие следующей колонны
{
   for(int i = 0; i < n_x; i++)
   {
      if(map[i][2] != 0)
      {
         ingame = false;
         settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
         outtextxy(300, 320, " онец игры");   
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

void clik(int &del, int &kol) // обработка нажати€ клавиш
{
   int Key = getch();
   if(Key == 0) Key = getch();
   switch(Key)
   {
      case KEY_ESC:
      {
         ingame = false;
         break;
      }
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
      case 32: // клавиша пробел
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
   initwindow( 800, 700,"Columns",200,20);
   
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
         if(del-score/100 > 0) delay(del-score/100);
      }
      else
      {
         menu(numbut);
      }
   }
   closegraph();
}