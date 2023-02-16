#include <iostream>

using namespace std;

class Set32
{
   /*ƒл€ временного хранени€ состо€ни€ множества*/
   unsigned long tempSet;
   public:
      /* онструктор*/
      Set32 ();
      /*перегрузка операции * */
      Set32& operator *= (const Set32& y);
      /*перегрузка операции += дл€ множества */
      Set32& operator += (const Set32& y);
      /*перегрузка операции += дл€ числа */
      Set32& operator += (unsigned long z);
      /*перегрузка операции -= дл€ множества */
      Set32& operator -= (Set32& y);
      /*перегрузка операции -= дл€ числа */
      Set32& operator -= (unsigned long z);
      /*перегрузка операции ! */
      bool operator ! ();
      /*перегрузка операции >= */
      bool operator >= (unsigned long int z);
      /*перегрузка операции == */
      friend bool operator == (const Set32& x, const Set32& y);
      /*перегрузка операции != */
      friend bool operator != (const Set32& x, const Set32& y);
      /*перегрузка операции <= */
      friend bool operator <= (const Set32& x, const Set32& y);
      /*перегрузка операции >= */
      friend bool operator >= (const Set32& x, const Set32& y);
      /*перегрузка операции >> */
      friend istream& operator >> (istream &in, Set32 &с);
      /*перегрузка операции << */
      friend ostream& operator << (ostream &out, const Set32&с);
};

/*–еализаци€ перегрузок операций класса Set32*/
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
   cout << "ѕроверка работы операций над множествами, ввод множеств происходит в виде: {7,13,53}, если множество пустое, то используетс€ знак / " << endl;
   cout << "¬ведите множество x: ";
   cin >> x;
   cout << "¬ведите множество y: ";
   cin >> y;
   cout << "ѕроверка пересечени€ множеств операцией * :" <<
   endl;
   cout << x << " * " << y << " = ";
   cout << (x * y) << endl;
   cout << "ѕроверка пересечени€ множеств операцией *= :" <<
   endl;
   cout << x << " *= " << y << " = ";
   cout << (x *= y) << endl;
   cout << "ѕроверка объединени€ множеств операцией + :" <<
   endl;
   cout << x << " + " << y << " = ";
   cout << (x + y) << endl;
   cout << "ѕроверка объединени€ множеств операцией += :" <<
   endl;
   cout << x << " += " << y << " = ";
   cout << (x += y) << endl;
   cout << "ѕроверка включение числа z в множество x операцией += :" << endl;
   cout << "¬ведите целое число z от 0 до 31: ";
   cin >> z;
   cout << x << " += " << z << " = ";
   cout << (x += z) << endl;
   cout << "ѕроверка разности множеств операцией -: " << endl;
   cout << x << " - " << y << " = ";
   cout << (x - y) << endl;
   cout << "ѕроверка разности множеств операцией -= :" << endl;
   cout << x << " -= " << y << " = ";
   cout << (x -= y) << endl;
   cout << "ѕроверка исключение числа z из множества y операцией -=: " << endl;
   cout << "¬ведите целое число z от 0 до 31: ";
   cin >> z;
   cout << y << " -= " << z << " = ";
   cout << (y -= z) << endl;
   cout << "ѕроверка множеств на совпадение операцией ==: " <<
   endl;
   cout << x << " == " << y << " = " << (x == y) << endl;
   cout << "ѕроверка множеств на совпадение операцией !=: " <<
   endl;
   cout << x << " != " << y << " = " << (x != y) << endl;
   cout << "ѕроверка операции <= дл€ множеств: " << endl;
   cout << x << " <= " << y << " = " << (x <= y) << endl;
   cout << "ѕроверка операции >= дл€ множеств: " << endl;
   cout << x << " >= " << y << " = " << (x >= y) << endl;
   cout << "ѕроверка вхождени€ числа z в множество x операцией <=: " << endl;
   cout << z << " <= " << x << " = " << (z <= x) << endl;
   cout << "ѕроверка вхождени€ числа z в множество x операцией >=: " << endl;
   cout << x << " >= " << z << " = " << (x >= z) << endl;
   cout << "ѕроверка множества на пустоту операцией ! : " <<
   endl;
   cout << "!" << x << " = " << !x << endl;*/
   int f(char *);
   int f(double *);
   int f(long *);
   int y;
   char x='a';
   y = f(x);
}
