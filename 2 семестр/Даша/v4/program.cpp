#include "stdio.h"
#include "stdlib.h"
#include "random"
#include "ctime"

#include "graphics.h"

double pi = 3.14; // число pi
int w = 1300, h = 800, radius = 25, speed = 2, score = 0, p = 0; //размер экрана, шара и скорость иъ перемещени€ по спирали
bool ingame = false;

struct Ball
{
   double x = 0;
   double y = 0;
   double fi = 0;
   int color = 0;
};

void copyball(Ball a, Ball &b) // копирование одной структуры в другую
{
   b.x = a.x;
   b.y = a.y;
   b.fi = a.fi;
   b.color = a.color;
}

void Ballgo(Ball &Balls) //движиение по троектории одного шара
{
   while(1)
   {
      Balls.fi -= 0.001;
      double x, y;
      x = 25*Balls.fi*(-cos(Balls.fi))+w/2;
      y = 18*Balls.fi*(-sin(Balls.fi))+h/2;
      if(pow(Balls.x-x, 2)+pow(Balls.y-y, 2) > pow(speed, 2))
      {
         if(pow(Balls.x-x, 2)+pow(Balls.y-y, 2) > pow(speed, 2) + 2)
         {
            Balls.fi += 0.0011;
         }
         else break;
      }
   }
}

void zuballC(Ball Balls[150], double zu_ball[5], int &n) //шар в л€гушке
{
   zu_ball[0] = w/2;
   zu_ball[1] = h/2;
   zu_ball[2] = Balls[rand()%n].color;
   zu_ball[4] = 0;
}

void setBall(Ball &a, double fi) // функци€ задани€ координат шара по углу
{
   a.fi = fi;
   a.x = 25*a.fi*(-cos(a.fi))+w/2;
   a.y = 18*a.fi*(-sin(a.fi))+h/2;
}

void creatball(Ball &a) // создаЄт новый шар в начале пути
{
   a.color = rand() % 6 + 1;
   setBall(a, 6.5*pi);
}

/*void delet(Ball Balls[150], double zu_ball[5], int &n, int &score)
{
   
}*/

void flyb(Ball Balls[150], double zu_ball[5], int &n, int &score) // полЄт шара после выстрела
{
   zu_ball[0] += 23*cos(zu_ball[3]);
   zu_ball[1] += 23*sin(zu_ball[3]);
   if(abs(zu_ball[0]-w/2) > w/2 || abs(zu_ball[1]-h/2) > h/2)
   {
      zuballC(Balls, zu_ball, n);
      return;
   }
   for(int i = 0; i < n; i++)
   {
      double x = Balls[i].x-zu_ball[0];
      double y = Balls[i].y-zu_ball[1];
      if(sqrt(x*x+y*y) <= radius+1)
      {
         for(int k = n; k > i; k--)
         {
            copyball(Balls[k-1], Balls[k]);
         }
         Balls[i].color = zu_ball[2];
         n++;
         for(int k = 1; k <= i; k++)
         {
            if(Balls[i-k].color != zu_ball[2] || k == i && Balls[i-k].color == zu_ball[2])
            {
               if(k == i && Balls[i-k].color == zu_ball[2]) k++;
               for(int l = 1; l+i < n; l++)
               {
                  if(Balls[i+l].color != zu_ball[2] || l+i+1 == n && Balls[i+l].color == zu_ball[2])
                  {
                     if(l+i+1 == n && Balls[i+l].color == zu_ball[2]) l++;
                     if(l+k < 4) 
                     {
                        zuballC(Balls, zu_ball, n);
                        return;
                     }
                     for(int j = 0; j <= i-k; j++)
                     {
                        Balls[j].fi = Balls[j+k+l].fi;
                     }
                     for(int j = i-k+1; j < n-k-l+1; j++)
                     {
                        copyball(Balls[j+k+l-1], Balls[j]);
                     }
                     score += 50*(l+k-1);
                     n = n - k - l + 1;
                     zuballC(Balls, zu_ball, n);
                     return;
                  }
               }
            }
         }
         zuballC(Balls, zu_ball, n);
         break;
      }
   }
}

void printmenu(int but){
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
   outtextxy(50, 50, "ZUMA");
   
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   rectangle(500, 290, 800, 390);
   rectangle(501, 291, 799, 389);
   outtextxy(540, 320, "»грать");
   rectangle(500, 440, 800, 540);
   rectangle(501, 441, 799, 539);
   outtextxy(530, 470, "ќб игре");
   rectangle(500, 590, 800, 690);
   rectangle(501, 591, 799, 689);
   outtextxy(540, 620, "¬ыход");
   
   if(but != -1){
      rectangle(490, 280+but*150, 810, 400+but*150);
      rectangle(491, 281+but*150, 809, 399+but*150);
   }
}

void managmenu(int &but){
   int x = mousex(), y = mousey();
   if(x > 500 && x < 800 && y > 300 && y < 400) but = 0;
   else
      {
      if(x > 500 && x < 800 && y > 450 && y < 550) but = 1;
      else
         {
         if(x > 500 && x < 800 && y > 600 && y < 700) but = 2;
         else but = -1;
      }
   }
   if(mousebuttons() == 1 && but == 0)
   {
      ingame = 1;
      printf("%d", score);
   }
   if(mousebuttons() == 1 && but == 1)
   {
      setfillstyle(SOLID_FILL, WHITE);
      rectangle(280, 200, 1020, 600);
      bar(281, 201, 1019, 599);
      rectangle(970, 200, 1020, 250);
      setfillstyle(SOLID_FILL, COLOR(240, 0, 0));
      bar(971, 201, 1019, 249);
      setfillstyle(SOLID_FILL, WHITE);
      line(980, 210, 1010, 240);
      line(980, 240, 1010, 210);
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
      outtextxy(300, 300, "ZUMA Ц казуальна€ игра, в которой");
      outtextxy(300, 330, "цель игры уничтожить л€гушкой все");
      outtextxy(300, 360, "разноцветные шарики, двигающиес€");
      outtextxy(300, 390, "цепочкой по экрану.");
      outtextxy(300, 420, "Ћ€гушка наводитс€ на курсор мыши");
      outtextxy(300, 450, "и по нажатию левой кнопки мыши");
      outtextxy(300, 480, "выстреливает.");
      setvisualpage(p);
      while(!(mousex() > 970 && mousex() < 1020 && mousey() > 200 && mousey() < 250 && mousebuttons() == 1));
   }
   if(mousebuttons() == 1 && but == 2)
      {
      exit(0);
   }
   while(mousebuttons() == 1);
}

void newgame(Ball Balls[150], double zu_ball[5], int &n)
{
   n = 1;
   score = 0;
   creatball(Balls[0]);
   zuballC(Balls, zu_ball, n);
}

int main()
{
   int but = 0;
   double fim; //угол отклонени€ муши от оси Ox
   int n = 1, l = 0; // количество шаров и таймер по€влени€ нового
   int po[8]; // вершины центрального треугольника
   srand(time(0));
   initwindow( w, h,"ZUMA",75,25);
   setbkcolor(WHITE);
   Ball Balls[150];
   double zu_ball[5];
   newgame(Balls, zu_ball, n);
   setcolor(BLACK);
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      if(!ingame)
      {
         managmenu(but);
         printmenu(but);
      }
      else
      {
         int xv, yv, xk, yk;
         double xpi, ypi;
         xv = mousex() - w/2;
         yv = mousey() - h/2;
         fim = asin(yv / pow(xv*xv + yv*yv, 1.0/2));
         if(xv < 0)
         {
            fim = pi - fim;
         }
         po[0] = w/2.0 + 60*cos(fim);
         po[1] = h/2.0 + 60*sin(fim);
         po[2] = w/2.0 + 60*cos(fim+2*pi/3);
         po[3] = h/2.0 + 60*sin(fim+2*pi/3);
         po[4] = w/2.0 + 60*cos(fim+4*pi/3);
         po[5] = h/2.0 + 60*sin(fim+4*pi/3);
         po[6] = po[0];
         po[7] = po[1];
         if(mousebuttons() == 1 && zu_ball[4] == 0)
         {
            zu_ball[4] = 1;
            zu_ball[3] = fim;
         }
         if(zu_ball[4])
         {
            flyb(Balls, zu_ball, n, score);
            for(int k = 0; k < n; k++)
            {
               setBall(Balls[k], Balls[k].fi);
            }
         }
         while(1)
         {
            Balls[n-1].fi -= 0.001;
            double x, y;
            x = 25*Balls[n-1].fi*(-cos(Balls[n-1].fi))+w/2;
            y = 18*Balls[n-1].fi*(-sin(Balls[n-1].fi))+h/2;
            if(pow(Balls[n-1].x-x, 2)+pow(Balls[n-1].y-y, 2) > pow(speed, 2))
            {
               if(pow(Balls[n-1].x-x, 2)+pow(Balls[n-1].y-y, 2) > pow(speed, 2) + 2)
               {
                  Balls[n-1].fi += 0.0011;
               }
               else break;
            }
         }
         setBall(Balls[n-1], Balls[n-1].fi);
         for(int i = n-2; i >= 0; i--)
         {
            for(int k = i+1; k < n; k++)
            {
               while(1)
               {
                  double x, y, xv, yv;
                  x = 25*Balls[i].fi*(-cos(Balls[i].fi))+w/2;
                  y = 18*Balls[i].fi*(-sin(Balls[i].fi))+h/2;
                  xv = abs(x-Balls[k].x);
                  yv = abs(y-Balls[k].y);
                  if(sqrt(xv*xv+yv*yv) < 2*radius)
                  {
                     Balls[i].fi -= 0.0002;
                  }
                  else break;
               }
               setBall(Balls[i], Balls[i].fi);
            }
         }
         l++;
         if(l == radius*2/speed && score < 2000)
         {
            creatball(Balls[n]);
            l = 0;
            n++;
         }
         if(n==0)
         {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
            outtextxy(550, 380, "ѕобеда");
            setvisualpage(p);
            delay(3000);
            ingame = false;
            newgame(Balls, zu_ball, n);
            continue;
         }
         if(Balls[0].fi <= pi)
         {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
            outtextxy(550, 380, " онец");
            setvisualpage(p);
            delay(3000);
            ingame = false;
            newgame(Balls, zu_ball, n);
            continue;
         }
         clearviewport();
         for(int i = 0; i < n; i++)
         {
            setfillstyle(SOLID_FILL, Balls[i].color);
            fillellipse(Balls[i].x, Balls[i].y, radius, radius);
         }
         settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
         char text[10];
         sprintf(text, "%d", score);
         outtextxy(w-100, h-100, text);
         drawpoly(4, po);
         setfillstyle(SOLID_FILL, zu_ball[2]);
         fillellipse(zu_ball[0], zu_ball[1], radius, radius);
      }
      delay(20);
      setvisualpage(p);
   }
   getch();
   closegraph();
}

























