#include <iostream>
#include <cmath>


using namespace std;

class Vector
{
   double x, y;
   public:
      Vector(double x, double y)
      {
         this->x = x;
         this->y = y;
      }
      double length()
      {
         return sqrt(x*x+y*y);
      }
      friend double operator*(Vector a)
      {
         double c = (this.x*a.x + this.y*a.y)/(this.length()*a.length());
         double s = sqrt(1-c*c);
         return a.length()*this.length()*s;
      }
};

int main()
{
   Vector a = Vector(1.5, 2);
   cout << a.length();
}