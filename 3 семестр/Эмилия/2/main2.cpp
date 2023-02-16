#include <iostream>
#include <cmath>

using namespace std;

class Rect {
   long l, t, // ����� ������� ����
          r, b; // ������ ������ ����
   bool real;
   public:
      Rect(long l=0, long t=0, long r=0, long b=0): l(l), t(t), r(r), b(b), real(true){}//�����������
      Rect &operator+=(const Rect&); //���������� �������� +=
      Rect &operator*=(const Rect&); //���������� �������� *=
      friend bool operator==(const Rect &, const Rect &);//���������� �������� ==
      friend bool operator!=(const Rect &, const Rect &);//���������� �������� !=
      friend bool operator<=(const Rect &,const Rect &);//���������� �������� <=
      friend bool operator>=(const Rect &,const Rect &);//���������� �������� >=
      bool operator!()const{return (!real);}//���������� �������� !
      friend istream &operator>>(istream &s, Rect &r);//���������� ��������  >>
      friend ostream &operator<<(ostream &s, const Rect &r);// ���������� ��������  <<
      long getLeft() const { return l; }  // ������ x
      long getTop() const { return t; } // ������� y
      long getRight() const { return r; } // ����� x
      long getBottom() const { return b; } // ������ y
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
   l = fmax(l, rect.l);
   r = fmin(r, rect.r);
   t = fmax(t, rect.t);
   b = fmin(b, rect.b);
   if(r-l <= 0 || b-t <= 0)
   {
      real = false;
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
   return (x.l >= y.l and x.t >= y.t and x.r <= y.r and x.b <= y.b and x.real);
}

bool operator>=(const Rect &x, const Rect &y) {
   return (y<=x);
}

istream &operator>>(istream &s, Rect &r) {
   char c[5];
   return s>>c[0]>>r.l>>c[1]>>r.t>>c[2]>>r.r>>c[3]>>r.b>>c[4];
}

ostream &operator<<(ostream &s, const Rect &r) {
   return s<<'['<<r.l <<","<<r.t<<','<<r.r<<','<<r.b<<']';
}

int main()
{
   Rect r1(0, 0, 10, 10), r2(3, 6, 15, 15);
   cout<<"�����\n";
   cout<<"r1="<<r1<<" "<<"r2="<<r2<<endl;
   cout<<"���� r1\n";
   cin>>r1;
   cout<<"r1="<<r1 <<endl;
   
   cout<<"�������� �������� +\n";
   cout<<r1<<" + "<<r2<<" = "<<(r1+r2)<<endl;
   
   cout<<"�������� �������� *\n";
   cout<<r1<<" * "<<r2<<" = "<<(r1*r2)<<endl;
    
   cout<<"�������� �������� +=\n";
   r1+=r2;
   cout<<"r1 += r2, r1 ="<<r1<<endl;
    
   cout<<"�������� �������� *=\n";
   r1*=r2;
   cout<<"r1 *= r2, r1 ="<<r1<<endl;

   cout<<"�������� �������� ==\n";
   cout<<r1<<" == "<<r2<<" = "<<(r1==r2)<<endl;
   
   cout<<"�������� �������� !=\n";
   cout<<r1<<" != "<<r2<<" = "<<(r1!=r2)<<endl;
   
   cout<<"�������� �������� !()\n";
   cout<<"!("<<r1<<") "<<(!(r1))<<endl;
   return 0;
}