#include "stdio.h"
#include "stdlib.h"
#include "random"
#include "ctime"

#include "graphics.h"

#define xmax 8 // размер карты по горизонтали
#define ymax 10// размер карты по вертикали
#define size 50 // размер квадратика

int score = 0, button = -1, game = 0; // переменные счёт, какая кнопка выбрана и в игре ли

void draw_sqr(int x, int y, int c){ // отрисовка квадратика
   char a[1];
   a[0] = c + '0';
   setfillstyle(1, c);
   rectangle(50+size*x, 50+size*y, 100+size*x, 100+size*y);
   bar(51+size*x, 51+size*y, 99+size*x, 99+size*y);
}

void draw_all(int map[ymax][xmax], int x, int y, int kol, int &bl){ //отрисовка карты и счёта
   clearviewport();
   char text[6];
   sprintf(text, "%d", score);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
   outtextxy(700, 100, text);
   bl = 1-bl;
   for(int i = 0; i < ymax; i++){
      for(int k = 0; k < xmax; k++){
         if(kol == 1 && x == k && y == i && bl == 1) draw_sqr(k, i, 0);
         else draw_sqr(k, i, map[i][k]);
      }
   }
}

void swap(int map[ymax][xmax], int &kol, int &x, int &y){ // выбор квадратиков и меняем их местами
   if(mousebuttons() == 1){
      if(kol != 0 && kol != 1){
         kol = 0;
      }
      if(mousex() < 50 || mousex() > 100+xmax*50 || mousey() < 50 || mousey() > 100+ymax*50) return;
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
   }
}

bool fall(int map[ymax][xmax]){ // падение всех висящих кубиков
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

void chop(int map[ymax][xmax]){ // удаление 3 и более в ряд
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

void creatmap(int map[ymax][xmax]){ // создание новой карты
   for(int i = 0; i < ymax; i++){
      for(int k = 0; k < xmax; k++){
         map[i][k] = rand()%6+1;
      }                                      
   }
   for(int i = 0; i < 150; i++){
      if(fall(map)) chop(map);
   }
   score = 0;
}

void draw_aboutgame(){ // отрисовка окна об игре
   int p = 0;
   while(!(mousex() > 300 && mousex() < 500 && mousey() > 550 && mousey() < 600 && mousebuttons() == 1))
   {
      setactivepage(p);
      p = 1-p;
      clearviewport();
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
      outtextxy(250, 100, "Об игре");
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
      outtextxy(210, 180, "Главный игровой мир");
      outtextxy(140, 205, "состоит из таблицы элементов,");
      outtextxy(80, 230, "задача игрока заключается в следующем,");
      outtextxy(110, 255, "манипулируя элементами из таблицы");
      outtextxy(215, 280, "нужно сделать так,");
      outtextxy(140, 305, "чтобы совпали заданные игрой");
      outtextxy(190, 330, "шаблонные комбинации,");
      outtextxy(120, 355, "после выполнения данного условия");
      outtextxy(130, 380, "собранные элементы исчезают,");
      outtextxy(50, 405, "тем самым добавляя вам внутриигровые очки");
      outtextxy(350, 570, "Назад");
      if(mousex() > 300 && mousex() < 500 && mousey() > 550 && mousey() < 600) rectangle(290, 540, 510, 610);
      else rectangle(300, 550, 500, 600);
      setvisualpage(p);
      delay(100);
   }
}

void draw_aboutme(){ // отрисовка окна об авторе
   int p = 0;
   while(!(mousex() > 300 && mousex() < 500 && mousey() > 550 && mousey() < 600 && mousebuttons() == 1))
   {
      setactivepage(p);
      p = 1-p;
      clearviewport();
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
      outtextxy(250, 100, "Об авторе");
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
      outtextxy(230, 230, "Данная игра созданна");
      outtextxy(250, 255, "Шелудько Арсением");
      outtextxy(260, 280, "из группы ЕТ-111");
      outtextxy(350, 570, "Назад");
      if(mousex() > 300 && mousex() < 500 && mousey() > 550 && mousey() < 600) rectangle(290, 540, 510, 610);
      else rectangle(300, 550, 500, 600);
      setvisualpage(p);
      delay(100);
   }
}

void draw_menu(){ // отрисовка меню
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(250, 120, "Три в ряд");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   if(button != 1){
      rectangle(300, 250, 500, 300);
   }
   outtextxy(350, 270, "Играть");
   if(button != 2){
      rectangle(300, 350, 500, 400);
   }
   outtextxy(345, 370, "Об игре");
   if(button != 3){
      rectangle(300, 450, 500, 500);
   }
   outtextxy(325, 470, "Об авторе");
   if(button != 4){
      rectangle(300, 550, 500, 600);
   }
   outtextxy(360, 570, "Выход");
   if(button != -1){
      rectangle(290, 140+button*100, 510, 210+button*100);
   }
}

void control_in_menu(){ // проверка выбранной кнопки в меню
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
      exit(0);
   }
   while(mousebuttons() == 1);
}

void back_game(int map[ymax][xmax]){ // отрисовка и обработка кнопки обратно в меню
   int x = mousex();
   int y = mousey();
   if(x > 500 && x < 700 && y > 500 && y < 550){
      rectangle(510, 490, 730, 560);
      if(mousebuttons() == 1){
         game = 0;
         creatmap(map);
      }
   }
   else rectangle(520, 500, 720, 550);
   outtextxy(570, 515, "Выход");
}

int main(){
   int kol = 0, x, y, p = 0, bl = 0; // количество выбранных квадратиков, положение его на карте, номер главного окна, моргание выбранного квадратика
   int map[ymax][xmax]; // карта игры
   srand(time(0));
   creatmap(map);
   
   initwindow(800, 700,"LOL",20,20);
   
   kol = 0;
   while(1){
      p = 1-p;
      setactivepage(p);
      if(game){
         if(fall(map)){
            chop(map);
            swap(map, kol, x, y);
         }
         draw_all(map, x, y, kol, bl);
         back_game(map);
      }
      else{
         control_in_menu();
         draw_menu();
      }
      setvisualpage(p);
      delay(100);
   }
   getch();
   closegraph();
}