#include "stdio.h"
#include "stdlib.h"
#include "random"
#include "ctime"

#include "graphics.h"

double pi = 3.14; // число pi
int w = 1300, h = 800, radius = 25, speed = 3; //размер экрана, шара и скорость иъ перемещени€ по спирали

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

void zuballC(double zu_ball[5]) //шар в л€гушке
{
   zu_ball[0] = w/2;
   zu_ball[1] = h/2;
   zu_ball[2] = rand()%6+1;
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

void flyb(Ball Balls[150], double zu_ball[5], int &n, int &score) // полЄт шара после выстрела
{
   zu_ball[0] += 25*cos(zu_ball[3]);
   zu_ball[1] += 25*sin(zu_ball[3]);
   if(abs(zu_ball[0]-w/2) > w/2 || abs(zu_ball[1]-h/2) > h/2)
   {
      zuballC(zu_ball);
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
            if(Balls[i-k].color != zu_ball[2])
            {
               for(int l = 1; l+i < n; l++)
               {
                  if(Balls[i+l].color != zu_ball[2])
                  {
                     if(l+k < 4) 
                     {
                        zuballC(zu_ball);
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
                     zuballC(zu_ball);
                     return;
                  }
               }
            }
         }
         zuballC(zu_ball);
         break;
      }
   }
}

int main()
{
   int score = 0;
   double fim; //угол отклонени€ муши от оси Ox
   int n = 1, l = 0; // количество шаров и таймер по€влени€ нового
   int po[8]; // вершины центрального треугольника
   srand(time(0));
   initwindow( w, h,"ZUMA",75,25);
   setbkcolor(WHITE);
   Ball Balls[150];
   double zu_ball[5];
   zuballC(zu_ball);
   creatball(Balls[0]);
   setcolor(BLACK);
   while(1)
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
      po[0] = w/2.0 + 70*cos(fim);
      po[1] = h/2.0 + 70*sin(fim);
      po[2] = w/2.0 + 70*cos(fim+2*pi/3);
      po[3] = h/2.0 + 70*sin(fim+2*pi/3);
      po[4] = w/2.0 + 70*cos(fim+4*pi/3);
      po[5] = h/2.0 + 70*sin(fim+4*pi/3);
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
      if(l == radius*2/speed)
      {
         creatball(Balls[n]);
         l = 0;
         n++;
      }
      if(Balls[0].fi <= pi)
      {
         break;
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
      delay(20);
   }
   delay(100000);
   closegraph();
}




























