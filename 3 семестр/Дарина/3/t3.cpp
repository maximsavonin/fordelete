#include<iostream>
#include"graphics.h"

using namespace std;

class Figure
{
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

class Arrow: public Figure
{
   protected:
      double w, h; // ������ � ������ �������
      void draw(); // ����������
   public:
      Arrow(int c, int x, int y, int w, int h): Figure(c, x, y), w(w), h(h) {} // �����������
      ~Arrow(){hide();} // ����������
      void setsizes(double w, double h);// ��������� �������
      void area(int &x1,int &y1,int &x2,int &y2) const; // �������� ������� ������������� �������, ���������� ������
};

class FillArrow: public Arrow
{
   int fillc; // ���� ��������
   void draw(); // ����������
   public:
      FillArrow(int c, int x, int y, int w, int h, int fillc): Arrow(c, x, y, w, h), fillc(fillc){} //�����������
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
   line(x, y, x+h/2, y-h/2);
   line(x, y-h, x+h/2, y-h/2);
   line(x, y, x+w, y);
   line(x, y-h, x+w, y-h);
   line(x+w, y, x+w+h/2, y-h/2);
   line(x+w, y-h, x+w+h/2, y-h/2);
}

void FillArrow::draw() {
   setfillstyle(SOLID_FILL, fillc);
   Arrow::draw();
   floodfill(x+w/2+h/2, y-h/2, getcolor());
}
void FillArrow::setfillcolor(int c) {
   fillc = c;
   if (isvisible()) draw();
}

int main() {
   initwindow(640, 480);
   Figure *a=new Arrow(RED, 100, 100, 150, 80);
   Figure *b=new FillArrow(YELLOW, 300, 300, 100, 50, MAGENTA);
   a->show();
   b->show();
   getch();
   a->hide();
   b->hide();
   getch();
   a->move(350, 350);
   b->move(150, 150);
   a->show();
   b->show();
   getch();
   a->setcolor(WHITE);
   b->setcolor(RED);
   getch();
   // ��������� ��������� ��������, ��� ������ ��������
   if(Arrow *r=dynamic_cast<Arrow*>(a)) r->setsizes(100,30);
   if(Arrow *r=dynamic_cast<Arrow*>(b)) r->setsizes(100,100);
   getch();
   // ��������� ����������, ������ a �� ������ ����������
   if(FillArrow *r=dynamic_cast<FillArrow*>(a)) r->setfillcolor(YELLOW);
   if(FillArrow *r=dynamic_cast<FillArrow*>(b)) r->setfillcolor(YELLOW);
   getch();
   // ��������� ������������ � ������ ��� ��������
   delete a;
   delete b;
   getch();
   return 0;
}