#include <iostream>

using namespace std;

class Complex 
{
   private:
      double a, b; // �������������� � ������ �����
   public:
      Complex(){a = 0; b = 0;}//�����������
      Complex(double a1, double b1){a = a1; b = b1;}//�����������
      Complex operator+(Complex&);
      Complex operator-(Complex&);
      Complex operator*(Complex&);
      Complex operator/(Complex&);
      Complex &operator+=(const Complex&);//���������� �������� +=
      Complex &operator-=(const Complex&);//���������� �������� -=
      Complex &operator*=(const Complex&);//���������� �������� *=
      Complex &operator/=(const Complex&);//���������� �������� /=
      friend bool operator==(const Complex &, const Complex &);//���������� �������� ==
      friend bool operator!=(const Complex &, const Complex &);//���������� �������� ==
      bool operator!()const{return (a==0 and b==0);}//���������� �������� !
      friend istream &operator>>(istream &s, Complex &p);//���������� ��������  >>
      friend ostream &operator<<(ostream &s, const Complex &p);// ���������� ��������  <<
      long getReal() const { return a; } // ��������������
      long getImaginary() const { return b; } // ������
};


Complex Complex::operator+(Complex& �)
{
   Complex ans(a+�.a, b+�.b);
   return ans;
}

Complex Complex::operator-(Complex& c)
{
   Complex ans(a-c.a, b-c.b);
   return ans;
}

Complex Complex::operator*(Complex& c)
{
   Complex ans(a*c.a-b*c.b, a*c.b+b*c.a);
   return ans;
}

Complex Complex::operator/(Complex& c)
{
   double del = c.a*c.a+c.b*c.b;
   Complex ans((a*c.a+b*c.b)*(1.0)/del, ((-1)*a*c.b+b*c.a)*(1.0)/del);
   return ans;
}

Complex &Complex::operator+=(const Complex& c) {
   a = a+c.a;
   b = b+c.b;
   return *this;
}

Complex &Complex::operator-=(const Complex& c) {
   a = a-c.a;
   b = b-c.b;
   return *this;
}

Complex &Complex::operator*=(const Complex& c) {
   double a1 = a;
   double b1 = b;
   a = a1*c.a-b1*c.b;
   b = a1*c.b+b1*c.a;
   return *this;
}

Complex &Complex::operator/=(const Complex&c) {
   double a1 = a;
   double b1 = b;
   a = a1*c.a+b1*c.b;
   b = (-1)*a1*c.b+b1*c.a;
   double del = c.a*c.a+c.b*c.b;
   a = a*(1.0)/del;
   b = b*(1.0)/del;
   return *this;
}

bool operator==(const Complex &x, const Complex &y) {
   return (x.a == y.a and x.b == y.b);
}

bool operator!=(const Complex &x, const Complex &y) {
   return !(x==y);
}


istream &operator>>(istream &s, Complex &p) {
   char c;
   s>>p.a>>c>>p.b;
   if(c == '-') p.b *= (-1);
   return s;
}

ostream &operator<<(ostream &s, const Complex &p) {
   if(p.b == 0) return s << p.a;
   if(p.a == 0) return s << p.b << 'i';
   if(p.b < 0) return s << p.a << p.b << 'i';
   return s<< p.a << "+"<< p.b << 'i';
}


int main()
{
   Complex a(1, 2);
   cout << "a=" << a << endl;
   Complex b(3, 4);
   cout << "b=" << b << endl;
   Complex c;
   c = a+b;
   cout << "a+b=" << c << endl;
   c = a-b;
   cout << "a-b=" << c << endl;
   c = a*b;
   cout << "a*b=" << c << endl;
   c = a/b;
   cout << "a/b=" << c << endl;
   c = a+b;
   c += b;
   cout << "c=a+b, c+=b, c=" << c << endl;
   c = a+b;
   c -= b;
   cout << "c=a+b, c-=b, c=" << c << endl;
   c = a+b;
   c *= b;
   cout << "c=a+b, c*=b, c=" << c << endl;
   c = a+b;
   c /= b;
   cout << "c=a+b, c/=b, c=" << c << endl;
   cout << "a==b " << a==b << endl;
   cout << "a!=b " << a!=b << endl;
   cout << "!a " << !a << endl;
   return 0;
}