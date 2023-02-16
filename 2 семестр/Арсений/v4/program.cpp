#include "stdio.h"
#include "stdlib.h"
#include "random"
#include "ctime"

#include "graphics.h"

#define xmax 8 // ������ ����� �� �����������
#define ymax 10// ������ ����� �� ���������
#define size 50 // ������ ����������

int score = 0, button = -1; //���� � ����� ������
int game = 0, ex = 0; // � ���� ��, ����� �� ����
int map[ymax][xmax]; // ����� ����

void draw_sqr(int x, int y, int color){ // ��������� ����������
   setfillstyle(1, color);
   rectangle(size*(x+1), size*(y+1), size*(x+2), size*(y+2));
   bar(1+size*(x+1), 1+size*(y+1), size*(x+2)-1, size*(y+2)-1);
}

void draw_all(int x, int y, int kol, int &blink){ //��������� ����� � �����
   clearviewport();
   char text[6];
   sprintf(text, "%d", score);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
   outtextxy(700, 100, text);
   blink = 1-blink;
   for(int i = 0; i < ymax; i++){
      for(int k = 0; k < xmax; k++){
         if(kol == 1 && x == k && y == i && blink == 1) draw_sqr(k, i, 0);
         else draw_sqr(k, i, map[i][k]);
      }
   }
}

void swap(int &kol, int &x, int &y){ // ����� ����������� � ������ �� �������
   if(mousebuttons() == 1){
      if(kol != 0 && kol != 1){
         kol = 0;
      }
      if(mousex() < size || mousex() > (xmax+2)*size || mousey() < size || mousey() > (ymax+2)*size) return;
      if(kol == 0){
         x = (mousex()-size)/size;
         y = (mousey()-size)/size;
         kol++;
      }
      else{
         if(abs(x-(mousex()-size)/size) + abs(y-(mousey()-size)/size) < 2){
            int a;
            a = map[y][x];
            map[y][x] = map[(mousey()-size)/size][(mousex()-size)/size];
            map[(mousey()-size)/size][(mousex()-size)/size] = a;
            kol = 0;
         }
      }
      while(mousebuttons() == 1);
   }
}

bool fall(){ // ������� ���� ������� �������
   int n = 0;
   for(int i = ymax-2; i >= 0 ; i--){
      for(int k = 0; k < xmax; k++){
         if(map[i+1][k] == 0 and map[i][k] != 0){
            map[i+1][k] = map[i][k];
            map[i][k] = 0;
            n++;
         }
      }
   }
   for(int i = 0; i < xmax; i++){
      if(map[0][i] == 0){
         map[0][i] = rand()%6+1;
      }
   }
   if(n != 0) return false;
   return true;
}

void chop(){ // �������� 3 � ����� � ���
   int map_corect[ymax][xmax];
   for(int i = 0; i < ymax; i++){
      for(int k = 0; k < xmax; k++){
         map_corect[i][k] = map[i][k];
      }
   }
   
   for(int i = 0; i < ymax; i++){
      int repeat = 1, colorr = map_corect[i][0];
      for(int k = 1; k < xmax; k++){
         if(colorr == map_corect[i][k]){
            repeat++;
         }
         else{
            if(repeat >= 3){
               score += pow(150, repeat-2)/pow(100, repeat-3);
               for(int j = 0; j < repeat; j++){
                  map[i][k-1-j] = 0;
               }
            }
            repeat = 1;
            colorr = map_corect[i][k];
         }
      }
      if(repeat >= 3){
         score += pow(150, repeat-2)/pow(100, repeat-3); 
         for(int j = 0; j < repeat; j++){
            map[i][xmax-1-j] = 0;
         }
      }
   }
   
   for(int i = 0; i < xmax; i++){
      int repeat = 1, colorr = map_corect[0][i];
      for(int k = 1; k < ymax; k++){
         if(colorr == map_corect[k][i]){
            repeat++;
         }
         else{
            if(repeat >= 3){
               score += pow(150, repeat-2)/pow(100, repeat-3);
               for(int j = 0; j < repeat; j++){
                  map[k-1-j][i] = 0;
               }
            }
            repeat = 1;
            colorr = map_corect[k][i];
         }
      }
      if(repeat >= 3){
         score += pow(150, repeat-2)/pow(100, repeat-3);
         for(int j = 0; j < repeat; j++){
            map[ymax-1-j][i] = 0;
         }
      }
   }
}

void creatmap(){ // �������� ����� �����
   for(int i = 0; i < ymax; i++){
      for(int k = 0; k < xmax; k++){
         map[i][k] = rand()%6+1;
      }                                      
   }
   for(int i = 0; i < 150; i++){
      if(fall()) chop();
   }
   score = 0;
}

void draw_aboutgame(){ // ��������� ���� �� ����
   int p = 0;
   while(!(mousex() > 300 && mousex() < 500 && mousey() > 550 && mousey() < 600 && mousebuttons() == 1))
   {
      setactivepage(p);
      p = 1-p;
      clearviewport();
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
      outtextxy(250, 100, "�� ����");
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
      outtextxy(210, 180, "������� ������� ���");
      outtextxy(140, 205, "������� �� ������� ���������,");
      outtextxy(80, 230, "������ ������ ����������� � ���������,");
      outtextxy(110, 255, "����������� ���������� �� �������");
      outtextxy(215, 280, "����� ������� ���,");
      outtextxy(140, 305, "����� ������� �������� �����");
      outtextxy(190, 330, "��������� ����������,");
      outtextxy(120, 355, "����� ���������� ������� �������");
      outtextxy(130, 380, "��������� �������� ��������,");
      outtextxy(50, 405, "��� ����� �������� ��� ������������� ����");
      outtextxy(350, 570, "�����");
      if(mousex() > 300 && mousex() < 500 && mousey() > 550 && mousey() < 600) rectangle(290, 540, 510, 610);
      else rectangle(300, 550, 500, 600);
      setvisualpage(p);
      delay(100);
   }
}

void draw_aboutme(){ // ��������� ���� �� ������
   int p = 0;
   while(!(mousex() > 300 && mousex() < 500 && mousey() > 550 && mousey() < 600 && mousebuttons() == 1))
   {
      setactivepage(p);
      p = 1-p;
      clearviewport();
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
      outtextxy(250, 100, "�� ������");
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
      outtextxy(230, 230, "������ ���� ��������");
      outtextxy(250, 255, "�������� ��������");
      outtextxy(260, 280, "�� ������ ��-111");
      outtextxy(350, 570, "�����");
      if(mousex() > 300 && mousex() < 500 && mousey() > 550 && mousey() < 600) rectangle(290, 540, 510, 610);
      else rectangle(300, 550, 500, 600);
      setvisualpage(p);
      delay(100);
   }
}

void draw_menu(){ // ��������� ����
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(250, 120, "��� � ���");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   if(button != 1){
      rectangle(300, 250, 500, 300);
   }
   outtextxy(350, 270, "������");
   if(button != 2){
      rectangle(300, 350, 500, 400);
   }
   outtextxy(345, 370, "�� ����");
   if(button != 3){
      rectangle(300, 450, 500, 500);
   }
   outtextxy(325, 470, "�� ������");
   if(button != 4){
      rectangle(300, 550, 500, 600);
   }
   outtextxy(360, 570, "�����");
   if(button != -1){
      rectangle(290, 140+button*100, 510, 210+button*100);
   }
}

void control_in_menu(){ // �������� ��������� ������ � ����
   int x = mousex();
   int y = mousey();
   if(x > 300 && x < 500 && y > 250 && y < 300) button = 1;
   else{
      if(x > 300 && x < 500 && y > 350 && y < 400) button = 2;
      else{
         if(x > 300 && x < 500 && y > 450 && y < 500) button = 3;
         else{
            if(x > 300 && x < 500 && y > 550 && y < 600) button = 4;
            else button = -1;
         }
      }
   }
   if(mousebuttons() == 1 && button == 1){
      game = 1;
   }
   if(mousebuttons() == 1 && button == 2){
      draw_aboutgame();
   }
   if(mousebuttons() == 1 && button == 3){
      draw_aboutme();
   }
   if(mousebuttons() == 1 && button == 4){
      ex = 1;
   }
   while(mousebuttons() == 1);
}

void back_game(){ // ��������� � ��������� ������ ������� � ����
   int x = mousex();
   int y = mousey();
   if(x > 500 && x < 700 && y > 500 && y < 550){
      rectangle(510, 490, 730, 560);
      if(mousebuttons() == 1){
         game = 0;
         creatmap();
      }
   }
   else rectangle(520, 500, 720, 550);
   outtextxy(570, 515, "�����");
}

int main(){
   int kol = 0, p = 0, blink = 0; // ���������� ��������� �����������, ����� �������� ����, �������� ���������� ����������
   int x, y; // ����� ��������� ���������� ��������
   srand(time(0));
   creatmap();
   
   initwindow(800, 700,"LOL",20,20);
   
   kol = 0;
   while(1){
      p = 1-p;
      setactivepage(p);
      if(game){
         if(fall()){
            chop();
            swap(kol, x, y);
         }
         draw_all(x, y, kol, blink);
         back_game();
      }
      else{
         control_in_menu();
         draw_menu();
      }
      if(ex == 1) return 0;
      setvisualpage(p);
      delay(100);
   }
   getch();
   closegraph();
}