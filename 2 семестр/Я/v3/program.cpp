#include <iostream>
#include <vector>
#include <random>
#include <ctime>

#include "graphics.h"

using namespace std;

bool ingame = false; //� ���� ��� � ����
int h = 40, score = 0;  // ������ ������� �������� � ����
int s_y = 100, s_x = 100; // ������ �����
int x_d = 0, y_d = 0; // ����� ���������� �������� �������
int n_y = 15, n_x = 9; // ������ ����� ����
int map[11][16]; //�����
int obj[2][3]; //�������� � �������� �������

void new_game() //��������� ����
{
   score = 0;
   for(int i = 0; i < 2; i++)
   {
      for(int k = 0; k < 3; k++)
      {
         obj[i][k] = 0;
      }
   }
   obj[1][0] = rand()%6+1;
   obj[1][1] = rand()%6+1;
   obj[1][2] = rand()%6+1;
    
   for(int i = 0; i < n_x+2; i++)
   {
      for(int k = 0; k < n_y+1; k++)
      {
         if(i%(n_x+1) == 0 or k == n_y)
            map[i][k] = 10;
         else
            map[i][k] = 0;
      }
   }
}

void draw(int x, int y, int col) // ��������� �������� ������������ �����
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

void down(int &falling) // ������� �����������
{
   for(int i = n_x; i > 0; i--)
      {
         for(int k = n_y-1; k > -1; k--)
         {
            if(map[i][k+1] == 0)
            {
               if(i == x_d and k == y_d)
               {
                  y_d += 1;
               }
               map[i][k+1] = map[i][k];
               map[i][k] = 0;
            }
            else
            {
               if(i == x_d and k == y_d)
               {
                  falling = 0;
               }
            }
         }
      }
}

void move_line(int turn) // �������� ������� � �������
{
   if(map[x_d+turn][y_d] == 0 and map[x_d+turn][y_d-1] == 0 and map[x_d+turn][y_d-2] == 0)
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

void checking(int &kol) // �������� 3 � ���
{
   int again = 1, max_n = 0;
   while(again == 1)
   {
      for(int i = 0; i < max_n; i++)
      {
         int x_d = 5, y_d = 2, falling = 1;
         down(falling);
         for(int i = 1; i < n_x+1; i++)
         {
            for(int k = 0; k < n_y-3; k++)
            {
               draw(s_x+i*h, s_y+k*h, map[i][k+3]);
            }
         }
         delay(50);
      }
      
      again = 0;
      max_n = 1;
      for(int i = 3; i < n_y; i++)
      {
         int n = 0, col = 0;
         for(int k = 1; k < n_x+1; k++)
         {
            if(col == map[k][i])
            {
               n++;
            }
            else
            {
               if(n > 2 and col != 0)
               {
                  again = 1;
                  kol++;
                  score += 100*pow(1.5, n-3);
                  for(int l = 0; l < n; l++)
                  {
                     map[k-l-1][i] = 0;
                  }
               }
               n = 1;
               col = map[k][i];
            }
         }
         if(n > 2 and col != 0)
         {
            again = 1;
            kol++;
            score += 100*pow(1.5, n-3);
            for(int l = 0; l < n; l++)
            {
               map[n_x-l][i] = 0;
            }
         }
      }
      
      for(int i = 1; i < n_x+1; i++)
      {
         int n = 0, col = 0;
         for(int k = 3; k < n_y; k++)
         {
            if(col == map[i][k])
            {
               n++;
            }
            else
            {
               if(n > 2 and col != 0)
               {
                  if(n > max_n) max_n = n;
                  again = 1;
                  kol++;
                  score += 100*pow(1.5, n-3);
                  for(int l = 0; l < n; l++)
                  {
                     map[i][k-l-1] = 0;
                  }
               }
               n = 1;
               col = map[i][k];
            }
         }
         if(n > 2 and col != 0)
         {
            if(n > max_n) max_n = n;
            again = 1;
            kol++;
            score += 100*pow(1.5, n-3);
            for(int l = 0; l < n; l++)
            {
               map[i][n_y-1-l] = 0;
            }
         }
      }
   }
}

void draw_menu(int &numbut) // ��������� ����
{
   clearviewport();
   
   rectangle(275, 280, 525, 350);
   rectangle(275, 390, 525, 460);
   rectangle(275, 500, 525, 570);
   rectangle(270, 275+numbut*110, 530, 355+numbut*110);
   
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(290, 150, "Columns");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(310, 310, "����� ����");
   outtextxy(335, 420, "�� ����");
   outtextxy(360, 530, "�����");   
}

void aboute_game() // ��������� �� ����
{
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(290, 150, "Columns");
   outtextxy(290, 200, "�� ����");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(90, 260, "������ ���� ������ ������� � �������");
   outtextxy(100, 280, "����� �������� �������� �� �������");
   outtextxy(95, 300, "��� ����� �������� �� ����� �������");
   outtextxy(105, 320, "� ������� ��������� �� ����������");
   outtextxy(105, 340, "���� ���������� 3 ���������� �����");
   outtextxy(100, 360, "� ���, � ������� ��� �� ���������, ��");
   outtextxy(270, 380, "��� ���������");
   rectangle(275, 560, 525, 630);
   rectangle(270, 555, 530, 635);
   outtextxy(360, 590, "�����");   
   int Key = getch();
   if(Key == 0) Key = getch();
   while(Key != KEY_ENTER)
   {
      int Key = getch();
      if(Key == 0) Key = getch();
   }
}

void menu_manager(int &numbut) // ��������� ����
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

void menu(int &numbut) // ����
{
   draw_menu(numbut);
   menu_manager(numbut);
}

void new_column(int p)// �������� ��������� �������
{
   for(int i = 1; i < n_x+1; i++)
   {
      if(map[i][2] != 0)
      {
         ingame = false;
         settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
         outtextxy(300, 320, "����� ����");   
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

void clik(int &del, int &kol) // ��������� ������� ������
{
   int Key = getch();
   if(Key == 0) Key = getch();
   switch(Key)
   {
      case KEY_LEFT:
      {
         move_line(-1);
         del = 200;
         kol++;
         break;
      }
      case KEY_RIGHT:
      {
         move_line(1);
         del=200;
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

void draw_game() // ��������� ����
{
   clearviewport();
   setcolor(WHITE);
   rectangle(s_x+h, s_y, s_x+h*n_x+h, s_y+(n_y-3)*h);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   char text[10];
   sprintf(text, "%d", score);
   outtextxy(s_x+h*n_x+h+50, s_y+(n_y-3)*h-100, text);
   for(int i = 1; i < n_x+1; i++)
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

int main()
{
   int del = 0, falling = 0; //�������� ����� ������� � ������ �� ���-���� � ���������� �����
   int numbut = 0, p = 0; // ����� ������ � ���� � ����� ��������
   srand(time(0));
   initwindow( 800, 700,"Columns",10,20);
   
   while(true)
   {
      if(!ingame)
      {
         menu(numbut);
      }
      else
      {
         p = 1-p;
         setactivepage(p);
         int kol = 0;
         del = 350;
         if(falling == 0)
         {
            checking(kol);
            new_column(p);
            falling = 1;
         }
         if(1 == kbhit())
         {
            clik(del, kol);
         }
         if(kol == 0)
         {
            down(falling);
         }
         draw_game();
         setvisualpage(p);
         delay(del);
      }
   }
   closegraph();
}