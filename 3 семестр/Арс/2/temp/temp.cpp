

using namespace std;

class Vector {
   long x, // числитель
          y; // знаменатель.
   public:
      Vector(long x=0, long y=0): x(x), y(y){}//конструктор
      Vector operator+(Vector, Vector);//перегрузка операции +
      Vector operator-(Vector, Vector);//перегрузка операции -
      int operator*(Vector);//перегрузка операции *
      Vector operator*(Vector, int&);//перегрузка операции *
      Vector operator/(Vector, int&);//перегрузка операции /
      Vector &operator+=(const Vector&);//перегрузка операции +=
      Vector &operator-=(const Vector&);//перегрузка операции -=
      friend bool operator==(const Vector &, const Vector &);//перегрузка операции ==
      friend bool operator!=(const Vector &, const Vector &);//перегрузка операции ==
      bool operator!()const{return (x == 0 and y == 0);}//перегрузка операции !
      friend istream &operator>>(istream &s, Vector &p);//перегрузка операции  >>
      friend ostream &operator<<(ostream &s, const Vector &p);// перегрузка операции  <<
      long getp() const { return a; } // числитель
      long getq() const { return b; } // знаменатель.
};

Vector &Vector::operator+=(const Vector&v) {
   x += v.x;
   y += v.y;
   return *this;
}

Vector Vector::operator+(Vector v1, Vector v2) {
   return v1 += v2;
}
Vector &Vector::operator-=(const Vector&v) {
   x -= v.x;
   y -= v.y;
   return *this;
}

Vector Vector::operator-(Vector v1, Vector v2) {
   return v1 -= v2;
}

int Vector::operator*(Vector&v)
{
   return x*v.x+y*v.y;
}

Vector Vector::operator*(Vector v, int&k)
{
   v.x *= k;
   v.y *= k;
   return v;
}

Vector Vector::operator/(Vector v, int&k)
{
   v.x /= k;
   v.y /= k;
   return v;
}

bool operator==(const Vector &v1, const Vector &v2) {
   return (v1.x == v2.x and v1.y == v2.y);
}

bool operator!=(const Vector &v1, const Vector &v2) {
   return !(v1==v2);
}


istream &operator>>(istream &s, Vector &v) {
   char c[3];
   return s>>c[0]>>v.x>>c[1]>>_abracadabra_cast(v);