


using namespace std;

class Rect {
   long l, t, // левый верхний угол
          r, b; // правый нижний угол
   bool real;
   public:
      Rect(long l=0, long t=0, long r=0, long b=0): l(l), t(t), r(r), b(b), real(true){}//конструктор
      Rect &operator+=(const Rect&); //перегрузка операции +=
      Rect &operator*=(const Rect&); //перегрузка операции *=
      friend bool operator==(const Rect &, const Rect &);//перегрузка операции ==
      friend bool operator!=(const Rect &, const Rect &);//перегрузка операции !=
      friend bool operator<=(const Rect &,const Rect &);//перегрузка операции <=
      friend bool operator>=(const Rect &,const Rect &);//перегрузка операции >=
      bool operator!()const{return (!real);}//перегрузка операции !
      friend istream &operator>>(istream &s, Rect &r);//перегрузка операции  >>
      friend ostream &operator<<(ostream &s, const Rect &r);// перегрузка операции  <<
      long getLeft() const { return l; }  // правый x
      long getTop() const { return t; } // верхний y
      long getRight() const { return r; } // левый x
      long getBottom() const { return b; } // нижний y
};

Rect& Rect::operator+=(const Rect& rect) {
   if(!real || !rect.real) return *this;
   l = fmin(l, rect.l);
   t = fmin(t, rect.t);
   r = fmax(r, rect.r);
   b = fmax(b, rect.b);
   return *this;
}

Rect operator+(Rect r1, Rect r2) {
   return r1 += r2;
}

Rect &Rect::operator*=(const Rect&rect) {
   if(!real || !rect.real) return *this;
   r = fmax(r, rect.r);
   l = fmin(l, rect.l);
   t = fmax(t, rect.t);
   b = fmin(b, rect.b);
   if(l-r <= 0 || t-b <= 0)
   {
      real = false
      r = 0;
      t = 0;
      l = 0;
      b = 0;
   }
   return *this;
}

Rect operator*(Rect r1, Rect r2) {
   return r1 *= r2;
}

bool operator==(const Rect &r1, const Rect &r2) {
   return (r1.r == r2.r and r1.t == r2.t and r1.l == r2.l and r1.b == r2.b and r1.real == r2.real);
}

bool operator!=(const Rect &r1, const Rect &r2) {
   return !(r1==r2);
}

bool operator<=(const Rect &x, const Rect &y) {
   return (x.l >= y.l and x.t >= y.t and x.r <= y.r and x.b <= y.b and _abracadabra_cast(x);