



using namespace std;

class Figure
{
   private:
      int c; // цвет
      bool visible; // видимость
   protected:
      int x,y; // базовая точка
      virtual void draw(); // нарисовать
   public:
      Figure(int c, int x, int y): c(c), x(x), y(y){visible = false;} // Конструктор
      virtual ~Figure() {} // Деструктор
      void move(int x, int y); // переместить фигуру в точку
      void setcolor(int c); // установить цвет фигуры
      int getcolor() const { return c; } // получить цвет
      void hide(); // спрятать фигуру
      void show(); // показать фигуру
      bool isvisible() const { return visible; } // видима?
      virtual void area(int &x1, int &y1, int &x2, int &y2) const = 0;
   // получить размеры прямоугольной области, содержащей фигуру
};

class Ellipse: public Figure
{
   protected:
      int r1, r2; // радиусы элипса
      void draw(); // нарисовать
   public:
      Ellipse(int c, int x, int y, int r1, int r2): Figure(c, x, y), r1(r1), r2(r2){} // конструктор
      ~Ellipse(){hide();} // деструктор
      void setsizes(int r1, int r2);// изменение размера
      void area(int &x1,int &y1,int &x2,int &y2) const; // получить размеры прямоугольной области, содержащей фигуру
};

class FillEllipse: public Ellipse
{
   private:
      int fillColor; // цвет закраски
      void draw(); // нарисовать
   public:
      FillEllipse(int c, int x, int y, int r1, int r2, int fillColor): Ellipse(c, x, y, r1, r2), fillColor(fillColor){} //конструктор
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