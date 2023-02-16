#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "graphics.h"

#include "program.h"

#define xmax 8 // размер карты по горизонтали
#define ymax 10// размер карты по вертикали
#define size 50 // размер квадратика

enum STAGE {
   MENU = 0,
   GAME = 1,
   ABOUT_GAME = 2,
   ABOUT_ME = 3,
   CLOSE = 4,
   MAX_BUTTONS
};

int score = 0; // счёт очков
int map[ymax][xmax]; // карта игры
int stage = MENU;
int p = 0; // номер холста

BUTTON buttons[MAX_BUTTONS];

void draw_sqr(int x, int y, int color) { // отрисовка квадратика
   setfillstyle(1, color);
   rectangle(size*(x+1), size*(y+1), size*(x+2), size*(y+2));
   bar(1+size*(x+1), 1+size*(y+1), size*(x+2)-1, size*(y+2)-1);
}

void draw_all() { //отрисовка карты и счёта
   p = 1-p;
   setactivepage(p);
   clearviewport();
   char text[6];
   sprintf(text, "%d", score);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
   outtextxy(600, 100, text);
   for(int i = 0; i < ymax; i++){
      for(int k = 0; k < xmax; k++){
         draw_sqr(k, i, map[i][k]);
      }
   }
   setvisualpage(p);
}

void swap(bool &selected, int &x, int &y) { // выбор квадратиков и меняем их местами
   if(mousex() < size || mousex() > (xmax + 1)*size || mousey() < size || mousey() > (ymax+1)*size) return;

   if(!selected) {
      x = (mousex()-size) / size;
      y = (mousey()-size) / size;
      selected = true;
   }
   else{
      int second_x = (mousex()-size) / size;
      int second_y = (mousey()-size) / size;
      if(abs(x - second_x) + abs(y - second_y) < 2){
         draw_sqr(second_x, second_y, map[y][x]);
         draw_sqr(x, y, map[second_y][second_x]);
         int a;
         a = map[y][x];
         map[y][x] = map[second_y][second_x];
         map[second_y][second_x] = a;
         selected = false;
      }
   }
}

bool fall() { // падение всех висящих кубиков
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

int check_sqrt(int x, int y, int kx, int ky) // векторная проверка и удаление 3 и более в ряд
{ // kx и ky коэфициенты для векторной проверки
   int n = 1;
   for(int k = 1; k+x*kx+y*ky < xmax*kx+ymax*ky; k++)
   {
      if(map[y][x] == map[y+k*ky][x+k*kx]) n++;
      else break;
   }
   
   return n;
}

int chop() { // удаление 3 и более в ряд и начесление очков
   int found = 0;
   for (int y = 0; y < ymax; y++)
   {
      for(int x = 0; x < xmax; x++) {
         int wn = check_sqrt(x, y, 1, 0);//количество удалённых вправо
         int hn = check_sqrt(x, y, 0, 1);//количество удалённых вверх
         if(wn > 2)
         {
            for(int i = 0; i < wn; i++)
            {
               map[y][x+i] = 0;
               score += 50;
               found = 1;
            }
         }
         if(hn > 2)
         {
            for(int i = 0; i < hn; i++)
            {
               map[y+i][x] = 0;
               score += 50;
               found = 1;
            }
         }
      }
   }
   
   return found;
}

bool blink_sqrt(int x, int y) { // моргание выбранной ячейки
   if (mousebuttons() == 1)
      return false;
   delay(100);
   draw_sqr(x, y, 0);
   
   if (mousebuttons() == 1)
      return false;
   delay(100);
   draw_sqr(x, y, map[y][x]);
   
   return true;
}

void game() { // запуск и работа игры
   int x = 0, y = 0;
   bool selected = false;
   stage = GAME;
   draw_all();
   BUTTON exit_button = create_button(510, 490, 220, 70, "Выход", MENU);
   
   delay(100);
   score = 0;
   
   while(true)
   {
      while(selected)
      {
         if (!blink_sqrt(x, y))
            break;
      }
      
      while(!fall()){
         draw_all();
         delay(300);
      }
      
      if (chop())
         continue;
      
      while(mousebuttons() != 1);
      if (mousex() > exit_button.x &&
         mousex() < exit_button.x + exit_button.width &&
         mousey() > exit_button.y &&
         mousey() < exit_button.y + exit_button.height)
         break;
      
      swap(selected, x, y);
      
      delay(100);
   }
   
   delay(100);
   menu();
}

void create_map() { // создание новой карты
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

BUTTON create_button(int x, int y, int width, int height, const char* text, int button_stage) {// обозначение кнопки
   rectangle(x, y, x+width, y+height);
   int text_width = textwidth(text);
   int text_height = textheight(text);
   outtextxy(x + (width - text_width) / 2, y + (height - text_height) / 2, text);
   return {x, y, width, height, text, button_stage};
}

void menu() { // отрисовка и обработка меню
   stage = MENU;
   p = 1-p;
   setactivepage(p);
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(250, 120, "Три в ряд");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   
   buttons[GAME] = create_button(300, 250, 200, 50, "Играть", GAME);
   buttons[ABOUT_GAME] = create_button(300, 350, 200, 50, "Правила", ABOUT_GAME);
   buttons[ABOUT_ME] = create_button(300, 450, 200, 50, "Об авторе", ABOUT_ME);
   buttons[CLOSE] = create_button(300, 550, 200, 50, "Выход", CLOSE);
   setvisualpage(p);
   
   while(stage == MENU)
   {
      while (mousebuttons() != 1);
      int x = mousex();
      int y = mousey();
      stage = control_in_menu(x, y);
      printf("%d", stage);
   }
   
   if (stage == GAME)
      game();
   
   if (stage == ABOUT_GAME)
      draw_aboutgame();
   
   if (stage == ABOUT_ME)
      draw_aboutme();
   
   if (stage == CLOSE)
      return;
}

void draw_aboutgame() { // отрисовка окна правила
   stage = ABOUT_GAME;
   int x = 300;
   int y = 550;
   int width = 200;
   int height = 50;
   p = 1-p;
   setactivepage(p);
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(280, 100, "Правила");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(140, 230, "Расположенные на поле фигуры,");
   outtextxy(120, 255, "можно соединять по три и боллее");
   outtextxy(140, 280, "в ряд, затем они уничтожаются.");
   outtextxy(200, 305, "После уничтожения фигур");
   outtextxy(250, 330, "начисляются очки.");
   create_button(x, y, width, height, "Назад", MENU);
   setvisualpage(p);
   while(!(mousex() > x && mousex() < y && mousey() > x+width && mousey() < y+height && mousebuttons() == 1));
   delay(100);
   menu();
}

void draw_aboutme() { // отрисовка окна об авторе
   stage = ABOUT_ME;
   int x = 300;
   int y = 550;
   int width = 200;
   int height = 50;
   p = 1-p;
   setactivepage(p);
   clearviewport();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
   outtextxy(250, 100, "Об авторе");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(230, 230, "Данная игра созданна");
   outtextxy(250, 255, "Шелудько Арсением");
   outtextxy(260, 280, "из группы ЕТ-111");
   create_button(300, 550, 200, 50, "Назад", MENU);
   setvisualpage(p);
   while(!(mousex() > x && mousex() < x+width && mousey() > y && mousey() < y+height && mousebuttons() == 1));
   delay(100);
   menu();
}

int control_in_menu(int x, int y) { // проверка выбранной кнопки в меню
   for (int i = 0; i < MAX_BUTTONS; i++)
   {
      if (x > buttons[i].x &&
          x < buttons[i].x + buttons[i].width &&
          y > buttons[i].y &&
          y < buttons[i].y + buttons[i].height)
      {
         return buttons[i].stage;
      }
   }
   
   return MENU;
}

int main() {
   srand(time(0));
   create_map();
   
   initwindow(800, 700, "Три в ряд", 20, 20);
   
   menu();
   
   while(stage != CLOSE);
   
   closegraph();
   return 0;
}