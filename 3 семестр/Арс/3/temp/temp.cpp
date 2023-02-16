



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

class Ellipse: public Figure
{
   protected:
      int r1, r2; // ������� ������
      void draw(); // ����������
   public:
      Ellipse(int c, int x, int y, int r1, int r2): Figure(c, x, y), r1(r1), r2(r2){} // �����������
      ~Ellipse(){hide();} // ����������
      void setsizes(int r1, int r2);// ��������� �������
      void area(int &x1,int &y1,int &x2,int &y2) const; // �������� ������� ������������� �������, ���������� ������
};

class FillEllipse: public Ellipse
{
   private:
      int fillColor; // ���� ��������
      void draw(); // ����������
   public:
      FillEllipse(int c, int x, int y, int r1, int r2, int fillColor): Ellipse(c, x, y, r1, r2), fillColor(fillColor){} //�����������
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

void Ellipse::area(int &x1,int &y1,int &x2,int &y2) const {
   x1 = x-r1;
   y1 = y-r2;
   x2 = x+r1;
   y2 = y+r2;
}

void Ellipse::setsizes(int r1, int r2) {
   bool s = isvisible();
   if (s) hide();
   this->w = w;
   _abracadabra_cast(*(this));