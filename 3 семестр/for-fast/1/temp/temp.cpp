



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
         double c = (_abracadabra_cast(this);