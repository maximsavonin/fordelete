#include <stdio.h>
#include <math.h>
#include <random>
#include <ctime>

#include "graphics.h"

int points[100];
int player[2];
int num = 0, p = 0;

void arrow(int i, int a){
   int x1, x, y1, y;
   if(i % 20 > 9){
      x1 = 815-i%10*70;
      y1 = 665-i/10*70;
   }
   else{
      x1 = 185+i%10*70;
      y1 = 665-i/10*70;
   }
   if(a % 20 > 9){
      x = 815-a%10*70 - x1;
      y = 665-a/10*70 - y1;
   }
   else{
      x = 185+a%10*70 - x1;
      y = 665-a/10*70 - y1;
   }
   line(x1, y1, x1 + x, y1 + y);
   circle(x1+x, y1+y, 5);
   
}

void draw(){
   p = 1-p;
   setactivepage(p);
   int pol[8];
   clearviewport();
   for(int i = 0; i < 100; i++){
      char text[3];
      sprintf(text, "%d", i+1);
      if(text[0] == '0') text[0] = ' ';
      if(text[1] == '0' && text[0] == ' ') text[1] = ' ';
      if(i % 20 > 9){
         rectangle(780-i%10*70, 630-i/10*70, 850-i%10*70, 700-i/10*70);
         outtextxy(781-i%10*70, 631-i/10*70, text);
      }
      else{
         rectangle(150+i%10*70, 630-i/10*70, 220+i%10*70, 700-i/10*70);
         outtextxy(151+i%10*70, 631-i/10*70, text);
      }
      if(i != points[i]) arrow(i, points[i]);
   }
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
   outtextxy(30, 415, "Бросить кость");
   char text[1];
   sprintf(text, "%d", num);
   outtextxy(70, 350, text);
   
   setvisualpage(p);
   delay(100);
}

void rand_num(){
   if(abs(mousex()-75) <= 55 && abs(mousey()-425) <= 25 && mousebuttons() == 1){
      for(int pl = 0; pl < 2; pl++){
         for(int i = 0; i < 15; i++){
            num = rand()%6 + 1;
            draw();
         }
         bool bl = false;
         for(int i = 0; i < num; i++){
            if(bl){
               player[pl]--;
            }
            else{
               player[pl]++;
            }
            if(player[pl] > 99){
               bl = true;
               player[pl] = 98;
            }
            draw();
         }
         if(points[player[pl]] != player[pl]){
            player[pl] = points[player[pl]];
         }
         if(num == 6){
            pl--;
         }
         delay(700);
      }
   }
}

int main(){
   initwindow(851, 701, "Win", 50, 50);
   srand(time(0));
   
   player[0] = -1;
   player[1] = -1;
   for(int i = 0; i < 100; i++){
      points[i] = i;
   }
   points[0] = 37;
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
   
   while(1){
      draw();
      rand_num();
   }

   getch();
   closegraph();
}