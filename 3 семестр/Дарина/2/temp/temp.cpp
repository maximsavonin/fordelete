

using namespace std;

class Complex 
{
   double a, b; // действительная и мнимая часть
   public:
      Complex(){a = 0; b = 0;}//конструктор
      Complex(double a1, double b1){a = a1; b = b1;}//конструктор
      Complex(Complex &obj){a = _abracadabra_cast(obj);