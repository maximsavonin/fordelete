#include <iostream>
#include <math.h>
#include "graphics.h"

using namespace std;

class Figure
{
   private:
      int c; // ����
      bool visible; // ���������
   protected:
      int x,y; // ������� �����
      virtual void draw(); // ����������
   public:
      Figure(int c, int x, int y): c(c), x(x), y(y){visible = false;} // �����������
      virtual ~Figure() {} // ����������
      void move(int x, int y); // ����������� ������ � �����
      void setcolor(int c); // ���������� ���� ������
      int getcolor() const { return c; } // �������� ����
      void hide(); // �������� ������
      void show(); // �������� ������
      bool isvisible() const { return visible; } // ������?
      virtual void area(int &x1, int &y1, int &x2, int &y2) const = 0;
   // �������� ������� ������������� �������, ���������� ������
};

class Ellips: public Figure
{
   protected:
      int r1, r2; // ������� ������
      void draw(); // ����������
   public:
      Ellips(int c, int x, int y, int r1, int r2): Figure(c, x, y), r1(r1), r2(r2){} // �����������
      ~Ellips(){hide();} // ����������
      void setsizes(int r1, int r2);// ��������� �������
      void area(int &x1,int &y1,int &x2,int &y2) const; // �������� ������� ������������� �������, ���������� ������
};

class FillEllipse: public Ellips
{
   private:
      int fillColor; // ���� ��������
      void draw(); // ����������
   public:
      FillEllipse(int c, int x, int y, int r1, int r2, int fillColor): Ellips(c, x, y, r1, r2), fillColor(fillColor){} //�����������
      void setfillcolor(int c); // �������� ���� ��������
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

void Ellips::area(int &x1,int &y1,int &x2,int &y2) const {
   x1 = x-r1;
   y1 = y-r2;
   x2 = x+r1;
   y2 = y+r2;
}

void Ellips::setsizes(int r1, int r2) {
   bool s = isvisible();
   if (s) hide();
   this->r1 = r1;
   this->r2 = r2;
   if (s) show();
}

void Ellips::draw() {
   ::setcolor(getcolor());
   ellipse(x, y, 0, 360, r1, r2);
}

void FillEllipse::draw() {
   setfillstyle(SOLID_FILL, fillColor);
   Ellips::draw();
   floodfill(x, y, getcolor());
}

void FillEllipse::setfillcolor(int c) {
   fillColor = c;
   if (isvisible()) draw();
}

int main() {
   initwindow(800, 600);
   Figure *a = new Ellips(GREEN, 200, 200, 150, 50);
   Figure *b = new FillEllipse(WHITE, 500, 200, 100, 80, BLUE);
   
   a->show();
   b->show();
   getch();
   a->hide();
   b->hide();
   getch();
   a->move(200, 400);
   b->move(500, 400);
   a->show();
   b->show();
   getch();
   a->setcolor(WHITE);
   b->setcolor(GREEN);
   getch();
// ��������� ��������� ��������, ��� ������ ��������
   if (Ellips *r=dynamic_cast<Ellips *>(a)) r->setsizes(30, 200);
   if (Ellips *r=dynamic_cast<Ellips *>(b)) r->setsizes(100, 100);
   getch();
// ��������� ����������, ������ a �� ������ ����������
   if (FillEllipse *r=dynamic_cast<FillEllipse *>(a)) r->setfillcolor(YELLOW);
   if (FillEllipse *r=dynamic_cast<FillEllipse *>(b)) r->setfillcolor(YELLOW);
   getch();
// ��������� ������������ � ������ ��� ��������
   delete a;
   delete b;
   getch();
   return 0;
}
