



using namespace std;

class Figure
{
   int c; // цвет
   bool visible; // видимость
   protected:
      int x,y; // базовая точка
      virtual void draw(); // нарисовать
   public:
      Figure(int x, int y, int c): x(x), y(y), c(c){visible = false;} // Конструктор
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

class Sector: public Figure
{
   protected:
      double r, fi1, fi2; // длинна и высота стрелки
      void draw(); // нарисовать
   public:
      Sector(int x, int y, int c, double r, double fi1, double fi2): Figure(x, y, c), r(r), fi1(fi1), fi2(fi2) {} // конструктор
      ~Sector(){hide();} // деструктор
      void setsizes(double r, double fi1, double fi2);// изменение размера
      void area(int &x1,int &y1,int &x2,int &y2) const; // получить размеры прямоугольной области, содержащей фигуру
};

class FillSector: public Sector
{
   int fillc; // цвет закраски
   void draw(); // нарисовать
   public:
      FillSector(int x, int y, int _abracadabra_cast(c);