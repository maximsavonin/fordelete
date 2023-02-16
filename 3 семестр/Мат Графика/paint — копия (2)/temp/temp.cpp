




using namespace std;

struct Point
{
   int x, y;
};

// line ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


lineB::lineB(int x, int y, int x0, int y0)
{
   x1 = x;
   y1 = y;
   x2 = x0;
   y2 = y0;
   color = WHITE;
   width = 1;
}

lineB::lineB(int x, int y, int x0, int y0, int color0)
{
   x1 = x;
   y1 = y;
   x2 = x0;
   y2 = y0;
   color = color0;
   width = 1;
}

lineB::lineB(int x, int y, int x0, int y0, int color0, int width0)
{
   x1 = x;
   y1 = y;
   x2 = x0;
   y2 = y0;
   color = color0;
   width = width0;
}

void lineB::setColor(int color0)
{
   color = color0;
}

void lineB::setStart(int x, int y)
{
   x1 = x;
   y1 = y;
}

void lineB::setEnd(int x, int y)
{
   x2 = x;
   y2 = y;
}

void lineB::setWidth(int w)
{
   width = w;
}

void lineB::draw()
{
   cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << width << endl;
   int dx = abs(x2-x1);
   int dy = abs(y2-y1);
   int err = 0;
   if(dy < dx)
   {
      if(x1 > x2)
      {
         int a = x1;
         x1 = x2;
         x2 = a;
         a = y1;
         y1 = y2;
         y2 = a;
      }
      int d = dy == 0 ? 0 : (y2-y1)/dy;
      int y = y1;
      for(int x = x1; x <= x2; x++)
      {
         for(int i = 0; i < width; i++)
         {
            int y0;
            y0 = (i+1)/2*pow(-1, i);
            putpixel(x, y+y0, color);
         }
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
      if(y1 > y2)
      {
         int a = x1;
         x1 = x2;
         x2 = a;
         a = y1;
         y1 = y2;
         y2 = a;
      }
      int d = dx == 0 ? 0 : (x2-x1)/dx;
      int x = x1;
      for(int y = y1; y <= y2; y++)
      {
         for(int i = 0; i < width; i++)
         {
            int x0;
            x0 = (i+1)/2*pow(-1, i);
            putpixel(x+x0, y, color);
         }
         err = err+dx;
         if(err >= dy)
         {
            x += d;
            err -= dy;
         }
      }
   }
}

// star ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void star::creatStar()
{
   int x0, y0;
   int m = (n-1)/2;
   m = m<2 ? 2 : m;
   x0 = x+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*cos(fi));
   y0 = y+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*sin(fi));
   for(int i = 1; i < n*2+1; i++)
   {
      int y1, x1;
      if(i%2)
      {
         x1 = x+int(r*cos(i*3.14*1/n+fi));
         y1 = y+int(r*sin(i*3.14*1/n+fi));
      }
      else
      {
         x1 = x+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*cos(i*3.14*1/n+fi));
         y1 = y+int(r*(cos(3.14/n*m)/cos(3.14/n*(m-1)))*sin(i*3.14*1/n+fi));
      }
      lines[i-1].setWidth(1);
      lines[i-1].setStart(x0, y0);
      lines[i-1].setEnd(x1, y1);
      x0 = x1;
      y0 = y1;
   }
   lineColor();
}

void star::lineColor()
{
   for(int i = 0; i < n*2; i++)
   {
      lines[i].setColor(colorLine);
   }
}

star::star(int x0, int y0, int r0, int n0)
{
   x = x0;
   y = y0;
   r = r0;
   n = n0;
   fi = 0;
   colorLine = WHITE;
   colorFill = WHITE;
   creatStar();
}

star::star(int x0, int y0, int r0, int n0, float fi0)
{
   x = x0;
   y = y0;
   r = r0;
   n = n0;
   fi = fi0;
   colorLine = WHITE;
   colorFill = WHITE;
   creatStar();
}

star::star(int x0, int y0, int r0, int n0, float fi0, int colorLine0)
{
   x = x0;
   y = y0;
   r = r0;
   n = n0;
   fi = fi0;
   colorLine = colorLine0;
   colorFill = WHITE;
   creatStar();
}

star::star(int x0, int y0, int r0, int n0, float fi0, int colorLine0, int colorFill0)
{
   x = x0;
   y = y0;
   r = r0;
   n = n0;
   fi = fi0;
   colorLine = colorLine0;
   colorFill = colorFill0;
   creatStar();
}

void star::setRadius(int r0)
{
   r = r0;
   creatStar();
}

void star::setCenter(int x0, int y0)
{
   x = x0;
   y = y0; 
   creatStar();
}

void star::setNumCorners(int n0)
{
   n = n0;
   creatStar();
}

void star::setColorLine(int color0)
{
   colorLine = color0;
}

void star::setColorFill(int color0)
{
   colorFill = color0;
}

void star::setCorners(int fi0)
{
   fi = fi0;
   creatStar();
}

void star::draw()
{
   for(int i = 0; i < n*2; i++)
   {
      lines[i].draw();
   }
}

void star::fill()
{
   setfillstyle(SOLID_FILL, colorFill);
   fillIn(x, y, colorFill, getpixel(x, y));
}

// circle  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

circl::circl(int x0, int y0, int r0)
{
   x = x0;
   y = y0;
   r = r0;
   colorLine = WHITE;
   colorFill = WHITE;
}

circl::circl(int x0, int y0, int r0, int colorLine0)
{
   x = x0;
   y = y0;
   r = r0;
   colorLine = colorLine0;
   colorFill = WHITE;
}

circl::circl(int x0, int y0, int r0, int colorLine0, int colorFill0)
{
   x = x0;
   y = y0;
   r = r0;
   colorLine = colorLine0;
   colorFill = colorFill0;
}

void circl::setCenter(int x0, int y0)
{
   x = x0;
   y = y0;
}

void circl::setRadius(int r0)
{
   r = r0;
}

void circl::setColorLine(int color0)
{
   colorLine = color0;
}

void circl::setColorFill(int color0)
{
   colorFill = color0;
}

void circl::draw()
{
   int thickness = 1;
   for(int i = 1; i < thickness+1; i++)
   {
      int x1 = 0;
      int y1 = r+i/2*pow(-1, i-1);
      int delta = 1-2*(r+i/2*pow(-1, i-1));
      int err = 0;
      while(y1 >= x1)
      {
         putpixel(x+x1, y+y1, colorLine);
         putpixel(x+x1, y-y1, colorLine);
         putpixel(x-x1, y+y1, colorLine);
         putpixel(x-x1, y-y1, colorLine);
         putpixel(x+y1, y+x1, colorLine);
         putpixel(x+y1, y-x1, colorLine);
         putpixel(x-y1, y+x1, colorLine);
         putpixel(x-y1, y-x1, colorLine);
         err = 2*(delta+y1)-1;
         if(delta < 0 && err <= 0)
         {
            delta += 2*++x1+1;
            continue;
         }
         if(delta > 0 && err > 0)
         {
            delta -= 2*--y1+1;
            continue;
         }
         delta += 2*(++x1- --y1);
      }
   }
}

void circl::fill()
{
   setfillstyle(SOLID_FILL, colorFill);
   fillIn(x, y, colorFill, getpixel(x, y));
}

//------------

void lineBez::pefog(int pef[100], int k, int n)
{
   if(n <= k) return;
   int a[100] = {0};
   for(int i = 0; i < k; i++) a[i] = pef[i];
   for(int i = 1; i < k+1; i++)
   {
      pef[i] = a[i-1]+a[i];
   }
   pefog(pef, k+1, n);
}

lineBez::lineBez(int color0)
{
   data = new Point[100];
   color = color0;
   width = 1;
}

lineBez::lineBez(int color0, int width0)
{
   data = new Point[100];
   color = color0;
   width = width0;
}

void lineBez::add(int x0, int y0)
{
   data = new Point[100];
   data[n].x = x0;
   data[n].y = y0;
   n++;
}

void lineBez::setColor(int color0)
{
   color = color0;
}

void lineBez::setWidth(int width0)
{
   width = width0;
}

void lineBez::draw()
{
   if(n>1)
   {
      int pef[100] = {0};
      pef[0] = 1;
      pef[1] = 1;
      pefog(pef, 2, n);
      Point b = {data[0].x, data[0].y};
      cout << data[0].x << ' ' << _abracadabra_cast(data[0]);