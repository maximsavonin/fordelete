





void lineB(int x0, int y0, int x1, int y1)
{
   int color = getcolor();
   int deltax = abs(x1-x0);
   int deltay = abs(y1-y0);
   double error = 0;
   double deltaerr = 0;
   if(deltay > deltax)
   {
      if(deltay != 0) deltaerr = 1.0*deltax/deltay;
      if(y0 > y1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int x = x0;
      int dir = x1-x0;
      if(dir > 0)
      {
         dir = 1;
      }
      else
      {
         dir = -1;
      }
      for(int y = y0; y <= y1; y++)
      {
         putpixel(x, y, color);
         error += deltaerr;
         if(error >= 1)
         {
            x += dir;
            error--;
         }
      }
   }
   else
   {
      if(deltax != 0) deltaerr = 1.0*deltay/deltax;
      if(x0 > x1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int y = y0;
      int dir = y1-y0;
      if(dir > 0)
      {
         dir = 1;
      }
      else
      {
         dir = -1;
      }
      for(int x = x0; x <= x1; x++)
      {
         putpixel(x, y, color);
         error += deltaerr;
         if(error >= 1)
         {
            y += dir;
            error--;
         }
      }
   }
}

void star(int x, int y, int n, int r)
{
   Point *points;
   points = new Point[2*n];
   for(int i = 0; i < n*2; i++)
   {
      Point *point;
      if(i%2)
      {
         _abracadabra_cast(point);