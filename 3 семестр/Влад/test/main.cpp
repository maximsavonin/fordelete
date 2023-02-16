#include <iostream>

using namespace std;

inline int max(int a, int b)
{
   return a<b?b:a;
}

template <typename T>
inline T max(T a, T b)
{
   return a<b?b:a;
}

void input(int &x)
{
   scanf("%d", &x);
}

void input(double &y)
{
   scanf("%lf", &y);
}

void input(char &z)
{
   scanf("%c", &z);
}

int main()
{
   int x;
   double y;
   char z;
   input(x);
   input(y);
   input(z);
   cout << x << ' ' << y << ' ' << z;
}