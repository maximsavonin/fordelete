#include "stdio.h"
#include "stdlib.h"
#include "random"
#include "ctime"

#include "graphics.h"

double pi = 3.14; // число pi
int w = 1300, h = 800, radius = 20, speed = 5; //размер экрана, шара и скорость иъ перемещени€ по спирали

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
   zu_ball[2] = 8;
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

void flyb(Ball Balls[150], double zu_ball[5], int &n) // полЄт шара после выстрела
{
   zu_ball[0] += 30*cos(zu_ball[3]);
   zu_ball[1] += 30*sin(zu_ball[3]);
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
         zuballC(zu_ball);
         n++;
         for(int k = 0; k <= i; k++)
         {
            for(int j = 0; j < 2*radius/speed; j++)
            {
               Ballgo(Balls[k]);
            }
         }
         break;
      }
   }
}

int main()
{
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
         flyb(Balls, zu_ball, n);
      }
      for(int i = 0; i < n; i++)
      {
         Ballgo(Balls[i]);
         setBall(Balls[i], Balls[i].fi);
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
      drawpoly(4, po);
      setfillstyle(SOLID_FILL, zu_ball[2]);
      fillellipse(zu_ball[0], zu_ball[1], radius, radius);
      delay(40);
   }
   delay(100000);
   closegraph();
}

































