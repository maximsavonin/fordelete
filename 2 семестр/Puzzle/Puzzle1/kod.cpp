#include <stdio.h>
#include <time.h>

#include "graphics.h"

typedef struct Button { // Кнопка
   int x, y, x1, y1,// координаты
       w, h, w1, h1;// размеры
   IMAGE *bmp;  // картинка
} Button;

typedef struct Puzzle {
   int x, y, index, now;
   IMAGE *img;
} Puzzle;

// глобальные константы
#define NMENU 3
#define MENU_W 200
#define MENU_H 56
#define IMG_COUNT 5

enum _special_keys { KEY_SPECIAL=0x100, MOUSE_CLICK=0x200};

//  глобальные переменные
Button mn[NMENU]; // кнопки меню
Button img[IMG_COUNT]; // кнопки с картинками
IMAGE *Picture;
IMAGE *fon; // фон для меню
int inmouse = 0; //какая картинка на мышке
Puzzle all[16];

// Заголовки функций
int menu();
void init();
void menu2();
void init2();
void draw_menu();
void get_variant();
int get_image();
void draw_variant();
void about_program();
void start_game();
void GameInit();
void DrawMap();
void treatment();

int main() {
   srand(time(0));
   int st;
   init();
   do {
      st = menu();
      switch (st) {
      case 1:
         menu2();
         break;
      case 2:
         about_program();
         break;
      }
   } while (st != 3);
   closegraph();
   return 0;
}
//----------------------------------------------------------------
Button new_button(int x, int y, const char *t) {
   Button b;
   b.x=x;
   b.y=y;
   b.w=MENU_W;
   b.h=MENU_H;
   b.w1 = 285,
   b.h1 = 178,
   b.bmp=loadBMP(t);
   return b;
}
//Кнопки главного меню
void init() {
   initwindow(1200, 600, "Puzzle");
   fon=loadBMP("main.jpg");
   int top = 150;
   int left = (getmaxx() - MENU_W)/2;
   int skip = MENU_H + 50;
   mn[0]=new_button(left,top,"Start game.bmp");
   top+=skip;
   mn[1]=new_button(left,top,"Program.bmp");
   top+=skip;
   mn[2]=new_button(left,top,"Exit.bmp");
}
//Отрисовка кнопок главного меню
void draw_menu() {
   clearviewport();
   putimage(0,0,fon,COPY_PUT);
   for (int i=0; i < NMENU; i++)
   {
      // рисуем кнопку
      putimage(mn[i].x, mn[i].y, mn[i].bmp, COPY_PUT);
   }
}
//------------------------------------------------------
int wait_click() {  
   while (1) 
   {
      if (kbhit()) {
         int k=getch();
         if (k==0) k=getch()+KEY_SPECIAL;
         return k;
      }
      int b=mousebuttons();
      if (b)
      {
         while (mousebuttons()); // ждем отпускания кнопки
         return MOUSE_CLICK+b;
      }
   }
}
// Главное меню
int menu() {
   while (1) {
      draw_menu();
      int k=wait_click();
      if (k&MOUSE_CLICK)
      {
         int x = mousex();
         int y = mousey();
         for (int i=0; i < NMENU; i++)
            if (x >= mn[i].x && y>=mn[i].y
                  && x <= mn[i].x+mn[i].w && y<=mn[i].y+mn[i].h)
               return i+1;
      }
      if (k==KEY_ESC) return NMENU;
   }
}
//Кнопки с картинками
void init2() {
   fon=loadBMP("main.jpg");
   int top1 = 100;
   int top2 = 370;
   int left1 = 183;
   int left2 = 733;
   img[0]=new_button(left1,top1,"11.bmp");
   img[1]=new_button(left2,top1,"22.bmp");
   img[2]=new_button(left1,top2,"33.bmp");
   img[3]=new_button(left2,top2,"44.bmp");
   img[4]=new_button(60,30,"Back.bmp");
}
//Отрисовка кнопок с картинками
void draw_variant() {
   clearviewport();
   putimage(0,0,fon,COPY_PUT);
   for (int i=0; i < IMG_COUNT; i++)
   {
      // рисуем кнопку
      putimage(img[i].x, img[i].y, img[i].bmp, COPY_PUT);
   }
}
//-----------------------------------------------------------------
int get_image() {
   while (1) {
      draw_variant();
      int k=wait_click();
      if (k & MOUSE_CLICK)
      {
         int x = mousex();
         int y = mousey();
         for (int i=0; i < IMG_COUNT; i++)
            if (x >= img[i].x && y >= img[i].y
                  && x <= img[i].x+img[i].w1 && y <= img[i].y+img[i].h1)
               return i+1;
      }
      if (k==KEY_ESC) return IMG_COUNT;
   }
}
//Выбор картинки
void menu2() {
   clearviewport();
   init2();
   int choose;
   do {
      choose = get_image();
      switch (choose) {
      case 1:
         clearviewport();
         Picture = loadBMP("111.jpg");
         putimage(0, 100, Picture, COPY_PUT);
         start_game();
         break;
      case 2:
         clearviewport();
         Picture = loadBMP("222.jpg");
         putimage(0, 100, Picture, COPY_PUT);
         start_game();
         break;
      case 3:
         clearviewport();
         Picture = loadBMP("333.jpg");
         putimage(0, 100, Picture, COPY_PUT);
         start_game();
         break;
      case 4:
         clearviewport();
         Picture = loadBMP("444.jpg");
         putimage(0, 100, Picture, COPY_PUT);
         start_game();
         break;
      }
   } while (choose != 5);
}
//О программе
void about_program() {
   clearviewport();
   putimage(0,0,fon,COPY_PUT);
   IMAGE *p=loadBMP("About program.jpg");
   putimage(382, 202, p, COPY_PUT);
   wait_click();
   freeimage(p);
}
//Разделение картинки и перемешивание
void GameInit() {
   int N = 4;
   for (int y = 0; y < N; y++)
   {
      for (int x = 0; x < N; x++)
      {
         int i = y*4+x;
         all[i].img = createimage(127, 100);
         getimage(x *124, 100 + y * 100, (x + 1) * 124, 100 + (y + 1) * 100, all[i].img);
         all[i].index = i;
         all[i].now = -1;
      }
   }
   for(int i = 0; i < 20; i++)
   {
      int j = rand()%16, k = rand()%16;
      Puzzle swap;
      swap = all[j];
      all[j] = all[k];
      all[k] = swap;
   }
   for (int y = 0; y < N; y++)
   {
      for (int x = 0; x < N; x++)
      {
         int i = y*4+x;
         all[i].x = 600+x*144;
         all[i].y = 60+y*120;
      }
   }
}
//отрисовка игры
void DrawMap() {
   setbkcolor(WHITE);
   clearviewport();
   for(int i = 0; i < 16; i++)
   {
      if(inmouse == i) continue;
      putimage(all[i].x, all[i].y, all[i].img, COPY_PUT);
   }
   if(inmouse != -1) putimage(all[inmouse].x, all[inmouse].y, all[inmouse].img, COPY_PUT);
   setcolor(BLACK);
   rectangle(49, 99, 547, 501);
}
//обработка игры
void treatment() {
   int x = mousex();
   int y = mousey();
   if(mousebuttons())
   {
      if(inmouse != -1)//перемещаем фрагмент за мышью
      {
         all[inmouse].x = x-62;
         all[inmouse].y = y-50;
      }
      else//берём фрагмент
      {
         for(int i = 0; i < 16; i++)
         {
            if(x >= all[i].x && x <= all[i].x + 124 && y >= all[i].y && y <= all[i].y+100)
            {
               
               all[i].x = x-62;
               all[i].y = y-50;
               inmouse = i;
               break;
            }
         }
      }
   }
   else 
   {
      if(inmouse == -1) return;
      for(int i = 0; i < 4; i++)
      {
         for(int k = 0; k < 4; k++)
         {
            if(x >= 50+k*124 && x <= 50+(k+1)*124 && y >= 100+i*100 && y <= 100+(i+1)*100) //поиск ячейки на которую навелись
            {
               for(int j = 0; j < 16; j++)
               {
                  if(all[j].now == i*4+k) // в ячейке есть фрагмент
                  {
                     all[inmouse].x = 600+(inmouse%4)*144;
                     all[inmouse].y = 60+(inmouse/4)*120;
                     all[inmouse].now = -1;
                     inmouse = -1;
                     return;
                  }
               }
               all[inmouse].x = 50+k*124; // помещаем фрагмент в ячейку
               all[inmouse].y = 100+i*100;
               all[inmouse].now = i*4+k;
               inmouse = -1;
               return;
            }
         }
      }
      all[inmouse].now = -1;
      inmouse = -1;
   }
}
//запуск игры
void start_game() {
   GameInit();
   int p = 0;
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      treatment();
      DrawMap();
      setvisualpage(p);
      int kor = 0;
      for(int k = 0; k < 16; k++)
      {
         if(all[k].index == all[k].now)
         {
            kor++;
         }
      }
      if(kor == 16) 
      {
         //все фрагменты на своих местах, победа
         delay(500);
         return;
      }
   }
   wait_click();
}
















