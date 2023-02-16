#include <iostream>

using namespace std;

class Vector {
   double x, // ���������
          y; // �����������.
   public:
      Vector(long x=0, long y=0): x(x), y(y){}//�����������
      double operator*(Vector);//���������� �������� *
      Vector &operator+=(const Vector&);//���������� �������� +=
      Vector &operator-=(const Vector&);//���������� �������� -=
      friend Vector operator*(Vector, double);
      friend Vector operator/(Vector, double);
      friend bool operator==(const Vector &, const Vector &);//���������� �������� ==
      friend bool operator!=(const Vector &, const Vector &);//���������� �������� ==
      bool operator!()const{return (x == 0 and y == 0);}//���������� �������� !
      friend istream &operator>>(istream &s, Vector &p);//���������� ��������  >>
      friend ostream &operator<<(ostream &s, const Vector &p);// ���������� ��������  <<
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
   cout<<"�����\n";
   cout<<"a="<<a<<" "<<"b="<<b<<endl;
   cout<<"���� a\n";
   cin>>a;
   cout<<"a="<<a <<endl;
   
   cout<<"�������� �������� +\n";
   cout<<a<<" + "<<b<<" = "<<(a+b)<<endl;
   
   cout<<"�������� �������� -\n";
   cout<<a<<" - "<<b<<" = "<<(a-b)<<endl;
    
   cout<<"�������� �������� *\n";
   cout<<a<<" * "<<b<<" = "<<(a*b)<<endl;
   cout<<a<<" * "<<2<<" = "<<(a*2)<<endl;
    
   cout<<"�������� �������� /\n";
   cout<<a<<" / "<<2<<" = "<<(a/2)<<endl;

   cout<<"�������� �������� +=\n";
   a+=b;
   cout<<"a="<<a<<endl;
    
   cout<<"�������� �������� -=\n";
   a-=b;
   cout<<"a="<<a<<endl;

   cout<<"�������� �������� ==\n";
   cout<<a<<" == "<<b<<" = "<<(a==b)<<endl;
   
   cout<<"�������� �������� !=\n";
   cout<<a<<" != "<<b<<" = "<<(a!=b)<<endl;
   
   cout<<"�������� �������� !()\n";
   cout<<"!"<<a<<' '<<(!(a))<<endl;
   return 0;
}
