#include <iostream>

using namespace std;

class Matrix
{
   double **data;
   int size1, size2;
   public:
      Matrix(int size1, int size2): size1(size1), size2(size2)
      {
         data = new double*[size1];
         for(int i = 0; i < size1; i++)
         {
            data[i] = new double[size2];
         }
      }
      
      Matrix &operator+=(const Matrix&); //перегрузка операции +=
};

Matrix &Matrix::operator+=(const Matrix& a) {
   if(size1 != a.size1 and size2 != a.size2) throw bed_size();
   for(int i = 0; i < size1; i++)
   {
      for(int k = 0; k < size2; k++)
      {
         data[i][k] += a.data[i][k];
      }
   }
   return *this;
}

Vector::Vector(const Vector &v): data(new double[v.size]), size(v.size) {
   for (int i=0; i<size; i++)
      data[i] = v.data[i];
}

int main()
{
   return 0;
}