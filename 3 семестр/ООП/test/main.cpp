#include <iostream>

using namespace std;

class Rational {
   private:
      long a, // ���������
             b; // �����������.
   public:
      Rational(long=0, long=1);//�����������
      Rational &operator+=(const Rational&);//���������� �������� +=
      Rational &operator-=(const Rational&);//���������� �������� -=
      Rational &operator*=(const Rational&);//���������� �������� *=
      Rational &operator/=(const Rational&);//���������� �������� /=
      friend bool operator>(const Rational &,const Rational &);//���������� �������� >
      friend bool operator<(const Rational &,const Rational &);//���������� �������� <
      friend bool operator>=(const Rational &,const Rational &);//���������� �������� >=
      friend bool operator<=(const Rational &,const Rational &);//���������� �������� <=
      friend bool operator==(const Rational &, const Rational &);//���������� �������� ==
      friend bool operator!=(const Rational &, const Rational &);//���������� �������� !=
      bool operator!()const{return (a==0);}//���������� �������� !
      friend istream &operator>>(istream &, Rational &);//���������� ��������  >>
      friend ostream &operator<<(ostream &, const Rational &);// ���������� ��������  <<
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
Rational::Rational(long a, long b){
   long tmp=NOD(a,b);
   this->a=a/tmp;
   this->b=b/tmp;
}

Rational &Rational::operator+=(const Rational&r) {
   a=a*r.b+r.a*b;
   b=b*r.b;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}

Rational operator+(Rational x, Rational y) {
   return x+=y;
}

Rational &Rational::operator-=(const Rational&r) {
   a=a*r.b-r.a*b;
   b=b*r.b;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}

Rational operator-(Rational x, Rational y) {
   return x-=y;
}

Rational &Rational::operator*=(const Rational&r) {
   a=a*r.a;
   b=b*r.b;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}

Rational operator*(Rational x, Rational y) {
   return x*=y;
}

Rational &Rational::operator/=(const Rational&r) {
   a=a*r.b;
   b=b*r.a;
   long tmp=NOD(a,b);
   a/=tmp;
   b/=tmp;
   return *this;
}

Rational operator/(Rational x, Rational y) {
   return x/=y;
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
   return (x.a==x.b&&y.a==y.b);
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
   Rational a(1, 3), b(1,2), c(15);
   cout<<"�����\n";
   cout<<"a="<<a<<" "<<"b="<<b<<" "<<"c="<<c<<endl;
   cout<<"���� a\n";
   cin>>a;
   cout<<"a="<<a <<endl;
   cout<<"�������� �������� +\n";
   cout<<a<<" + "<<b<<" = "<<(a+b)<<endl;
   cout<<a<<" + "<<2<<" = "<<(a+2)<<endl;
   cout<<2<<" + "<<a<<" = "<<(2+a)<<endl;
   cout<<a+b<<endl;
   cout<<"�������� �������� -\n";
   cout<<a<<" - "<<b<<" = "<<(a-b)<<endl;
   cout<<a<<" - "<<2<<" = "<<(a-2)<<endl;
   cout<<2<<" - "<<a<<" = "<<(2-a)<<endl;
   cout<<a-b<<endl;
   cout<<"�������� �������� *\n";
   cout<<a<<" * "<<b<<" = "<<(a*b)<<endl;
   cout<<a<<" * "<<2<<" = "<<(a*2)<<endl;
   cout<<2<<" * "<<a<<" = "<<(2*a)<<endl;
   cout<<a*b<<endl;
   cout<<"�������� �������� /\n";
   cout<<a<<" / "<<b<<" = "<<(a/b)<<endl;
   cout<<a<<" / "<<2<<" = "<<(a/2)<<endl;
   cout<<2<<" / "<<a<<" = "<<(2/a)<<endl;
   cout<<a/b<<endl;
   
   cout<<"�������� �������� +=\n";
   a+=b;
   cout<<"a="<<a<<endl;
   cout<<"�������� �������� -=\n";
   a-=b;
   cout<<"a="<<a<<endl;
   cout<<"�������� �������� *=\n";
   a*=b;
   cout<<"a="<<a<<endl;
   cout<<"�������� �������� /=\n";
   a/=b;
   cout<<"a="<<a<<endl;

   cout<<"�������� �������� >\n";
   cout<<a<<" > "<<b<<" = "<<(a>b)<<endl;
   cout<<a<<" > "<<2<<" = "<<(a>2)<<endl;
   cout<<2<<" > "<<a<<" = "<<(2>a)<<endl;
   cout<<"�������� �������� <\n";
   cout<<a<<" < "<<b<<" = "<<(a<b)<<endl;
   cout<<a<<" < "<<2<<" = "<<(a<2)<<endl;
   cout<<2<<" < "<<a<<" = "<<(2<a)<<endl;
   cout<<"�������� �������� >=\n";
   cout<<a<<" >= "<<b<<" = "<<(a>=b)<<endl;
   cout<<a<<" >= "<<2<<" = "<<(a>=2)<<endl;
   cout<<2<<" >= "<<a<<" = "<<(2>=a)<<endl;
   cout<<"�������� �������� <=\n";
   cout<<a<<" <= "<<b<<" = "<<(a<=b)<<endl;
   cout<<a<<" <= "<<2<<" = "<<(a<=2)<<endl;
   cout<<2<<" <= "<<a<<" = "<<(2<=a)<<endl;
   cout<<"�������� �������� ==\n";
   cout<<a<<" == "<<b<<" = "<<(a==b)<<endl;
   cout<<a<<" == "<<2<<" = "<<(a==2)<<endl;
   cout<<2<<" == "<<a<<" = "<<(2==a)<<endl;
   cout<<"�������� �������� !=\n";
   cout<<a<<" != "<<b<<" = "<<(a!=b)<<endl;
   cout<<a<<" != "<<2<<" = "<<(a!=2)<<endl;
   cout<<2<<" != "<<a<<" = "<<(2!=a)<<endl;
   cout<<"�������� �������� !()\n";
   cout<<"!"<<a<<' '<<(!(a))<<endl;

   return 0;
}
