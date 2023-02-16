





Square sq[2];

void genPoint(int left, int top, int width, int height)
{
   srand(time(0));
   
   setfillstyle(SOLID_FILL, BLACK);
   bar(left, top, width, height);
   
   setcolor(WHITE);
   for(int i = 0; i < 2; i++)
   {
      sq[i].x1 = rand()%(width-left-10)+5;
      sq[i].x2 = rand()%(width-left-10)+5;
      sq[i].y1 = rand()%(height-top-10)+5;
      sq[i].y2 = rand()%(height-top-10)+5;
      if(sq[i].x1 > sq[i].x2)
      {
         int x = sq[i].x1;
         sq[i].x1 = sq[i].x2;
         sq[i].x2 = x;
      }
      if(sq[i].y1 > sq[i].y2)
      {
         int y = sq[i].y1;
         sq[i].y1 = sq[i].y2;
         sq[i].y2 = y;
      }
      rectangle(sq[i].x1, sq[i].y1, sq[i].x2, sq[i].y2);
   }
}

void recPoint(int left, int top, int width, int height)
{
   int x1 = fmax(sq[0].x1, sq[1].x1);
   int x2 = fmin(sq[0].x2, _abracadabra_cast(sq[1]);