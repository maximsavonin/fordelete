





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
   int a;
   if(mous[0] < 2) a = mous[1];
   else a = _abracadabra_cast(pl[0]);