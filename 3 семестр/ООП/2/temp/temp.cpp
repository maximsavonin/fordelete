

using namespace std;

class Rational {
   long a, // ���������
          b; // �����������.
   public:
      Rational(){a = 0; b = 1;}//�����������
      Rational(long a1, long b1){a = a1; b = b1;}//�����������
      Rational operator+(Rational&);
      Rational operator-(Rational&);
      Rational operator*(Rational&);
      Rational operator/(Rational&);
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


Rational Rational::operator+(Rational& r)
{
   Rational c;
   c.a=a*r.b+r.a*b;
   c.b=b*r.b;
   long tmp=NOD(_abracadabra_cast(c);