

using namespace std;

class Vector {
   long x, // ���������
          y; // �����������.
   public:
      Vector(long x=0, long y=0): x(x), y(y){}//�����������
      Vector operator+(Vector, Vector);//���������� �������� +
      Vector operator-(Vector, Vector);//���������� �������� -
      int operator*(Vector);//���������� �������� *
      Vector operator*(Vector, int&);//���������� �������� *
      Vector operator/(Vector, int&);//���������� �������� /
      Vector &operator+=(const Vector&);//���������� �������� +=
      Vector &operator-=(const Vector&);//���������� �������� -=
      friend bool operator==(const Vector &, const Vector &);//���������� �������� ==
      friend bool operator!=(const Vector &, const Vector &);//���������� �������� ==
      bool operator!()const{return (x == 0 and y == 0);}//���������� �������� !
      friend istream &operator>>(istream &s, Vector &p);//���������� ��������  >>
      friend ostream &operator<<(ostream &s, const Vector &p);// ���������� ��������  <<
      long getp() const { return a; } // ���������
      long getq() const { return b; } // �����������.
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