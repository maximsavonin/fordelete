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

class Pentagram: public Figure
{
   protected:
      double r, fi; // ������ � ������ �������
      void draw(); // ����������
   public:
      Pentagram(int c, int x, int y, int r, int fi): Figure(c, x, y), r(r), fi(fi) {} // �����������
      ~Pentagram(){hide();} // ����������
      void setsizes(double r, double fi);// ��������� �������
      void area(int &x1,int &y1,int &x2,int &y2) const; // �������� ������� ������������� �������, ���������� ������
};

class FillPentagram: public Pentagram
{
   private:
      void fill(int x, int y); // ��������
      int fillColor; // ���� ��������
      void draw(); // ����������
   public:
      FillPentagram(int c, int x, int y, int r, int fi, int fillColor): Pentagram(c, x, y, r, fi), fillColor(fillColor){} //�����������
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

void Pentagram::area(int &x1,int &y1,int &x2,int &y2) const {
   x1 = x-r;
   y1 = y-r;
   x2 = x+r;
   y2 = y+r;
}

void Pentagram::setsizes(double r, double fi) {
   bool s = isvisible();
   if (s) hide();
   this->r = r;
   this->fi = fi;
   if (s) show();
}

void Pentagram::draw() {
   ::setcolor(getcolor());
   int x0, y0;
   x0 = x+int(r*(cos(3.14/5*2)/cos(3.14/5))*cos(fi));
   y0 = y+int(r*(cos(3.14/5*2)/cos(3.14/5))*sin(fi));
   for(int i = 1; i < 11; i++)
   {
      int y1, x1;
      if(i%2)
      {
         x1 = x+int(r*cos(i*3.14/5+fi));
         y1 = y+int(r*sin(i*3.14/5+fi));
      }
      else
      {
         x1 = x+int(r*(cos(3.14/5*2)/cos(3.14/5))*cos(i*3.14/5+fi));
         y1 = y+int(r*(cos(3.14/5*2)/cos(3.14/5))*sin(i*3.14/5+fi));
      }
      line(x0, y0, x1, y1);
      x0 = x1;
      y0 = y1;
   }
}

void FillPentagram::fill(int x, int y)
{
   if(getpixel(x, y) == 0)
   {
      putpixel(x, y, fillColor);
      fill(x+1, y);
      fill(x-1, y);
      fill(x, y+1);
      fill(x, y-1);
   }
}

void FillPentagram::draw() {
   setfillstyle(SOLID_FILL, fillColor);
   Pentagram::draw();
   fill(x, y);
}

void FillPentagram::setfillcolor(int c) {
   fillColor = c;
   if (isvisible()) draw();
}

int main() {
   initwindow(800, 600);
   Figure *a=new Pentagram(BLUE, 100, 100, 30, 2);
   Figure *b=new FillPentagram(GREEN, 300, 100, 125, 1, RED);
   
   a->show();
   b->show();
   while(!mousebuttons());
   while(mousebuttons());
   a->hide();
   b->hide();
   while(!mousebuttons());
   while(mousebuttons());
   a->move(200, 200);
   b->move(500, 200);
   a->show();
   b->show();
   while(!mousebuttons());
   while(mousebuttons());
   a->setcolor(WHITE);
   b->setcolor(LIGHTBLUE);
   while(!mousebuttons());
   while(mousebuttons());
// ��������� ��������� ��������, ��� ������ ��������
   if (Pentagram *r=dynamic_cast<Pentagram *>(a)) r->setsizes(130, 2);
   if (Pentagram *r=dynamic_cast<Pentagram *>(b)) r->setsizes(30, 2);
   while(!mousebuttons());
   while(mousebuttons());
// ��������� ����������, ������ a �� ������ ����������
   if (FillPentagram *r=dynamic_cast<FillPentagram *>(a)) r->setfillcolor(GREEN);
   if (FillPentagram *r=dynamic_cast<FillPentagram *>(b)) r->setfillcolor(GREEN);
   while(!mousebuttons());
   while(mousebuttons());
// ��������� ������������ � ������ ��� ��������
   delete a;
   delete b;
   while(!mousebuttons());
   while(mousebuttons());
   return 0;
}
