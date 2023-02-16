






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
   
   for(int i = 0; i < 4; i++)
   {
      for(int k = 0; k < 4; k++)
      {
         setcolor(BLACK);
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
   
   setvisualpage(p);
   delay(50);
}

int put_figure(int x, int y, int player)
{
   if(pl[player-1].x == x && pl[player-1].y == y && pl[player-1].rot == mous[1]) return 1
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
   if(mous[0] == -1)
   {
      delay(500);
      for(int i = 0; i < 4; i++)
      {
         for(int k = 0; k < 4; k++)
         {
            for(int l = 0; l < 4; l++)
            {
               if(pl[1].y != i || pl[1].x != k || pl[1].rot != l)
               {
                  mous[1] = l;
                  if(1-put_figure(k, i, 2)) 
                  {
                     mous[0] = 0;
                     return;
                  }
               }
            }
         }
      }
   }
   if(mousebuttons() == 1)
   {
      int x = mousex()/CELL-1;
      int y = mousey()/CELL-1;
      printf("%d %d\n", x, y);
      if(x >= 0 && x < 4 && y >= 0 && y < 4)
      {
         if(mous[0] != 1)
         {         
            if(map[y][x] == 1) 
            {
               mous[0] = 1;
               mous[1] = _abracadabra_cast(pl[0]);