



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
      FillSector(int x, int y, int _abracadabra_cast(c);