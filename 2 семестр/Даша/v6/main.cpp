#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graphics.h"

double pi = acos(-1); // ����� pi
int width = 1300, height = 800; //������ ������
int radius = 25, speed = 2; // ������ ���� � ��� ��������
int score = 0, page = 0;// ���� � ����� ������� � ������� ��������
int ingame = 0, n = 0; // � ���� � ���������� ����� �� ������
int ex = 0; // �������� ���������

typedef struct Ball
{
   double x = 0;// ���������� ���� �� x
   double y = 0;// ���������� ���� �� y
   double fi = 0; // ���� �������� ���� �� ��� Ox
   int color = 0; // ���� ����
}Ball;

Ball Balls[150]; // ������ �����

void goBall(int a, int b) //��������� �� ���������� ������ ����
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

void zuballC(double zu_ball[5]) //��� � �������
{
   zu_ball[0] = width/2;
   zu_ball[1] = height/2;
   zu_ball[2] = Balls[rand()%n].color;
   zu_ball[4] = 0;
}

void setBall(int a, double fi) // ������� ������� ��������� ���� �� ����
{
   Balls[a].fi = fi;
   Balls[a].x = 25*Balls[a].fi*(-cos(Balls[a].fi))+width/2;
   Balls[a].y = 18*Balls[a].fi*(-sin(Balls[a].fi))+height/2;
}

void createBall(int a) // ������ ����� ��� � ������ ����
{
   Balls[a].color = rand() % 6 + 1;
   setBall(a, 6.5*pi);
}

void newgame(double zu_ball[5]) // ������� ���������� ��� ����� ����
{
   n = 1;
   score = 0;
   createBall(0);
   zuballC(zu_ball);
}

void flyBall(double zu_ball[5]) // ���� ���� ����� ��������
{
   int indentic = 1, left = 0, right = 0;
   zu_ball[0] += 23*cos(zu_ball[3]);
   zu_ball[1] += 23*sin(zu_ball[3]);
   if(abs(zu_ball[0]-width/2) > width/2 || abs(zu_ball[1]-height/2) > height/2)
   {
      zuballC(zu_ball);
      return;
   }
   for(int i = 0; i < n; i++)
   {
      double x = Balls[i].x-zu_ball[0];
      double y = Balls[i].y-zu_ball[1];
      if(sqrt(x*x+y*y) <= radius+1)// ������ � ���
      {
         for(int k = n; k > i; k--)
         {
            Balls[k] = Balls[k-1];
         }
         Balls[i].color = zu_ball[2];
         n++;
         for(int k = 1; k <= i; k++)
         {
            if(Balls[i-k].color == zu_ball[2]) indentic += 1;
            
            if(Balls[i-k].color != zu_ball[2] || k == i && Balls[i-k].color == zu_ball[2])
            {
               left = k-1;
               break;
            }
         }
         for(int k = 1; k+i < n; k++)
         {
            if(Balls[i+k].color == zu_ball[2]) indentic += 1;
            
            if(Balls[i+k].color != zu_ball[2] || k+i+1 == n && Balls[i+k].color == zu_ball[2])
            {
               if(k+i+2 == n && Balls[i+k].color == zu_ball[2]) k++;
               right = k-1;
               break;
            }
         }
         
         if(indentic < 3) 
         {
            zuballC(zu_ball);
            return;
         }
         n = n - indentic;
         if(n==0)// ������
         {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
            outtextxy(550, 380, "������");
            setvisualpage(page);
            delay(2000);
            ingame = 0;
            newgame(zu_ball);
            return;
         }
         for(int k = 0; k < i-left; k++)
         {
            Balls[k].fi = Balls[k+indentic].fi;
         }
         for(int k = i-left; k < n; k++)
         {
            Balls[k] = Balls[k+indentic];
         }
         score += 50*indentic;
         zuballC(zu_ball);
         return;
      }
   }
}

void print_menu(int button, IMAGE *pic) // ��������� �������� ����
{
   clearviewport();
   putimage(0, 0, pic, COPY_PUT);
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(10, 4, 4, 1);
   outtextxy(800, 20, "ZUMA");
   
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(1, 1, 4, 3);
   setfillstyle(SOLID_FILL, COLOR(255, 255, 150));
   for(int i = 0; i < 3; i++)
   {
      rectangle(500, 290+150*i, 800, 390+150*i);
      rectangle(501, 291+150*i, 799, 389+150*i);
      bar(502, 292+150*i, 798, 388+150*i);
   }
   outtextxy(570, 320, "������");
   outtextxy(560, 470, "�� ����");
   outtextxy(570, 620, "�����");
   
   if(button != -1)
   {
      rectangle(490, 280+button*150, 810, 400+button*150);
      rectangle(491, 281+button*150, 809, 399+button*150);
   }
}

int manage_menu(int button) // ��������� �������� ���� managemenu
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
            outtextxy(300, 300, "ZUMA � ���������� ����, � �������"); //������� ��������� ����
            outtextxy(300, 330, "���� ���� ���������� �������� ���");
            outtextxy(300, 360, "������������ ������, �����������");
            outtextxy(300, 390, "�������� �� ������.");
            outtextxy(300, 420, "������� ��������� �� ������ ����");
            outtextxy(300, 450, "� �� ������� ����� ������ ����");
            outtextxy(300, 480, "������������.");
            setvisualpage(page);
            while(!(mousex() > 970 && mousex() < 1020 && mousey() > 200 && mousey() < 250 && mousebuttons() == 1));
            break;
         }
         case 2:
         {
            ex = 1;
            break;
         }
      }
   }
   while(mousebuttons() == 1);
   return button;
}

void colorball(int a)
{
   switch(a)
   {
      case 1:
      {
         setfillstyle(SOLID_FILL, COLOR(255, 0, 0));
         break;
      }
      case 2:
      {
         setfillstyle(SOLID_FILL, COLOR(0, 255, 0));
         break;
      }
       case 3:
      {
         setfillstyle(SOLID_FILL, COLOR(0, 0, 255));
         break;
      }
       case 4:
      {
         setfillstyle(SOLID_FILL, COLOR(255, 128, 64));
         break;
      }
       case 5:
      {
         setfillstyle(SOLID_FILL, COLOR(128, 0, 255));
         break;
      }
       case 6:
      {
         setfillstyle(SOLID_FILL, COLOR(0, 255, 255));
         break;
      }
   }
}

void stop(double zu_ball[5])
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
         outtextxy(520, 320, "����� ����");
         outtextxy(570, 470, "����");
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
                  newgame(zu_ball);
                  while(mousebuttons());
                  return;
               }
               case 1:
               {
                  newgame(zu_ball);
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

int main()
{
   initwindow( width, height,"ZUMA",75,25);
   IMAGE *picm, *picg;
   picm=loadBMP("menu.bmp"); // �������� ��������
   if(picm==NULL) exit(1); // ������ ��� ��������
   picg=loadBMP("game.bmp"); // �������� ��������
   if(picg==NULL) exit(1); // ������ ��� ��������
   
   int button = 0;
   double fim; //���� ���������� ���� �� ��� Ox
   int l = 0; // ���������� ����� � ������ ��������� ������
   int po[8]; // ������� ������������ ������������
   srand(time(0));
   setbkcolor(COLOR(255, 255, 150));
   double zu_ball[5];
   newgame(zu_ball);
   setcolor(BLACK);
   
   while(1)
   {
      page = 1-page;
      setactivepage(page);
      if(1-ingame)
      {
         button = manage_menu(button);
         print_menu(button, picm);
         l = 0;
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
         po[0] = width/2.0 + 60*cos(fim); // ���������� ����� ������������
         po[1] = height/2.0 + 60*sin(fim);
         po[2] = width/2.0 + 60*cos(fim+2*pi/3);
         po[3] = height/2.0 + 60*sin(fim+2*pi/3);
         po[4] = width/2.0 + 60*cos(fim+4*pi/3);
         po[5] = height/2.0 + 60*sin(fim+4*pi/3);
         po[6] = po[0];
         po[7] = po[1];
         if(mousebuttons() == 1 && zu_ball[4] == 0 && !(abs(mousex()-1235) < 25 && abs(mousey()-65) < 25))
         {
            zu_ball[4] = 1;
            zu_ball[3] = fim;
         }
         if(zu_ball[4])
         {
            flyBall(zu_ball);
            if(n == 0) continue;
            for(int k = 0; k < n; k++)
            {
               setBall(k, Balls[k].fi);
            }
         }
         while(1) // ��������� ��� ���������� ��� �� ������ ���������
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
         setBall(n-1, Balls[n-1].fi);
         for(int i = n-2; i >= 0; i--)// �������� ��������� �����
         {
            for(int k = i+1; k < n; k++)
            {
               goBall(i, k);
               setBall(i, Balls[i].fi);
            }
         }
         l++;
         if(l == radius*2/speed && score < 2500) // ��������� ������ ����
         {
            createBall(n);
            l = 0;
            n++;
         }
         if(Balls[0].fi <= pi) // ��������
         {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
            outtextxy(550, 380, "�����");
            setvisualpage(page);
            delay(3000);
            ingame = 0;
            newgame(zu_ball);
            continue;
         }
         clearviewport();
         putimage(0, 0, picg, COPY_PUT);
         for(int i = 0; i < n; i++)
         {
            colorball(Balls[i].color);
            fillellipse(Balls[i].x, Balls[i].y, radius, radius);
         }
         settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
         setusercharsize(1, 1, 5, 4);
         char text[10];
         sprintf(text, "%d", score);
         outtextxy(width-150, height-100, text);
         drawpoly(4, po);
         setfillstyle(SOLID_FILL, COLOR(255, 200, 100));
         fillpoly(4, po);
         colorball(zu_ball[2]);
         fillellipse(zu_ball[0], zu_ball[1], radius-2, radius-2);
         stop(zu_ball);
      }
      if(ex == 1) break;
      setvisualpage(page);
      delay(20);
   }
   
   closegraph();
   
   return 0;
}