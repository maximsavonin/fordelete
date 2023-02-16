#include "stdio.h"
#include "stdlib.h"
#include "random"
#include "ctime"

#include "graphics.h"

#define xmax 8
#define ymax 10
#define size 25

int score = 0;

void creatmap(int map[ymax][xmax]){
   for(int i = 0; i < ymax; i++){
      for(int k = 0; k < xmax; k++){
         map[i][k] = rand()%6+1; // рондомизация цветов на поле 0 - пустота, 1 - красный, 2 - синий,
      }                                       //                                                     3 - жёлтый, 4 - зелёный
   }
}

void draw_sqr(int x, int y, int c){
   char a[1];
   a[0] = c + '0';
   setfillstyle(1, c);
   rectangle(50+50*x, 50+50*y, 100+50*x, 100+50*y);
   bar(51+50*x, 51+50*y, 99+50*x, 99+50*y);
   //outtextxy(75+50*x, 75+50*y, a);
}

void draw_all(int map[ymax][xmax]){
   clearviewport();
   char text[6];
   sprintf(text, "%d", score);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
   outtextxy(700, 100, text);
   for(int y = 0; y < ymax; y++){
      for(int x = 0; x < xmax; x++){
         draw_sqr(x, y, map[y][x]);
      }
   }
}

void swap(int map[ymax][xmax], int &kol, int &x, int &y){
   if(mousebuttons() == 1){
      if(kol != 0 && kol != 1){
         kol = 0;
      }
      if(kol == 0){
         x = (mousex()-50)/50;
         y = (mousey()-50)/50;
         kol++;
      }
      else{
         if(abs(x-(mousex()-50)/50) + abs(y-(mousey()-50)/50) < 2){
            int a;
            a = map[y][x];
            map[y][x] = map[(mousey()-50)/50][(mousex()-50)/50];
            map[(mousey()-50)/50][(mousex()-50)/50] = a;
            kol = 0;
         }
      }
      while(mousebuttons() == 1);
      draw_all(map);
   }
}

void fall(int map[ymax][xmax]){
   int n = 1;
   while(n > 0){
      n = 0;
      for(int i = ymax-1; i >= 0 ; i--){
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
      if(n != 0){
         draw_all(map);
         delay(100);
      }
   }
}

void chop(int map[ymax][xmax]){
   int n = 0;
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
                  n++;
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
            n++;
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
                  n++;
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
            n++;
         }
      }
   }
   if(n != 0){
      fall(map);
   }
}

int main(){
   int kol = 0, x, y;
   int map[ymax][xmax];
   creatmap(map);
   
   srand(time(0));
   initwindow(800, 700,"LOL",20,20);
   draw_all(map);
   kol = 0;
   while(1){
      fall(map);
      chop(map);
      swap(map, kol, x, y);
   }
   getch();
   closegraph();
}