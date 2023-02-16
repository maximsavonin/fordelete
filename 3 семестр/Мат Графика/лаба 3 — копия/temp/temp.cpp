





using namespace std;

int col[3][2] = {0};

struct Point
{
   int x, y;
   Point *next;
};

int t = 0, p = 0;

Point *addPoint(int x, int y, Point *one)
{
   if(one == NULL)
   {
      one = new Point;
      one->x = x;
      one->y = y;
      one->next = NULL;
      return one;
   }
   one->next = addPoint(x, y, one->next);
   return one;
}

void lineb(Point a, Point b)
{
   int dx = abs(b.x-a.x);
   int dy = abs(b.y-a.y);
   int err = 0;
   if(dy < dx)
   {
      if(a.x > b.x)
      {
         Point c = a;
         a = b;
         b = c;
      }
      int d = dy == 0 ? 0 : (b.y-a.y)/dy;
      int y = a.y;
      for(int x = a.x; x <= b.x; x++)
      {
         putpixel(x, y, WHITE);
         err = err+dy;
         if(err >= dx)
         {
            y += d;
            err -= dx;
         }
      }
   }
   else
   {
      if(a.y > b.y)
      {
         Point c = a;
         a = b;
         b = c;
      }
      int d = dx == 0 ? 0 : (b.x-a.x)/dx;
      int x = a.x;
      for(int y = a.y; y <= b.y; y++)
      {
         putpixel(x, y, WHITE);
         err = err+dx;
         if(err >= dy)
         {
            x += d;
            err -= dy;
         }
      }
   }
}

void linev(Point *a, Point *b)
{
   int dx = abs(b->x-a->x);
   int dy = abs(b->y-a->y);
   int err = 0;
   int derr = 100;
   if(dx != 0) derr = 100*(dy)/(dx);
   if(derr < 100)
   {
      if(a->x > b->x)
      {
         Point *c = a;
         a = b;
         b = c;
      }
      int y = a->y;
      int d = dy == 0 ? 0 : (b->y-a->y)/dy;
      for(int x = a->x; x <= b->x; x++)
      {
         int color = err*255/100;
         putpixel(x, y, COLOR((255-err)*col[0][0]/255, (255-err)*col[1][0]/255, (255-err)*col[2][0]/255));
         putpixel(x, y+1, COLOR(err*col[0][0]/255, err*col[1][0]/255, err*col[2][0]/255));
         err = err+derr;
         if(err >= 100)
         {
            y += d;
            err -= 100;
         }
      }
   }
   else
   {
      if(a->y > b->y)
      {
         Point *c = a;
         a = b;
         b = c;
      }
      derr = 10000/derr;
      int x = a->x;
      int d = dx == 0 ? 0 : (b->x-a->x)/dx;
      for(int y = a->y; y <= b->y; y++)
      {
         int color = err*255/100;
         putpixel(x, y, COLOR((255-err)*col[0][0]/255, (255-err)*col[1][0]/255, (255-err)*col[2][0]/255));
         putpixel(x+1, y, COLOR(err*col[0][0]/255, err*col[1][0]/255, err*col[2][0]/255));
         err = err+derr;
         if(err >= 100)
         {
            x += d;
            err -= 100;
         }
      }
   }
}

void drawpol(int x, int y, int n, int r)
{
   Point *one = NULL;
   
   for(int i = 0; i < n*2+1; i++)
   {
      int yp, xp;
      if(i%2)
      {
         xp = x+int(r*cos(i*3.14*1/n));
         yp = y+int(r*sin(i*3.14*1/n));
      }
      else
      {
         xp = x+int(r*cos(3.14/n*(n*2+1))/cos(3.14/n*n*2)*cos(i*3.14*1/n));
         yp = y+int(r*cos(3.14/n*(n*2+1))/cos(3.14/n*n*2)*sin(i*3.14*1/n));
      }
      one = addPoint(xp, yp, one);
   }
   
   Point *two = one->next;
   while(two != NULL)
   {
      cin << one->x << ' ' <<  _abracadabra_cast(*(one));