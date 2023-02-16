#ifndef DRAW_H
#define DRAW_H

#include <vector>

using namespace std;

struct Point
{
   int x, y;
};

class Figure // Абстрактный класс Figure
{
   protected:
      int x0 ,y0; // основная точка фигуры
      int color, thickness; // цвет и толщина линии
   public:
      Figure(int x0, int y0, int color = WHITE, int thickness = 1): x0(x0), y0(y0), color(color), thickness(thickness) {} // конструктор
      void setCoord(int x0, int y0){this->x0 = x0; this->y0 = y0;} //сетер координат
      void setColor(int color){this->color = color;} //сетер цвета лини
      void setThickness(int thickness){this->thickness = thickness;} // сетер толщины линии
      virtual void draw(); // виртуальный метод отрисовки
};

class Line: public Figure // Класс Линии
{
   private:
      int x1, y1; // координаты конечной точки линии
   
   public:
      Line(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){} // конструктор
      Line(const Line &a): Figure(a.x0, a.y0, a.color, a.thickness), x1(a.x1), y1(a.y1){} // конструктор копии
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;} // сетер конечной точки линии
      void draw(); //отрисовка линии
};

class Rect: public Figure // класс Прямоугольник
{
   protected:
      int x1, y1; // вторая точка прямоугольника
   public:
      Rect(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){} // Конструктор
      Rect(const Rect &a): Figure(a.x0, a.y0, a.color, a.thickness), x1(a.x1), y1(a.y1){}// конструктор копии
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;} // сетер второй точки прямоугольника
      void draw(); // отрисовка прямоугольника
};

class FillRec: public Rect // Класс закрашенный прямоугольник
{
   private:
      int fillColor; // цвет закраски
   public:
      FillRec(int x0, int y0, int x1, int y1, int fillColor, int color = WHITE, int thickness = 1): Rect(x0, y0, x1, y1, color, thickness), fillColor(fillColor){} // конструктор
      FillRec(const FillRec &a): Rect(a.x0, a.y0, a.x1, a.y1, a.color, a.thickness), fillColor(a.fillColor){} //конструктор копии
      void setFillColor(int fillColor){this->fillColor = fillColor;} // сетер цвет закраски
      void draw(); // отрисовка
};

class Circl: public Figure // Класс окружность
{
   protected:
      int r; // радиус окружности

   public:
      Circl(int x, int y, int r, int color = WHITE, int thickness = 1): Figure(x, y, color, thickness), r(r){} // конструктор
      Circl(const Circl &a): Figure(a.x0, a.y0, a.color, a.thickness), r(a.r){} // конструктор копии
      void setRadius(int r){this->r = r;} // сетер радиуса
      void draw(); // отрисовка окружности
};

class FillCircl: public Circl // Класс закрашенная окружность
{
   private:
      int fillColor; // цвет закраски
   public:
      FillCircl(int x, int y, int r, int fillColor, int color = WHITE, int thickness = 1): Circl(x, y, r, color, thickness), fillColor(fillColor){} // конструктор
      FillCircl(const FillCircl &a): Circl(a.x0, a.y0, a.r, a.color, a.thickness), fillColor(a.fillColor){} // конструктор копии
      void setFillColor(int fillColor){this->fillColor = fillColor;} //  сетер цвета закраски
      void draw(); // отрисовка
};

class Curve: public Figure // Класс кривой Безье
{
   private:
      vector<vector<int>> data; // массив точек
      double step = 0.02; // шаг искривления
      void pefog(int[100], int, int); // вычисление последовательности степеней
   
   public:
      Curve(): Figure(0, 0, WHITE, 1) {} // конструктор по умолчанию
      Curve(int data[][2], int n, int color = WHITE, int thickness = 1); // конструктор по массиву точек
      Curve(vector<vector<int>> data, int color = WHITE, int thickness = 1) : Figure(0, 0, color, thickness), data(data) {} // конструктор по вектору точек
      Curve(const Curve &a): Figure(a.x0, a.y0, a.color, a.thickness), data(a.data), step(a.step){} // конструктор копии
      void add(int x, int y){data.push_back({x, y});} // добавление точки
      void setStep(double a){step = a;} // сетер шага
      void setPoints(vector<vector<int>>); // сутер точек
      vector<vector<int>> getPoints(){return data;} // гетер точек
      void draw(); // отрисовка
};

class Picture: public Figure // Класс картинки
{
   private:
      IMAGE *file; //загруженная картинка
   public:
      Picture(int x, int y, string fileName): Figure(x, y), file(loadBMP(fileName.c_str())){} // конструктор
      void draw() {if(file) putimage(x0, y0, file, COPY_PUT);} // отрисовка
};

void outcoord(); // вывод координат указателя мыши
void drawAll(vector<Figure*> acts); // отрисовка всех фигур

#endif