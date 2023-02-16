#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

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
   public:
      FillRec(int x0, int y0, int x1, int y1, int fillColor, int color = WHITE, int thickness = 1): Rect(x0, y0, x1, y1, color, thickness), fillColor(fillColor){}
      FillRec(const FillRec &a): Rect(a.x0, a.y0, a.x1, a.y1, a.color, a.thickness), fillColor(a.fillColor){}
      void setFillColor(int fillColor){this->fillColor = fillColor;}
      void draw();
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
      Curve(const Curve &a): Figure(a.x0, a.y0, a.color, a.thickness), data(a.data), step(a.step){}
      void add(int x, int y){data.push_back({x, y});}
      void setStep(double a){step = a;}
      void setPoints(vector<vector<int>>);
      vector<vector<int>> getPoints(){return data;}
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

void outcoord();
void drawAll(vector<Figure*> acts);

#endif