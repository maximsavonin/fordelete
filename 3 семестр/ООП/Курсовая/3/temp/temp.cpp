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
   private:
      int x1, y1;
   public:
      Rect(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){}
      Rect(const Rect &a): Figure(a.x0, a.y0, a.color, a.thickness), x1(a.x1), y1(a.y1){}
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;}
      void draw();
};

class Circl: public Figure
{
   private:
      int r;

   public:
      Circl(int x, int y, int r, int color = WHITE, int thickness = 1): Figure(x, y, color, thickness), r(r){}
      Circl(const Circl &a): Figure(a.x0, a.y0, a.color, a.thickness), r(a.r){}
      void setRadius(int r){this->r = r;}
      void draw();
};

class Curve: public Figure
{
   private:
      int n;
      int **data;
      double step = 0.02;
      void pefog(int[100], int, int);
   
   public:
      Curve(): Figure(0, 0, WHITE, 1), data(new int*[0]), n(0) {}
      Curve(int data[][2], int n, int color = WHITE, int thickness = 1) : Figure(0, 0, color, thickness), data(new int* [0]), n(n)
      {
          for (int i = 0; i < n; i++)
          {
              this->data[i] = new int[2];
              this->data[i][0] = data[i][0];
              this->data[i][1] = data[i][1];
          }
      }
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
      Picture(int x, int y, string fileName): Figure(x, y), file(loadBMP(_abracadabra_cast(fileName);