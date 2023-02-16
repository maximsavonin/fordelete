


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

class Pentagram: public Figure
{
   protected:
      double r, fi; // длинна и высота стрелки
      void draw(); // нарисовать
   public:
      Pentagram(int c, int x, int y, int r, int fi): Figure(c, x, y), r(r), fi(fi) {} // конструктор
      ~Pentagram(){hide();} // деструктор
      void setsizes(double r, double fi);// изменение размера
      void area(int &x1,int &y1,int &x2,int &y2) const; // получить размеры прямоугольной области, содержащей фигуру
};

class FillPentagram: public Pentagram
{
   int fillColor; // цвет закраски
   void draw(); // нарисовать
   public:
      FillPentagram(int c, int x, int y, int r, int fi, int fillColor): Pentagram(c, x, y, r, fi), fillColor(fillColor){} //конструктор
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