#include <iostream>

using namespace std;

class Set32
{
   /*��� ���������� �������� ��������� ���������*/
   unsigned long tempSet;
   public:
      /*�����������*/
      Set32 ();
      /*���������� �������� * */
      Set32& operator *= (const Set32& y);
      /*���������� �������� += ��� ��������� */
      Set32& operator += (const Set32& y);
      /*���������� �������� += ��� ����� */
      Set32& operator += (unsigned long z);
      /*���������� �������� -= ��� ��������� */
      Set32& operator -= (Set32& y);
      /*���������� �������� -= ��� ����� */
      Set32& operator -= (unsigned long z);
      /*���������� �������� ! */
      bool operator ! ();
      /*���������� �������� >= */
      bool operator >= (unsigned long int z);
      /*���������� �������� == */
      friend bool operator == (const Set32& x, const Set32& y);
      /*���������� �������� != */
      friend bool operator != (const Set32& x, const Set32& y);
      /*���������� �������� <= */
      friend bool operator <= (const Set32& x, const Set32& y);
      /*���������� �������� >= */
      friend bool operator >= (const Set32& x, const Set32& y);
      /*���������� �������� >> */
      friend istream& operator >> (istream &in, Set32 &�);
      /*���������� �������� << */
      friend ostream& operator << (ostream &out, const Set32&�);
};

/*���������� ���������� �������� ������ Set32*/
Set32 :: Set32 () { tempSet = 0; }
Set32 operator * (Set32 x, Set32 y) { return x *= y; }
Set32& Set32 :: operator *= (const Set32& y) { tempSet &= y.tempSet; return *this; }
Set32 operator + (Set32 x, Set32 y) { return x += y; }
Set32& Set32 :: operator += (const Set32& y) { tempSet |= y.tempSet; return *this; }
Set32& Set32 :: operator += (unsigned long z) { tempSet |= (1 << z); return *this; }
Set32 operator - (Set32 x, Set32 y) { return x -= y; }
Set32& Set32 :: operator -= (Set32& y) { tempSet &= ~(tempSet & y.tempSet); return *this; }
Set32& Set32 :: operator -= (unsigned long z) { tempSet &= ~(1 << z); return *this; }
bool Set32 :: operator ! () { return !(tempSet); }
bool operator <= (unsigned int z, Set32 x) { return x >= z; }
bool Set32 :: operator >= (unsigned long int z) { return tempSet & (1 << z); }
bool operator == (const Set32& x, const Set32& y) { return (x.tempSet == y.tempSet); }
bool operator != (const Set32& x, const Set32& y) { return !(x == y); }
bool operator <= (const Set32& x, const Set32& y) {
   unsigned int a = x.tempSet, b = y.tempSet;
   int Y = 0, X = 0;
   while (a) { X += a & 1; a >>= 1; }
   while (b) { Y += b & 1; b >>= 1; }
   return (X <= Y);
}
bool operator >= (const Set32& x, const Set32& y) {
   unsigned int a = x.tempSet, b = y.tempSet;
   int X = 0, Y = 0;
   while (a) { X += a & 1; a >>= 1; }
   while (b) { Y += b & 1; b >>= 1; }
   return (X >= Y);
}
istream& operator >> (istream &in, Set32 &s) {
   unsigned int n;
   char c;
   in >> c;
   if (c == '/') { s.tempSet = 0; return in; }
   else while (c != '}') { in >> n >> c; s += n; }
   return in;
}
ostream& operator << (ostream &out, const Set32 &s) {
   if (s.tempSet == 0) { out << "/"; return out; }
   else {
      unsigned int a = s.tempSet;
      out << "{";
      while (a) { out << a; a >>= 1; if(a) out << ',';}
   }
   out << "}";
   return out;
}

int main() {
   /*setlocale(LC_ALL, "Russian");
   unsigned long z;
   Set32 x;
   Set32 y;
   cout << "�������� ������ �������� ��� �����������, ���� �������� ���������� � ����: {7,13,53}, ���� ��������� ������, �� ������������ ���� / " << endl;
   cout << "������� ��������� x: ";
   cin >> x;
   cout << "������� ��������� y: ";
   cin >> y;
   cout << "�������� ����������� �������� ��������� * :" <<
   endl;
   cout << x << " * " << y << " = ";
   cout << (x * y) << endl;
   cout << "�������� ����������� �������� ��������� *= :" <<
   endl;
   cout << x << " *= " << y << " = ";
   cout << (x *= y) << endl;
   cout << "�������� ����������� �������� ��������� + :" <<
   endl;
   cout << x << " + " << y << " = ";
   cout << (x + y) << endl;
   cout << "�������� ����������� �������� ��������� += :" <<
   endl;
   cout << x << " += " << y << " = ";
   cout << (x += y) << endl;
   cout << "�������� ��������� ����� z � ��������� x ��������� += :" << endl;
   cout << "������� ����� ����� z �� 0 �� 31: ";
   cin >> z;
   cout << x << " += " << z << " = ";
   cout << (x += z) << endl;
   cout << "�������� �������� �������� ��������� -: " << endl;
   cout << x << " - " << y << " = ";
   cout << (x - y) << endl;
   cout << "�������� �������� �������� ��������� -= :" << endl;
   cout << x << " -= " << y << " = ";
   cout << (x -= y) << endl;
   cout << "�������� ���������� ����� z �� ��������� y ��������� -=: " << endl;
   cout << "������� ����� ����� z �� 0 �� 31: ";
   cin >> z;
   cout << y << " -= " << z << " = ";
   cout << (y -= z) << endl;
   cout << "�������� �������� �� ���������� ��������� ==: " <<
   endl;
   cout << x << " == " << y << " = " << (x == y) << endl;
   cout << "�������� �������� �� ���������� ��������� !=: " <<
   endl;
   cout << x << " != " << y << " = " << (x != y) << endl;
   cout << "�������� �������� <= ��� ��������: " << endl;
   cout << x << " <= " << y << " = " << (x <= y) << endl;
   cout << "�������� �������� >= ��� ��������: " << endl;
   cout << x << " >= " << y << " = " << (x >= y) << endl;
   cout << "�������� ��������� ����� z � ��������� x ��������� <=: " << endl;
   cout << z << " <= " << x << " = " << (z <= x) << endl;
   cout << "�������� ��������� ����� z � ��������� x ��������� >=: " << endl;
   cout << x << " >= " << z << " = " << (x >= z) << endl;
   cout << "�������� ��������� �� ������� ��������� ! : " <<
   endl;
   cout << "!" << x << " = " << !x << endl;*/
   int f(char *);
   int f(double *);
   int f(long *);
   int y;
   char x='a';
   y = f(x);
}
