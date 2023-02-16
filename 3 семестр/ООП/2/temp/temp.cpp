

using namespace std;

class Rational {
   long a, // числитель
          b; // знаменатель.
   public:
      Rational(){a = 0; b = 1;}//конструктор
      Rational(long a1, long b1){a = a1; b = b1;}//конструктор
      Rational operator+(Rational&);
      Rational operator-(Rational&);
      Rational operator*(Rational&);
      Rational operator/(Rational&);
      Rational &operator+=(const Rational&);//перегрузка операции +=
      Rational &operator-=(const Rational&);//перегрузка операции -=
      Rational &operator*=(const Rational&);//перегрузка операции *=
      Rational &operator/=(const Rational&);//перегрузка операции /=
      friend bool operator<(const Rational &,const Rational &);//перегрузка операции <
      friend bool operator>(const Rational &,const Rational &);//перегрузка операции >
      friend bool operator<=(const Rational &,const Rational &);//перегрузка операции <
      friend bool operator>=(const Rational &,const Rational &);//перегрузка операции >
      friend bool operator==(const Rational &, const Rational &);//перегрузка операции ==
      friend bool operator!=(const Rational &, const Rational &);//перегрузка операции ==
      bool operator!()const{return (a==0);}//перегрузка операции !
      friend istream &operator>>(istream &s, Rational &p);//перегрузка операции  >>
      friend ostream &operator<<(ostream &s, const Rational &p);// перегрузка операции  <<
      long getp() const { return a; } // числитель
      long getq() const { return b; } // знаменатель.
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