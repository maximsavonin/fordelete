#include<iostream>
#include"graphics.h"

using namespace std;

class Figure
{
   int c; // цвет
   bool visible; // видимость
   protected:
      int x,y; // базовая точка
      virtual void draw(); // нарисовать
   public:
      Figure(int c, int x, int y): c(c), x(x), y(y){visible = false;} // Конструктор
      virtual ~Figure() {} // Деструктор !!!
      void move(int x, int y); // переместить фигуру в точку
      void setcolor(int c); // установить цвет фигуры
      int getcolor() const { return c; } // получить цвет
      void hide(); // спрятать фигуру
      void show(); // показать фигуру
      bool isvisible() const { return visible; } // видима?
      virtual void area(int &x1, int &y1, int &x2, int &y2) const = 0;
   // получить размеры прямоугольной области, содержащей фигуру
};

class Arrow: public Figure
{
   protected:
      double w, h; // длинна и высота стрелки
      void draw(); // нарисовать
   public:
      Arrow(int c, int x, int y, int w, int h): Figure(c, x, y), w(w), h(h) {} // конструктор
      ~Arrow(){hide();} // деструктор
      void setsizes(double w, double h);// изменение размера
      void area(int &x1,int &y1,int &x2,int &y2) const; // получить размеры прямоугольной области, содержащей фигуру
};

class FillArrow: public Arrow
{
   int fillc; // цвет закраски
   void draw(); // нарисовать
   public:
      FillArrow(int c, int x, int y, int w, int h, int fillc): Arrow(c, x, y, w, h), fillc(fillc){} //конструктор
      void setfillcolor(int c); // изменить цвет закраски
};

void Figure::setcolor(int c) {
   this->c = c;
   if (visible) draw();
}

void Figure::move(int x, int y) {
   bool s = visible;
   if (s) hide();
   this->x = x;
   this->y = y;
   if (s) show();
}

void Figure::hide() {
   if (visible == 0) return;
   int x1, y1, x2, y2;
   area(x1, y1, x2, y2);
   setfillstyle(SOLID_FILL, BLACK);
   bar(x1, y1, x2, y2);
   visible = 0;
}

void Figure::show() {
   if (visible) return;
   draw();
   visible = 1;
}

void Arrow::area(int &x1,int &y1,int &x2,int &y2) const {
   x1 = x;
   y1 = y - h;
   x2 = x + w + h/2;
   y2 = y;
}

void Arrow::setsizes(double w, double h) {
   bool s = isvisible();
   if (s) hide();
   this->w = w;
   this->h = h;
   if (s) show();
}

void Arrow::draw() {
   ::setcolor(getcolor());
   line(x, y, x+w, y);
   line(x, y, x, y-h);
   line(x, y-h, x+w, y-h);
   line(x+w, y, x+w+h/2, y-h/2);
   line(x+w, y-h, x+w+h/2, y-h/2);
}

void FillArrow::draw() {
   setfillstyle(SOLID_FILL, fillc);
   Arrow::draw();
   floodfill(x+w/2, y-h/2, getcolor());
}
void FillArrow::setfillcolor(int c) {
   fillc = c;
   if (isvisible()) draw();
}

int main() {
   initwindow(800, 800);
   Figure *a=new Arrow(BLUE, 200, 400, 120, 150);
   Figure *b=new FillArrow(GREEN, 600, 400, 80, 10, RED);
   
   a->show();
   b->show();
   delay(10000);
   a->hide();
   b->hide();
   delay(10000);
   a->move(400, 200);
   b->move(400, 600);
   a->show();
   b->show();
   delay(10000);
   a->setcolor(WHITE);
   b->setcolor(LIGHTBLUE);
   delay(10000);
// проверяем изменение размеров, обе фигуры меняются
   if (Arrow *r=dynamic_cast<Arrow *>(a)) r->setsizes(100, 20);
   if (Arrow *r=dynamic_cast<Arrow *>(b)) r->setsizes(100, 30);
   delay(10000);
// проверяем перекраску, фигура a не должна измениться
   if (FillArrow *r=dynamic_cast<FillArrow *>(a)) r->setfillcolor(GREEN);
   if (FillArrow *r=dynamic_cast<FillArrow *>(b)) r->setfillcolor(GREEN);
   delay(10000);
// проверяем исчезновение с экрана при удалении
   delete a;
   delete b;
   delay(10000);
   return 0;
}
