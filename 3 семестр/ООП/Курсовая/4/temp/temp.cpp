#define _USE_MATH_DEFINES









using namespace std;

struct Point
{
   int x, y;
};

class Figure
{
   protected:
      int x0 ,y0; // базовая точка
      int color, thickness;
   public:
      Figure(int x0, int y0, int color = WHITE, int thickness = 1): x0(x0), y0(y0), color(color), thickness(thickness) {}
      void setCoord(int x0, int y0){this->x0 = x0; this->y0 = y0;}
      void setColor(int color){this->color = color;}
      void setThickness(int thickness){this->thickness = thickness;}
      virtual void draw(); // нарисовать
};

class Line: public Figure
{
   private:
      int x1, y1;
   
   public:
      Line(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){}
      Line(const Line &a): Figure(a.x0, a.y0, a.color, a.thickness), x1(a.x1), y1(a.y1){}
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;}
      void draw();
};

class Rect: public Figure
{
   protected:
      int x1, y1;
   public:
      Rect(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){}
      Rect(const Rect &a): Figure(a.x0, a.y0, a.color, a.thickness), x1(a.x1), y1(a.y1){}
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;}
      void draw();
};

class FillRec: public Rect
{
   private:
      int fillColor;
      void draw();
   public:
      FillRec(int x0, int y0, int x1, int y1, int fillColor, int color = WHITE, int thickness = 1): Rect(x0, y0, x1, y1, color, thickness), fillColor(fillColor){}
      FillRec(const FillRec &a): Rect(a.x0, a.y0, a.x1, a.y1, a.color, a.thickness), fillColor(a.fillColor){}
      void setFillColor(int fillColor){this->fillColor = fillColor;}
};

class Circl: public Figure
{
   protected:
      int r;

   public:
      Circl(int x, int y, int r, int color = WHITE, int thickness = 1): Figure(x, y, color, thickness), r(r){}
      Circl(const Circl &a): Figure(a.x0, a.y0, a.color, a.thickness), r(a.r){}
      void setRadius(int r){this->r = r;}
      void draw();
};

class FillCircl: public Circl
{
   private:
      int fillColor;
   public:
      FillCircl(int x, int y, int r, int fillColor, int color = WHITE, int thickness = 1): Circl(x, y, r, color, thickness), fillColor(fillColor){}
      FillCircl(const FillCircl &a): Circl(a.x0, a.y0, a.r, a.color, a.thickness), fillColor(a.fillColor){}
      void setFillColor(int fillColor){this->fillColor = fillColor;}
      void draw();
};

class Curve: public Figure
{
   private:
      vector<vector<int>> data;
      double step = 0.02;
      void pefog(int[100], int, int);
   
   public:
      Curve(): Figure(0, 0, WHITE, 1) {}
      Curve(int data[][2], int n, int color = WHITE, int thickness = 1) : Figure(0, 0, color, thickness)
      {
          for (int i = 0; i < n; i++)
          {
              this->data.push_back({0, 0});
              this->data[i][0] = data[i][0];
              this->data[i][1] = data[i][1];
          }
      }
      Curve(vector<vector<int>> data, int color = WHITE, int thickness = 1) : Figure(0, 0, color, thickness), data(data) {}
      Curve(const Curve&);
      ~Curve();
      void add(int, int);
      void setStep(double a){step = a;}
      void setPoints(int **, int);
      void getPoints(int **, int&);
      void draw();
};

class Picture: public Figure
{
   private:
      IMAGE *file;
   public:
      Picture(int x, int y, string fileName): Figure(x, y), file(loadBMP(fileName.c_str())){}
      void draw() {putimage(x0, y0, file, COPY_PUT);}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Line::draw()
{
   int dx = abs(x1-x0);
   int dy = abs(y1-y0);
   int err = 0;
   if(dy < dx)
   {
      if(x0 > x1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int d = dy == 0 ? 0 : (y1-y0)/dy;
      int y = y0;
      for(int x = x0; x <= x1; x++)
      {
         for(int i = 0; i < thickness; i++)
         {
            int yd;
            yd = (i+1)/2*pow(-1, i);
            putpixel(x, y+yd, color);
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
      if(y0 > y1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int d = dx == 0 ? 0 : (x1-x0)/dx;
      int x = x0;
      for(int y = y0; y <= y1; y++)
      {
         for(int i = 0; i < thickness; i++)
         {
            int xd;
            xd = (i+1)/2*pow(-1, i);
            putpixel(x+xd, y, color);
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
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rect::draw()
{
   Line a(x0, y0, x1, y0, color, thickness);
   a.draw();
   a.setCoord(x1, y0);
   a.setCoordEnd(x1, y1);
   a.draw();
   a.setCoord(x1, y1);
   a.setCoordEnd(x0, y1);
   a.draw();
   a.setCoord(x0, y0);
   a.setCoordEnd(x0, y1);
   a.draw();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void FillRec::draw()
{
   Rect::draw();
   setfillstyle(SOLID_FILL, fillColor);
   floodfill((x1-x0)/2+x0, (y1-y0)/2+y0, color);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Circl::draw()
{
   for(int i = 1; i < thickness+1; i++)
   {
      int x1 = 0;
      int y1 = r+i/2*pow(-1, i-1);
      int delta = 1-2*(r+i/2*pow(-1, i-1));
      int err = 0;
      while(y1 >= x1)
      {
         putpixel(x0+x1, y0+y1, color);
         putpixel(x0+x1, y0-y1, color);
         putpixel(x0-x1, y0+y1, color);
         putpixel(x0-x1, y0-y1, color);
         putpixel(x0+y1, y0+x1, color);
         putpixel(x0+y1, y0-x1, color);
         putpixel(x0-y1, y0+x1, color);
         putpixel(x0-y1, y0-x1, color);
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
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void FillCircl::draw()
{
   Circl::draw();
   setfillstyle(SOLID_FILL, fillColor);
   floodfill(x0, y0, color);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Curve::pefog(int pef[100], int k, int n)
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

Curve::Curve(const Curve &a): Figure(a.x0, a.y0, a.color, a.thickness), data(_abracadabra_cast(a);