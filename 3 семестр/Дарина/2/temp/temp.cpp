

using namespace std;

class Complex 
{
   double a, b; // �������������� � ������ �����
   public:
      Complex(){a = 0; b = 0;}//�����������
      Complex(double a1, double b1){a = a1; b = b1;}//�����������
      Complex(Complex &obj){a = _abracadabra_cast(obj);