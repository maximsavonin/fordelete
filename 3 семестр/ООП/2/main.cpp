#include <iostream>

using namespace std;

class Rational {
   long a, // ���������
          b; // �����������.
   public:
      Rational(long a=0, long b=1): a(a), b(b){}//�����������
      Rational &operator=(const long a1){a = a1; b = 1; return *this;}//���������� �������� =
      Rational operator+(Rational, Rational);
      //Rational operator+(Rational&);//���������� �������� +
      Rational operator+(int&);//���������� �������� +
      Rational operator-(Rational&);//���������� �������� -
      Rational operator*(Rational&);//���������� �������� *
      Rational operator/(Rational&);//���������� �������� /
      Rational &operator+=(const Rational&);//���������� �������� +=
      Rational &operator-=(const Rational&);//���������� �������� -=
      Rational &operator*=(const Rational&);//���������� �������� *=
      Rational &operator/=(const Rational&);//���������� �������� /=
      friend bool operator<(const Rational &,const Rational &);//���������� �������� <
      friend bool operator>(const Rational &,const Rational &);//���������� �������� >
      friend bool operator<=(const Rational &,const Rational &);//���������� �������� <
      friend bool operator>=(const Rational &,const Rational &);//���������� �������� >
      friend bool operator==(const Rational &, const Rational &);//���������� �������� ==
      friend bool operator!=(const Rational &, const Rational &);//���������� �������� ==
      bool operator!()const{return (a==0);}//���������� �������� !
      friend istream &operator>>(istream &s, Rational &p);//���������� ��������  >>
      friend ostream &operator<<(ostream &s, const Rational &p);// ���������� ��������  <<
      long getp() const { return a; } // ���������
      long getq() const { return b; } // �����������.
};

long NOD(long a, long b){
   long c;
   if(a<0) a=-a;
   while(b!=0){
      c=a;
      a=b;
      b=c%b;
   }
   return a;   
}


/*Rational Rational::operator+(Rational& r)
{
   Rational c;
   c.a=a*r.b+r.a*b;
   c.b=b*r.b;
   long tmp=NOD(c.a,c.b);
   c.a/=tmp;
   c.b/=tmp;
   return c;
}

Rational Rational::operator+(int& r)
{
   Rational c;
   c.a=a+r*b;
   c.b=b;
   long tmp=NOD(c.a,c.b);
   c.a/=tmp;
   c.b/=tmp;
   return c;
}*/

Rational &Rational::operator+=(const Rational&p) {
   a=a*p.b+p.a*b;
   b=b*p.b;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}

Rational Rational::operator+(Rational x, Rational y) {
   return x+=y;
}


Rational Rational::operator-(Rational& r)
{
   Rational c;
   c.a = a*r.b;
   c.a = c.a - r.a*b;
   c.b = b*r.b;
   long tmp=NOD(c.a,c.b);
   c.a/=tmp;
   c.b/=tmp;
   return c;
}

Rational Rational::operator*(Rational& r)
{
   Rational c;
   c.a = a*r.a;
   c.b = b*r.b;
   long tmp=NOD(c.a,c.b);
   c.a/=tmp;
   c.b/=tmp;
   return c;
}

Rational Rational::operator/(Rational& r)
{
   Rational c;
   c.a = a*r.b;
   c.b = b*r.a;
   long tmp=NOD(c.a,c.b);
   c.a/=tmp;
   c.b/=tmp;
   return c;
}

/*Rational &Rational::operator+=(const Rational&r) {
   a=a*r.b+r.a*b;
   b=b*r.b;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}*/

Rational &Rational::operator-=(const Rational&r) {
   a=a*r.b-r.a*b;
   b=b*r.b;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}

Rational &Rational::operator*=(const Rational&r) {
   a=a*r.a;
   b=b*r.b;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}

Rational &Rational::operator/=(const Rational&r) {
   a=a*r.b;
   b=b*r.a;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}

bool operator<(const Rational &x, const Rational &y) {
   if ((x.a*y.b-y.a*x.b)<0) return 1;
   return 0;
}

bool operator>(const Rational &x, const Rational &y) {
   return y<x;
}

bool operator>=(const Rational &x, const Rational &y) {
   return !(x<y);
}

bool operator<=(const Rational &x, const Rational &y) {
   return !(y<x);
}

bool operator==(const Rational &x, const Rational &y) {
   return (x.a*y.b==x.b*y.a);
}

bool operator!=(const Rational &x, const Rational &y) {
   return !(x==y);
}


istream &operator>>(istream &s, Rational &p) {
   char c;
   return s>>p.a>>c>>p.b;
}

ostream &operator<<(ostream &s, const Rational &p) {
   return s<<p.a <<"/"<<p.b;
}


int main() {
   Rational a(1, 3), b(1,2);
   cout<<"�����\n";
   cout<<"a="<<a<<" "<<"b="<<b<<" "<<endl;
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
   cout<<2<<" * "<<a<<" = "<<(2*a)<<endl;
    
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
