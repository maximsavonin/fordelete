





#define CELL 40

typedef struct Snake{
   int x, y;
}Snake;

Snake all[225];
int n = 0;
int map[15][15] = {0};
int p = 0;

void drawgame()
{
   p = 1-p;
   setactivepage(p);
   clearviewport();
   
   setbkcolor(BLACK);
   setcolor(WHITE);
   for(int i = 0; i < 15; i++)
   {
      for(int k = 0; k < 15; k++)
      {
         rectangle(k*CELL, i*CELL, (k+1)*CELL, (i+1)*CELL);
         switch(map[i][k])
         {
            case 1:
            {
               setfillstyle(SOLID_FILL, GREEN);
               bar((k+0.1)*CELL, (i+0.1)*CELL, (k+0.9)*CELL, (i+0.9)*CELL);
               break;
            }
            case 2:
            {
               setfillstyle(SOLID_FILL, RED);
               bar((k+0.2)*CELL, (i+0.2)*CELL, (k+0.8)*CELL, (i+0.8)*CELL);
               break;
            }
         }
      }
   }
   
   setvisualpage(p);
}

void apple()
{
   while(1)
   {
      int x = rand()%15, y = rand()%15;
      if(map[y][x] == 0)
      {
         map[y][x] = 2;
         break;
      }
   }
}

void start()
{
   for(int i = 0; i < 15; i++)
   {
      for(int k = 0; k < 15; k++)
      {
         map[i][k] = 0;
      }
   }
   
   all[0].x = 3;
   all[0].y = 1;
   all[1].x = 2;
   all[1].y = 1;
   all[2].x = 1;
   all[2].y = 1;
   n = 3;
   
   map[1][1] = 1;
   map[1][2] = 1;
   map[1][3] = 1;
   
   apple();
}

void movesnake(int x, int y)
{
   if(map[all[0].y+y][all[0].x+x] == 2)
   {
      n++;
   }
   else if(map[all[0].y+y][all[0].x+x] == 1 && (all[0].x+x == _abracadabra_cast(all[0]);