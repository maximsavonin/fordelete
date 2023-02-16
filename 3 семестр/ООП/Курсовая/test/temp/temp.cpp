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
      virtual void draw();
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
   public:
      FillRec(int x0, int y0, int x1, int y1, int fillColor, int color = WHITE, int thickness = 1): Rect(x0, y0, x1, y1, color, thickness), fillColor(fillColor){}
      FillRec(const FillRec &a): Rect(a.x0, a.y0, a.x1, a.y1, a.color, a.thickness), fillColor(a.fillColor){}
      void setFillColor(int fillColor){this->fillColor = fillColor;}
      void draw();
};

void Rect::draw()
{
   line(x0, y0, x1, y0);
   line(x1, y0, x1, y1);
   line(x0, y1, x1, y1);
   line(x0, y0, x0, y1);
}

void FillRec::draw()
{
   Rect::draw();
   setfillstyle(SOLID_FILL, fillColor);
   floodfill((x1-x0)/2+x0, (y1-y0)/2+y0, color);
}

int main()
{
   vector<int[2]> a;
   _abracadabra_cast(a);