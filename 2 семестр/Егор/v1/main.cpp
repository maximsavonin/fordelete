#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

#define CELL 80

typedef struct Player{ // игрок
   int rot = 0;
   int x, y;
} Player;

Player pl[2] = {{0, 0, 1}, {2, 1, 1}};

int map[4][4] = {{3, 1, 1, 0},
                        {0, 2, 1, 0},
                        {0, 2, 1, 0},
                        {0, 2, 2, 3}};
                        
int p = 0;
int mous[2] = {0, 0};
int netr[2][2] = {{0, 0}, {3, 3}};
int pos[4][3][3] = {{{1, 1, 0},
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

void draw_game()
{
   p = 1-p;
   setactivepage(p);
   clearviewport();
   setlinestyle(SOLID_LINE, 1, 1);
   setcolor(BLACK);
   for(int i = 0; i < 4; i++)
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
   if(mousex() > CELL && mousex() < CELL+220 && mousey() > 6*CELL && mousey() < 6*CELL+70) setlinestyle(SOLID_LINE, 1, 3);
   else setlinestyle(SOLID_LINE, 1, 1);
   rectangle(CELL, 6*CELL, CELL+220, 6*CELL+70);
   settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(1, 2, 2, 3);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   outtextxy(CELL+110, 6*CELL+25, "Не двигать");
   outtextxy(CELL+110, 6*CELL+50, "нейтральную фишку");
   
   setvisualpage(p);
   delay(50);
}

int put_figure(int x, int y, int player)
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
         if(pos[r][i][k] == 1)
         {
            map[y+i][x+k] = player;
         }
      }
   }
   pl[player-1].x = x;
   pl[player-1].y = y;
   pl[player-1].rot = mous[1];
   return 0;
}

void control_game()
{
   if(mous[0] == -1)// ходит компьютер
   {
      delay(500);
      int mind[2] = {rand()%4, rand()%4};
      for(int i = 0; i < 4; i++)
      {
         for(int k = 0; k < 4; k++)
         {
            for(int l = 0; l < 4; l++)
            {
               int x = (k+mind[0]) % 4;
               int y = (i+mind[1]) % 4;
               if(pl[1].y != y || pl[1].x != x || pl[1].rot != l)
               {
                  mous[1] = l;
                  if(1-put_figure(x, y, 2)) 
                  {
                     mous[0] = 0;
                     int choice = rand()%2;
                     for(int j = 0; j < 2; j++)
                     {
                        int x = rand() % 4;
                        int y = rand() % 4;
                        if(map[y][x] == 0)
                        {
                           map[netr[choice][1]][netr[choice][0]] = 0;
                           map[y][x] = 3;
                           netr[choice][1] = y;
                           netr[choice][0] = x;
                           break;
                        }
                     }
                     return;
                  }
               }
            }
         }
      }
      setfillstyle(SOLID_FILL, WHITE);// победа игрока
      bar(150, 275, 450, 325);
      rectangle(150, 275, 450, 325); 
      settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
      setusercharsize(1, 1, 4, 3);
      settextjustify(CENTER_TEXT,CENTER_TEXT);
      outtextxy(300, 310, "Победа игрока");
      while(1);
   }
   if(mousebuttons() == 1)
   {
      int x = mousex()/CELL-1;
      int y = mousey()/CELL-1;
      printf("%d %d\n", x, y);
      if(x >= 0 && x < 4 && y >= 0 && y < 4)
      {
         switch(mous[0])
         {
            case 0:
            {
               if(map[y][x] == 1) 
               {
                  mous[0] = 1;
                  mous[1] = pl[0].rot;
               }
               break;
            }
            case 1:
            {
               if(1-put_figure(x, y, 1))
               {
                  mous[0] = 2;
               }
               break;
            }
            case 2:
            {
               if(map[y][x] == 3)
               {
                  mous[0] = 3;
                  if(netr[0][0] == x && netr[0][1] == y) mous[1] = 0;
                  else mous[1] = 1;
               }
               break;
            }
            case 3:
            {
               if(map[y][x] == 0)
               {
                  mous[0] = -1;
                  map[netr[mous[1]][1]][netr[mous[1]][0]] = 0;
                  map[y][x] = 3;
                  netr[mous[1]][0] = x;
                  netr[mous[1]][1] = y;
               }
               break;
            }
         }
      }
      if(mousex() > CELL && mousex() < CELL+220 && mousey() > 6*CELL && mousey() < 6*CELL+70 && mous[0] > 1) mous[0] = -1;
      while(mousebuttons());
      return;
   }
   if(mousebuttons() == 2 && mous[0] == 1)
   {
      mous[1] = (mous[1]+1)%4;
      printf("%d\n", mous[1]);
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