


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
      virtual ~Figure() {} // ���������� !!!
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
   ::setcolor(BLACK);
   setfillstyle(SOLID_FILL, BLACK);
   fillellipse(x, y, r, r);
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
   _abracadabra_cast(*(this));