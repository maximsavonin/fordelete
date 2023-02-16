#include <stdio.h>
#include <math.h>
#include <random>
#include <ctime>

#include "graphics.h"

int points[100]; // ������ ����� ����� � �� ������
int player[2]; // ����� ���������� ������� ������
int num = 0, p = 0; // ����� �������� �� ����� � ����� ������������ ��������
int play = 0, button = 0; // ������ ��� � ���� � �� ����� ������ ������ �����
int nplayer = 0;

void startgame(){
   player[0] = -1;
   player[1] = -1;
}

void drawcube(int n)
{
   rectangle(40, 300, 110, 370);
   setlinestyle(SOLID_LINE, 1, 3);
   if(n%2 == 1)
   {
      circle(75, 335, 3);
   }
   if(n > 1)
   {
      circle(95, 315, 3);
      circle(55, 355, 3);
      if(n > 3)
      {
         circle(95, 355, 3);
         circle(55, 315, 3);
         if(n == 6)
         {
            circle(95, 335, 3);
            circle(55, 335, 3);
         }
      }
   }   
   setlinestyle(SOLID_LINE, 1, 1);
}

void draw(IMAGE *pic){ // ��������� ����
   p = 1-p;
   setactivepage(p);
   clearviewport();
   int pol[8];
   setusercharsize(4, 10, 1, 2);
   putimage(150, 0, pic, COPY_PUT);
   for(int i = 1; i >= 0; i--){
      if(player[i] == -1){
         pol[0] = 125;
         pol[1] = 690-i*15;
      }
      else{
         if(player[i] % 20 > 9){
            pol[0] = 825-player[i]%10*70;
            pol[1] = 690-i*15-player[i]/10*70;
         }
         else{
            pol[0] = 195+player[i]%10*70;
            pol[1] = 690-i*15-player[i]/10*70;
         }
      }
      pol[2] = pol[0]-20;
      pol[3] = pol[1];
      pol[4] = pol[0]-10;
      pol[5] = pol[1]-20;
      pol[6] = pol[0];
      pol[7] = pol[1];
      
      if(i == 0) setfillstyle(SOLID_FILL, RED);
      else setfillstyle(SOLID_FILL, BLUE);
      fillpoly(4, pol);
   }
   
   
   
   rectangle(20, 400, 130, 450);
   if(abs(mousex()-75) <= 55 && abs(mousey()-425) <= 25){
      setfillstyle(SOLID_FILL, WHITE);
      bar(21, 401, 129, 449);
   }
   outtextxy(26, 415, "������� �����");
   drawcube(num);
   
   setvisualpage(p);
}

void rand_num(IMAGE *pic){ // �������� �����, ��� ������ � ���������� � ��������� ����� �����
   if(abs(mousex()-75) <= 55 && abs(mousey()-425) <= 25 && mousebuttons() == 1){
      for(int i = 0; i < 15; i++){
         num = rand()%6 + 1;
         draw(pic);
         delay(100);
      }
      bool bl = false;
      for(int i = 0; i < num; i++){
         if(bl){
            player[nplayer]--;
         }
         else{
            player[nplayer]++;
         }
         if(player[nplayer] > 99){
            bl = true;
            player[nplayer] = 98;
         }
         draw(pic);
         delay(100);
      }
      if(points[player[nplayer]] != player[nplayer]){
         player[nplayer] = points[player[nplayer]];
      }
      if(player[nplayer] == 99){
         play = 0;
         setfillstyle(SOLID_FILL, BLACK);
         bar(150, 280, 650, 420);
         settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
         setusercharsize(3, 2, 3, 2);
         outtextxy(300, 300, "�����");
         if(player[nplayer] == 0) outtextxy(170, 350, "������ ������ 0");
         else outtextxy(170, 350, "������ ������ 1");
         delay(2000);
         startgame();
         return;
      }
      if(num != 6){
         nplayer = (nplayer+1)%2;
      }
      delay(700);
   }
}

void drawmenu(){ // ��������� ����
   p = 1-p;
   setactivepage(p);
   clearviewport();
   
   if(button != -1){
      bar(326, 251+button*100, 524, 299+button*100);
   }
   
   settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(1, 1, 3, 2);
   outtextxy(220, 100, "�������������� ����");
   outtextxy(200, 140, "� ���������� ��������");
   
   setusercharsize(4, 5, 1, 1);
   for(int i = 0; i < 4; i++){
      rectangle(325, 250+i*100, 525, 300+i*100);
   }
   outtextxy(380, 260, "������");
   outtextxy(365, 360, "�� ����");
   outtextxy(365, 460, "�� ������");
   outtextxy(375, 560, "�����");
   
   setvisualpage(p);
}

void abovegame(){ // ��������� �� ����
   while(1){
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
      setusercharsize(1, 1, 3, 2);
      outtextxy(350, 150, "�� ����");
      
      setusercharsize(1, 2, 1, 2);
      outtextxy(50, 250, "� ����� ����� ������, ������� ��������� ����� � ������� ���� ����� ��");
      outtextxy(50, 275, "����� ���������� �����, ������� ������ �� ��������� �����.");
      outtextxy(50, 305, "� ���� �� ��������� ����� �������� ����� 6, �� ����� ������ ��� ���� ���,");
      outtextxy(50, 330, "����� ��� ��������� ����������.");
      outtextxy(50, 360, "� ����� ���� �������� ��������� �� ������ 100.");
      outtextxy(50, 390, "� �� ���� ������� ����� ���������� ��������, ������� �������� �� �����,");
      outtextxy(50, 415, "��� ����, ������� ������� �� ����.");
      outtextxy(50, 445, "� �����, ����������� ������ �� ������ 100, ��������� �����������.");
      
      if(abs(425-mousex()) < 100 && abs(575-mousey()) < 25){
         bar(326, 551, 524, 599);
         if(mousebuttons() == 1){
            return;
         }
      }
      
      setusercharsize(4, 5, 1, 1);
      rectangle(325, 550, 525, 600);
      outtextxy(375, 560, "�����");
      
      setvisualpage(p);
      delay(50);
   }
}

void above(){ // ��������� �� ������
   while(1){
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
      setusercharsize(1, 1, 3, 2);
      outtextxy(350, 150, "�� ������");
      
      setusercharsize(1, 2, 1, 2);
      outtextxy(50, 250, "���� ������, � ������� ���������, ������� ����� ������");
      outtextxy(50, 275, "��-211.'�������������� ���� � ���������� ��������' ��� ������");
      outtextxy(50, 305, "��������� ���������� ����!");
      outtextxy(50, 330, "������������� ������� ���������!");
      
      if(abs(425-mousex()) < 100 && abs(575-mousey()) < 25){
         bar(326, 551, 524, 599);
         if(mousebuttons() == 1){
            return;
         }
      }
      
      setusercharsize(4, 5, 1, 1);
      rectangle(325, 550, 525, 600);
      outtextxy(375, 560, "�����");
      
      setvisualpage(p);
      delay(50);
   }
}

void treatmenu(){ // ��������� ����
   int x = mousex(), y = mousey();
   button = -1;
   for(int i = 0; i < 4; i++)
   {
      if(abs(425-x) < 100 && abs(275+100*i-y) < 25){
         button = i;
      }
   }
   
   if(mousebuttons() == 1)
   {
      if(button == 0){
         play = 1;
      }
      if(button == 1){
         abovegame();
      }
      if(button == 2){
         above();
      }
      if(button == 3){
         exit(0);
      }
   }
}

int main(){
   initwindow(850, 700, "Win", 50, 50);
   IMAGE *picm;
   picm=loadBMP("map.bmp"); // �������� ��������
   if(picm==NULL) exit(1); // ������ ��� ��������
   srand(time(0));
   startgame();
   for(int i = 0; i < 100; i++){
      points[i] = i;
   }
   points[0] = 37; // �������� ������ ����� �������� ����
   points[3] = 13;
   points[8] = 30;
   points[15] = 5;
   points[20] = 41;
   points[27] = 83;
   points[35] = 43;
   points[46] = 25;
   points[48] = 29;
   points[50] = 66;
   points[55] = 52;
   points[61] = 18;
   points[62] = 59;
   points[70] = 90;
   points[61] = 18;
   points[79] = 99;
   points[86] = 23;
   points[92] = 72;
   points[94] = 74;
   points[97] = 77;
   
   play = 0;
   while(1){
      if(play){
         draw(picm);
         rand_num(picm);
      }
      else{
         treatmenu();
         drawmenu();
      }
      delay(100);
   }

   getch();
   closegraph();
}