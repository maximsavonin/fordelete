





#define hlab 12
#define wlab 12

int width = 800, height = 800; //размер экрана

typedef struct Cell
{
   int Left = 1, Bottom = 1;
   int flag = 0;
}Cell;

Cell map[hlab][wlab];

void shift(int x, int y)
{
   int em[4] = {0};
   int n = 0;
   for(int i = 0; i < 4; i++)
   {
      if(i%2) if(i/2)
         {
            if(y+1 < hlab-1 && 1-map[y+1][x].flag) 
            {
               em[n] = i;
               n++;
            }
         }
         else
         {
            if(y-1 > -1 && 1-map[y-1][x].flag) 
            {
               em[n] = i;
               n++;
            }
         }
      else if(i/2)
         {
            if(x+1 < wlab-1 && 1-map[y][x+1].flag) 
            {
               em[n] = i;
               n++;
            }
         }
         else
         {
            if(x-1 > -1 && 1-map[y][x-1].flag) 
            {
               em[n] = i;
               n++;
            }
         }
   }
   
   if(n == 0) return;
   
   int r = em[rand()%n];
   if(r%2) if(r/2)
      {
         map[y+1][x].flag = 1;
         map[y+1][x].Bottom = 0;
         shift(x, y+1);
      }
      else
      {
         map[y-1][x].flag = 1;
         map[y][x].Bottom = 0;
         shift(x, y-1);
      }
   else if(r/2)
      {
         map[y][x+1].flag = 1;
         map[y][x+1].Left = 0;
         shift(x+1, y);
      }
      else
      {
         map[y][x-1].flag = 1;
         map[y][x].Left = 0;
         shift(x-1, y);
      }
}

int main()
{
   initwindow( width, height,"Labirint",10,20);
   int p = 0;
   
   for(int i = 0; i < hlab; i++)
   {
      for(int k = 0; k < wlab; k++)
      {
         if(i+1 == hlab) map[i][k].Left = 0;
         if(k+1 == wlab) map[i][k].Bottom = 0;
      }
   }
   
   _abracadabra_cast(Cell[0][0]);