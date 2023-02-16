#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graphics.h"

double pi = acos(-1); // число pi
int width = 1300, height = 800; //размер экрана
int radius = 25, speed = 2; // радиус шара и его скорость
int score = 0, page = 0;// счёт и номер страниы с которой работаем
int ingame = 0, n = 0; // в игре и количество шаров на экране
int exi = 0; // закрытие программы
IMAGE *picm, *picg;

typedef struct Ball
{
   double x = 0;// Координаты шара по x
   double y = 0;// Координаты шара по y
   double fi = 0; // угол отклонен шара от оси Ox
   int color = 0; // цвет шара
}Ball;

Ball Balls[150]; // Массив шаров
Ball zu_ball; // шар которым стреляем
int fly = 0; // выстрелили шар

void go_ball(int a, int b) //движиение по троектории одного шара
{
   while(1)
   {
      double x, y, xv, yv;
      x = 25*Balls[a].fi*(-cos(Balls[a].fi))+width/2;
      y = 18*Balls[a].fi*(-sin(Balls[a].fi))+height/2;
      xv = abs(x-Balls[b].x);
      yv = abs(y-Balls[b].y);
      if(sqrt(xv*xv+yv*yv) < 2*radius)
      {
         Balls[a].fi -= 0.0002;
      }
      else break;
   }
}

void zuballC() //шар в лягушке
{
   if(!(zu_ball.x == width/2 && zu_ball.y == height/2))
   {
      zu_ball.x = width/2;
      zu_ball.y = height/2;
      zu_ball.color = Balls[rand()%n].color;
      fly = 0;
   }
}

void set_ball(int a, double fi) // функция задания координат шара по углу
{
   Balls[a].fi = fi;
   Balls[a].x = 25*Balls[a].fi*(-cos(Balls[a].fi))+width/2;
   Balls[a].y = 18*Balls[a].fi*(-sin(Balls[a].fi))+height/2;
}

void create_ball(int a) // создаёт новый шар в начале пути
{
   Balls[a].color = rand() % 6 + 1;
   set_ball(a, 6.5*pi);
}

void new_game() // задание переменных для новой игры
{
   n = 1;
   score = 0;
   create_ball(0);
   zuballC();
}

void print_menu(int button) // отрисовка главного меню
{
   clearviewport();
   putimage(0, 0, picm, COPY_PUT);
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(10, 4, 4, 1);
   outtextxy(800, 20, "ZUMA");
   
   setusercharsize(1, 1, 4, 3);
   setfillstyle(SOLID_FILL, COLOR(255, 255, 150));
   for(int i = 0; i < 3; i++)
   {
      rectangle(500, 290+150*i, 800, 390+150*i);
      rectangle(501, 291+150*i, 799, 389+150*i);
      bar(502, 292+150*i, 798, 388+150*i);
   }
   outtextxy(570, 320, "Играть");
   outtextxy(560, 470, "Об игре");
   outtextxy(570, 620, "Выход");
   
   if(button != -1)
   {
      rectangle(490, 280+button*150, 810, 400+button*150);
      rectangle(491, 281+button*150, 809, 399+button*150);
   }
}

int manage_menu(int button) // обработка главного меню managemenu
{
   int x = mousex(), y = mousey();
   if(x > 500 && x < 800 && y > 300 && y < 400) button = 0;
   else
   {
      if(x > 500 && x < 800 && y > 450 && y < 550) button = 1;
      else
      {
         if(x > 500 && x < 800 && y > 600 && y < 700) button = 2;
         else button = -1;
      }
   }

   if(mousebuttons() == 1)
   {
      switch(button)
      {
         case 0:
         {
            ingame = 1;
            break;
         }
         case 1:
         {
            setfillstyle(SOLID_FILL, COLOR(255, 255, 150));
            rectangle(280, 200, 1020, 600);
            bar(281, 201, 1019, 599);
            rectangle(970, 200, 1020, 250);
            setfillstyle(SOLID_FILL, COLOR(240, 0, 0));
            bar(971, 201, 1019, 249);
            setfillstyle(SOLID_FILL, COLOR(255, 255, 150));
            line(980, 210, 1010, 240);
            line(980, 240, 1010, 210);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
            setusercharsize(3, 4, 1, 1);
            outtextxy(300, 300, "ZUMA – казуальная игра, в которой"); //сделать текстовый файл
            outtextxy(300, 330, "цель игры уничтожить лягушкой все");
            outtextxy(300, 360, "разноцветные шарики, двигающиеся");
            outtextxy(300, 390, "цепочкой по экрану.");
            outtextxy(300, 420, "Лягушка наводится на курсор мыши");
            outtextxy(300, 450, "и по нажатию левой кнопки мыши");
            outtextxy(300, 480, "выстреливает.");
            setvisualpage(page);
            while(!(mousex() > 970 && mousex() < 1020 && mousey() > 200 && mousey() < 250 && mousebuttons() == 1));
            break;
         }
         case 2:
         {
            exi = 1;
            break;
         }
      }
   }
   while(mousebuttons() == 1);
   return button;
}

void color_ball(int a) // установление цвета шара
{
   int colors[6] = {COLOR(255, 0, 0), COLOR(0, 255, 0), COLOR(0, 0, 255), COLOR(255, 128, 64), COLOR(128, 0, 255), COLOR(0, 255, 255)};
   setfillstyle(SOLID_FILL, colors[a-1]);
}

void stop() // пауза в игре
{
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(2, 1, 1, 1);
   rectangle(1210, 40, 1260, 90);
   setfillstyle(SOLID_FILL, COLOR(255, 255, 150));
   bar(1211, 41, 1259, 89);
   outtextxy(1215, 45, "||");
   if(abs(mousex()-1235)<25 && abs(mousey()-65)<25 && mousebuttons() == 1)
   {
      while(1)
      {
         rectangle(400, 200, 900, 600);
         setfillstyle(SOLID_FILL, COLOR(255, 255, 150));
         bar(401, 201, 899, 599);
         rectangle(850, 200, 900, 250);
         setfillstyle(SOLID_FILL, COLOR(240, 0, 0));
         bar(851, 201, 899, 249);
         setfillstyle(SOLID_FILL, COLOR(255, 255, 150));
         line(860, 210, 890, 240);
         line(860, 240, 890, 210);
         settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
         setusercharsize(1, 1, 4, 3);
         for(int i = 0; i < 2; i++)
         {
            rectangle(450, 290+150*i, 850, 390+150*i);
            rectangle(451, 291+150*i, 849, 389+150*i);
         }
         outtextxy(520, 320, "Новая игра");
         outtextxy(570, 470, "Меню");
         int button;
         if(abs(mousex()-650) < 200 && abs(mousey()-340) < 50) button = 0;
         else
         {
            if(abs(mousex()-650) < 200 && abs(mousey()-490) < 50) button = 1;
            else button = -1;
         }
         
         if(button != -1)
         {
            rectangle(440, 280+button*150, 860, 400+button*150);
            rectangle(441, 281+button*150, 859, 399+button*150);
         }
         
         if(mousebuttons() == 1)
         {
            if(abs(mousex()-875) < 25 && abs(mousey()-225) < 25)
            {
               while(mousebuttons());
               return;
            }
            switch(button)
            {
               case 0:
               {
                  new_game();
                  while(mousebuttons());
                  return;
               }
               case 1:
               {
                  new_game();
                  ingame = 0;
                  while(mousebuttons());
                  return;
               }
            }
         }
         
         setvisualpage(page);
         delay(100);
      }
   }
}

void draw_game(int po[6])
{
   clearviewport();
   putimage(0, 0, picg, COPY_PUT);
   for(int i = 0; i < n; i++)
   {
      color_ball(Balls[i].color);
      fillellipse(Balls[i].x, Balls[i].y, radius, radius);
   }
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(1, 1, 5, 4);
   char text[10];
   sprintf(text, "%d", score);
   outtextxy(width-150, height-100, text);
   drawpoly(3, po);
   setfillstyle(SOLID_FILL, COLOR(255, 200, 100));
   fillpoly(3, po);
   color_ball(zu_ball.color);
   fillellipse(zu_ball.x, zu_ball.y, radius-2, radius-2);
   stop();
}

void stabilization()
{
   for(int i = n-2; i >= 0; i--)
   {
      for(int k = i+1; k < n; k++)
      {
         go_ball(i, k);
         set_ball(i, Balls[i].fi);
      }
   }
}

void chek(int i, int po[6])
{
   while(1)
   {
      int indentic = 1, left = 0, right = 0;
      for(int k = 1; k <= i; k++)
      {
         if(Balls[i-k].color == Balls[i].color) indentic += 1;
         
         if(Balls[i-k].color != Balls[i].color)
         {
            left = k-1;
            break;
         }
         if(k == i && Balls[i-k].color == Balls[i].color)
         {
            left = k;
            break;
         }
      }
      for(int k = 1; k+i < n; k++)
      {
         if(Balls[i+k].color == Balls[i].color) indentic += 1;
         
         if(Balls[i+k].color != Balls[i].color || k+i+1 == n && Balls[i+k].color == Balls[i].color)
         {
            if(k+i+2 == n && Balls[i+k].color == Balls[i].color) k++;
            right = k-1;
            break;
         }
      }
      
      if(indentic < 3) 
      {
         zuballC();
         return;
      }
      n = n - indentic;
      if(n==0 && score > 2500)// победа
      {
         settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
         outtextxy(550, 380, "Победа");
         setvisualpage(page);
         delay(2000);
         ingame = 0;
         new_game();
         zuballC();
         return;
      }
      for(int k = 0; k < i-left; k++) Balls[k].fi = Balls[k+indentic].fi;
      for(int k = i-left; k < n; k++) Balls[k] = Balls[k+indentic];
      stabilization();
      score += 50*indentic;
      i -= left;
      zuballC();
      setactivepage(page);
      draw_game(po);
      setvisualpage(page);
      delay(100);
   }
}

void fly_ball(int po[6]) // полёт шара после выстрела
{
   zu_ball.x += 23*cos(zu_ball.fi);
   zu_ball.y += 23*sin(zu_ball.fi);
   if(abs(zu_ball.x-width/2) > width/2 || abs(zu_ball.y-height/2) > height/2)
   {
      zuballC();
      return;
   }
   for(int i = 0; i < n; i++)
   {
      double x = Balls[i].x-zu_ball.x;
      double y = Balls[i].y-zu_ball.y;
      if(sqrt(x*x+y*y) <= radius+1)// попали в шар
      {
         for(int k = n; k > i; k--)
         {
            Balls[k] = Balls[k-1];
         }
         Balls[i].color = zu_ball.color;
         n++;
         chek(i, po);
         return;
      }
   }
}

int main()
{
   initwindow( width, height,"ZUMA",75,25);
   picm=loadBMP("menu.bmp"); // Загрузка картинки
   if(picm==NULL) exit(1); // Ошибка при загрузке
   picg=loadBMP("game.bmp"); // Загрузка картинки
   if(picg==NULL) exit(1); // Ошибка при загрузке
   
   int button = 0; // кнопка на которую навелись
   double fim; //угол отклонения мыши от оси Ox
   int tim = 0; // количество шаров и таймер появления нового
   int po[6]; // вершины центрального треугольника
   srand(time(0));
   setbkcolor(COLOR(255, 255, 150));
   new_game();
   setcolor(BLACK);
   
   while(1)
   {
      page = 1-page;
      setactivepage(page);
      if(1-ingame)
      {
         button = manage_menu(button);
         print_menu(button);
         tim = 0;
      }
      else
      {
         int xv, yv, xk, yk;
         double xpi, ypi;
         xv = mousex() - width/2;
         yv = mousey() - height/2;
         fim = asin(yv / pow(xv*xv + yv*yv, 1.0/2));
         if(xv < 0)
         {
            fim = pi - fim;
         }
         po[0] = width/2.0 + 60*cos(fim); // координаты углов треугольника
         po[1] = height/2.0 + 60*sin(fim);
         po[2] = width/2.0 + 60*cos(fim+2*pi/3);
         po[3] = height/2.0 + 60*sin(fim+2*pi/3);
         po[4] = width/2.0 + 60*cos(fim+4*pi/3);
         po[5] = height/2.0 + 60*sin(fim+4*pi/3);
         if(mousebuttons() == 1 && fly == 0 && !(abs(mousex()-1235) < 25 && abs(mousey()-65) < 25))
         {
            fly = 1;
            zu_ball.fi = fim;
         }
         if(fly)
         {
            fly_ball(po);
            if(n == 0) continue;
            for(int k = 0; k < n; k++)
            {
               set_ball(k, Balls[k].fi);
            }
         }
         while(1) // последний шар сдвигается, как бы толкая следующие
         {
            Balls[n-1].fi -= 0.001;
            double x, y;
            x = 25*Balls[n-1].fi*(-cos(Balls[n-1].fi))+width/2;
            y = 18*Balls[n-1].fi*(-sin(Balls[n-1].fi))+height/2;
            if((Balls[n-1].x-x)*(Balls[n-1].x-x)+(Balls[n-1].y-y)*(Balls[n-1].y-y) > speed*speed)
            {
               if(pow(Balls[n-1].x-x, 2)+pow(Balls[n-1].y-y, 2) > pow(speed, 2) + 2)
               {
                  Balls[n-1].fi += 0.0011;
               }
               else break;
            }
         }
         set_ball(n-1, Balls[n-1].fi);
         stabilization();// смещение остальных шаров
         tim++;
         
         if(tim == radius*2/speed) // добаление нового шара
         {
            if(score < 2500)
            {
               create_ball(n);
               n++;
            }
            tim = 0;
         }
         if(Balls[0].fi <= pi) // проигрыш
         {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
            outtextxy(550, 380, "Конец");
            setvisualpage(page);
            delay(3000);
            ingame = 0;
            new_game();
            continue;
         }
         draw_game(po);
      }
      if(exi == 1) break;
      setvisualpage(page);
      delay(20);
   }
   
   closegraph();
   
   return 0;
}