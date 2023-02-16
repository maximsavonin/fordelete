





void creatPoint(Point points[15], int left, int top, int width, int height)
{
   srand(time(0));
   for(int i = 0; i < 15; i++)
   {
      setfillstyle(SOLID_FILL, BLACK);
      setcolor(BLACK);
      fillellipse(points[i].x, points[i].y, 3, 3);
      
      points[i].x = rand()%(width-left)+left;
      points[i].y = rand()%(height-top)+top;
      
      setfillstyle(SOLID_FILL, WHITE);
      setcolor(WHITE);
      fillellipse(points[i].x, points[i].y, 3, 3);
   }
}

void treat(Point points[15])
{
   double l_max = 0, l;
   int twoPoint[2];
   for(int i = 0; i < 15; i++)
   {
      for(int k = i; k < 15; k++)
      {
         int x = points[i].x-points[k].x;
         int y = points[i].y-points[k].y;
         l = sqrt(x*x+y*y);
         if(l > l_max)
         {
            l_max = l;
            twoPoint[0] = i;
            twoPoint[1] = k;
         }
      }
   }
   line(points[twoPoint[0]].x, points[twoPoint[0]].y, points[twoPoint[1]].x, _abracadabra_cast(points[twoPoint[1]]);