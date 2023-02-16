#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

#define CELL 80

typedef struct Player{ // игрок
   int rot = 0;
   int x, y;
} Player;

Player pl[2] = {{0, 0, 1}, {2, 1, 1}}; // игрок, компьютер

int map[4][4] = {{3, 1, 1, 0}, // игровое поле
                        {0, 2, 1, 0},
                        {0, 2, 1, 0},
                        {0, 2, 2, 3}};
                        
int p = 0; // лист который отображается игроку
int mous[3] = {0, 0, 1}; // что сейчас делаем
int netr[2][2] = {{0, 0}, {3, 3}}; // нейтральные фишки
int pos[4][3][3] = {{{1, 1, 0}, // все положения г образной фигуры
                              {0, 1, 0},
                              {0, 1, 0}},
                              
                              {{0, 0, 1},
                              {1, 1, 1},
                              {0, 0, 0}},
                              
                              {{1, 0, 0},
                              {1, 0, 0},
                              {1, 1, 0}},
                              
                              {{1, 1, 1},
                              {1, 0, 0},
                              {0, 0, 0}}};

void draw_game() // отрисовка игры
{
   p = 1-p;
   setactivepage(p);
   clearviewport();
   setlinestyle(SOLID_LINE, 1, 1);
   setcolor(BLACK);
   for(int i = 0; i < 4; i++) // отрисовка сетки игры
   {
      for(int k = 0; k < 4; k++)
      {
         switch(map[i][k])
         {
            case 1:
            {
               setfillstyle(SOLID_FILL, RED);
               break;
            }
            case 2:
            {
               setfillstyle(SOLID_FILL, BLUE);
               break;
            }
            case 3:
            {
               setfillstyle(SOLID_FILL, BLACK);
               break;
            }
            default:
            {
               setfillstyle(SOLID_FILL, WHITE);
               break;
            }
         }
         bar((1+k)*CELL, (1+i)*CELL, (2+k)*CELL, (2+i)*CELL);
         rectangle((1+k)*CELL, (1+i)*CELL, (2+k)*CELL, (2+i)*CELL);
      }
   }
   if(mousex() > CELL && mousex() < CELL+220 && mousey() > 6*CELL && mousey() < 6*CELL+70) setlinestyle(SOLID_LINE, 1, 3); //навели на кнопку
   else setlinestyle(SOLID_LINE, 1, 1);
   rectangle(CELL, 6*CELL, CELL+220, 6*CELL+70); // отрисовка кнопки
   settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(1, 2, 2, 3);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   outtextxy(CELL+110, 6*CELL+25, "Не двигать");
   outtextxy(CELL+110, 6*CELL+50, "нейтральную фишку");

   if(mousex() > 2*CELL+220 && mousex() < 3*CELL+220 && mousey() > 6*CELL && mousey() < 6*CELL+70) setlinestyle(SOLID_LINE, 1, 3); //навели на кнопку
   else setlinestyle(SOLID_LINE, 1, 1);
   rectangle(2*CELL+220, 6*CELL, 3*CELL+220, 6*CELL+70); // отрисовка кнопки
   settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(1, 2, 2, 3);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   outtextxy(2.5*CELL+220, 6*CELL+40, "Выход");
   setlinestyle(SOLID_LINE, 1, 1);
   int a;
   if(mous[0] < 2 && mous[0] != 0) a = mous[1]; 
   else a = pl[mous[2]-1].rot;
   for(int i = 0; i < 3; i++) // отрисовка положение нашей фишки в данный момент
   {
      for(int k = 0; k < 3; k++)
      {
         if(pos[a][i][k])
         {
            if(mous[2] == 1) setfillstyle(SOLID_FILL, RED);
            else setfillstyle(SOLID_FILL, BLUE);
            bar((6+k*0.4)*CELL, (1+i*0.4)*CELL, (6.4+k*0.4)*CELL, (1.4+i*0.4)*CELL);
            rectangle((6+k*0.4)*CELL, (1+i*0.4)*CELL, (6.4+k*0.4)*CELL, (1.4+i*0.4)*CELL);
         }
         else
         {
            setfillstyle(SOLID_FILL, WHITE);
         }
      }
   }
   
   setvisualpage(p);
   delay(50);
}

int chec(int x, int y, int player) // можем ли в данную точку поставить фигуру?
{
   if(pl[player-1].x == x && pl[player-1].y == y && pl[player-1].rot == mous[1]) return 1;
   int r = mous[1];
   for(int i = 0; i < 3; i++)
   {
      for(int k = 0; k < 3; k++)
      {
         if(pos[r][i][k] == 1)
         {
            if(y+i < 0 || y+i > 3 || x+k < 0 || x+k > 3) return 1;
            else if(map[y+i][x+k] != 0 && map[y+i][x+k] != player) return 1;
         }
      }
   }
   return 0;
}

void put_figure(int x, int y, int player) // ставим фигуру в выбранную точку
{
   for(int i = 0; i < 4; i++)
   {
      for(int k = 0; k < 4; k++)
      {
         if(map[i][k] == player) map[i][k] = 0;
      }
   }
   for(int i = 0; i < 3; i++)
   {
      for(int k = 0; k < 3; k++)
      {
         if(pos[mous[1]][i][k] == 1)
         {
            map[y+i][x+k] = player;
         }
      }
   }
   pl[player-1].x = x;
   pl[player-1].y = y;
   pl[player-1].rot = mous[1];
   return;
}

void can_player_put() // не проиграл ли игрок?
{
   for(int i = 0; i < 4; i++)
   {
      for(int k = 0; k < 4; k++)
      {
         for(int l = 0; l < 4; l++)
         {
            if(pl[mous[2]-1].y != i || pl[mous[2]-1].x != k || pl[mous[2]-1].rot != l)
            {
               mous[1] = l;
               if(1-chec(k, i, mous[2])) return;
            }
         }
      }
   }
   draw_game();
   setfillstyle(SOLID_FILL, WHITE);// игрок проиграл
   bar(150, 275, 450, 325);
   rectangle(150, 275, 450, 325); 
   settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(3, 4, 1, 1);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   char a[16] = {"Победа игрока "};
   a[14] = 1-mous[2]+2+'0';
   outtextxy(300, 310, a);
   while(1);
}

void control_game() // обработка игры
{
   if(mousebuttons() == 1)
   {
      int x = mousex()/CELL-1;
      int y = mousey()/CELL-1;
      if(x >= 0 && x < 4 && y >= 0 && y < 4)
      {
         switch(mous[0])
         {
            case 0:// берём фигуру
            {
               if(map[y][x] == mous[2]) 
               {
                  mous[0] = 1;
                  mous[1] = pl[mous[2]-1].rot;
               }
               break;
            }
            case 1://ставим фигуру
            {
               if(1-chec(x, y, mous[2]))
               {
                  put_figure(x, y, mous[2]);
                  mous[0] = 2;
               }
               break;
            }
            case 2: // берём нейтральную фишку
            {
               if(map[y][x] == 3)
               {
                  mous[0] = 3;
                  if(netr[0][0] == x && netr[0][1] == y) mous[1] = 0;
                  else mous[1] = 1;
               }
               break;
            }
            case 3: // ставим нейтральную фишку
            {
               if(map[y][x] == 0)
               {
                  map[netr[mous[1]][1]][netr[mous[1]][0]] = 0;
                  map[y][x] = 3;
                  netr[mous[1]][0] = x;
                  netr[mous[1]][1] = y;
                  mous[0] = 0;
                  mous[1] = pl[mous[2]-1].rot;
                  mous[2] = 1-mous[2]+2;
                  can_player_put();
               }
               break;
            }
         }
      }
      if(mousex() > CELL && mousex() < CELL+220 && mousey() > 6*CELL && mousey() < 6*CELL+70 && mous[0] > 1) 
      {
         mous[0] = 0;
         mous[2] = 1-mous[2]+2;
         can_player_put();
      }
      while(mousebuttons());
      return;
   }
   if(mousebuttons() == 2 && mous[0] == 1)// поварачиваем фигуру
   {
      mous[1] = (mous[1]+1)%4;
      while(mousebuttons());
   }

}

int main()
{
   initwindow(600, 600, "L",30,30);
   srand(time(0));
   setbkcolor(WHITE);
   while(1)
   {
      control_game();
      draw_game();
   }
}