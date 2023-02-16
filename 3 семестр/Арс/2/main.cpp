#include <iostream>

using namespace std;

class Vector {
   double x, // числитель
          y; // знаменатель.
   public:
      Vector(long x=0, long y=0): x(x), y(y){}//конструктор
      double operator*(Vector);//перегрузка операции *
      Vector &operator+=(const Vector&);//перегрузка операции +=
      Vector &operator-=(const Vector&);//перегрузка операции -=
      friend Vector operator*(Vector, double);
      friend Vector operator/(Vector, double);
      friend bool operator==(const Vector &, const Vector &);//перегрузка операции ==
      friend bool operator!=(const Vector &, const Vector &);//перегрузка операции ==
      bool operator!()const{return (x == 0 and y == 0);}//перегрузка операции !
      friend istream &operator>>(istream &s, Vector &p);//перегрузка операции  >>
      friend ostream &operator<<(ostream &s, const Vector &p);// перегрузка операции  <<
      long getx() const { return x; }
      long gety() const { return y; }
};

Vector &Vector::operator+=(const Vector&v) {
   x += v.x;
   y += v.y;
   return *this;
}

Vector operator+(Vector v1, Vector v2) {
   return v1 += v2;
}
Vector &Vector::operator-=(const Vector&v) {
   x -= v.x;
   y -= v.y;
   return *this;
}

Vector operator-(Vector v1, Vector v2) {
   return v1 -= v2;
}

double Vector::operator*(Vector v)
{
   return x*v.x+y*v.y;
}

Vector operator*(Vector v, double k)
{
   v.x *= k;
   v.y *= k;
   return v;
}

Vector operator/(Vector v, double k)
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
   return s>>c[0]>>v.x>>c[1]>>v.y>>c[2];
}

ostream &operator<<(ostream &s, const Vector &v) {
   return s<<'('<<v.x <<","<<v.y<<')';
}

int main() {
   Vector a(4, 3), b(1,2);
   cout<<"Вывод\n";
   cout<<"a="<<a<<" "<<"b="<<b<<endl;
   cout<<"Ввод a\n";
   cin>>a;
   cout<<"a="<<a <<endl;
   
   cout<<"Проверка операции +\n";
   cout<<a<<" + "<<b<<" = "<<(a+b)<<endl;
   
   cout<<"Проверка операции -\n";
   cout<<a<<" - "<<b<<" = "<<(a-b)<<endl;
    
   cout<<"Проверка операции *\n";
   cout<<a<<" * "<<b<<" = "<<(a*b)<<endl;
   cout<<a<<" * "<<2<<" = "<<(a*2)<<endl;
    
   cout<<"Проверка операции /\n";
   cout<<a<<" / "<<2<<" = "<<(a/2)<<endl;

   cout<<"Проверка операции +=\n";
   a+=b;
   cout<<"a="<<a<<endl;
    
   cout<<"Проверка операции -=\n";
   a-=b;
   cout<<"a="<<a<<endl;

   cout<<"Проверка операции ==\n";
   cout<<a<<" == "<<b<<" = "<<(a==b)<<endl;
   
   cout<<"Проверка операции !=\n";
   cout<<a<<" != "<<b<<" = "<<(a!=b)<<endl;
   
   cout<<"Проверка операции !()\n";
   cout<<"!"<<a<<' '<<(!(a))<<endl;
   return 0;
}
