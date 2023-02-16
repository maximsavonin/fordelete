#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "graphics.h"

using namespace std;

class Figure
{
   int c; // ����
   bool visible; // ���������
   protected:
      int x,y; // ������� �����
      virtual void draw(); // ����������
   public:
      Figure(int x, int y, int c): x(x), y(y), c(c){visible = false;} // �����������
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

class Sector: public Figure
{
   protected:
      double r, fi1, fi2; // ������ � ������ �������
      void draw(); // ����������
   public:
      Sector(int x, int y, int c, double r, double fi1, double fi2): Figure(x, y, c), r(r), fi1(fi1), fi2(fi2) {} // �����������
      ~Sector(){hide();} // ����������
      void setsizes(double r, double fi1, double fi2);// ��������� �������
      void area(int &x1,int &y1,int &x2,int &y2) const; // �������� ������� ������������� �������, ���������� ������
};

class FillSector: public Sector
{
   int fillc; // ���� ��������
   void draw(); // ����������
   public:
      FillSector(int x, int y, int c, double r, double fi1, double fi2, int fillc): Sector(x, y, c, r, fi1, fi2), fillc(fillc){} //�����������
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

void Sector::area(int &x1,int &y1,int &x2,int &y2) const {
   x1 = x+fmin(0, fmin(r*cos(fi1/180.0*M_PI), r*cos(fi2/180.0*M_PI)))-1;
   y1 = y+fmin(0, fmin(-r*sin(fi1/180.0*M_PI), -r*sin(fi2/180.0*M_PI)))-1;
   x2 = x+fmax(0, fmax(r*cos(fi1/180.0*M_PI), r*cos(fi2/180.0*M_PI)))+1;
   y2 = y+fmax(0, fmax(-r*sin(fi1/180.0*M_PI), -r*sin(fi2/180.0*M_PI)))+1;
}

void Sector::setsizes(double r, double fi1, double fi2) {
   bool s = isvisible();
   if (s) hide();
   this->r = r;
   this->fi1 = fi1;
   this->fi2 = fi2;
   if (s) show();
}

void Sector::draw() {
   ::setcolor(getcolor());
   arc(x, y, fi1, fi2, r);
   line(x, y, x+r*cos(fi1/180.0*M_PI), y-r*sin(fi1/180.0*M_PI));
   line(x, y, x+r*cos(fi2/180.0*M_PI), y-r*sin(fi2/180.0*M_PI));
}

void FillSector::draw() {
   setfillstyle(SOLID_FILL, fillc);
   Sector::draw();
   int x1, x2, y1, y2;
   Sector::area(x1, y1, x2, y2);
   floodfill((x1+x2)/2, (y1+y2)/2, getcolor());
}
void FillSector::setfillcolor(int c) {
   fillc = c;
   if (isvisible()) draw();
}

int main() {
   initwindow(800, 800);
   Figure *a=new Sector(200, 300, WHITE, 30, 180, 270);
   Figure *b=new FillSector(400, 300, YELLOW, 80, 0, 90, LIGHTCYAN);
   
   a->show();
   b->show();
   getch();
   a->hide();
   b->hide();
   getch();
   a->move(300, 400);
   b->move(500, 400);
   a->show();
   b->show();
   getch();
   a->setcolor(GREEN);
   b->setcolor(LIGHTBLUE);
   getch();
// ��������� ��������� ��������, ��� ������ ��������
   if (Sector *r=dynamic_cast<Sector *>(a)) r->setsizes(40, 100, 180);
   if (Sector *r=dynamic_cast<Sector *>(b)) r->setsizes(100, 30, 80);
   getch();
// ��������� ����������, ������ a �� ������ ����������
   if (FillSector *r=dynamic_cast<FillSector *>(a)) r->setfillcolor(GREEN);
   if (FillSector *r=dynamic_cast<FillSector *>(b)) r->setfillcolor(GREEN);
   getch();
// ��������� ������������ � ������ ��� ��������
   delete a;
   delete b;
   getch();
   return 0;
}
