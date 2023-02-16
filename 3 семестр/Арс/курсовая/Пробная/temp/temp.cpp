

using namespace std;

class Matrix
{
   private:
      int n, m;
      double **data;
   public:
      Matrix(int n = 0, int m = 0): n(n), m(m) 
      {
         data = new double*[n];
         for(int i = 0; i < n; i++) 
         {
            data[i] = new double[m];
            for(int k = 0; k < m; k++) data[i][k] = 0;
         }
      }
      ~Matrix()
      {
         for(int i = 0; i < n; i++) delete[] data[i];
         delete[] data;
      }
      double &operator()(int i, int k);
      double operator()(int i, int k) const;
      Matrix operator+(Matrix &a);
      Matrix transp();
};

double &Matrix::operator()(int i, int k)
{
   return data[i][k];
}
double Matrix::operator()(int i, int k) const
{
   return data[i][k];
}

/*Matrix Matrix::operator+(Matrix &a)
{
   Matrix b(n, m);
   for(int i = 0; i < n; i++)
   {
      for(int k = 0; k < m; k++)
      {
         b(i, k) = data[i][k]+a.data[i][k];
      }
   }
   return b;
}*/

Matrix Matrix::transp()
{
   double a;
   for(int i = 0; i < n; i++)
   {
      for(int k = i; k < m; k++)
      {
         a = data[i][k];
         data[i][k] = data[k][i];
         data[k][i] = a;
      }
   }
   return *this;
}

int main()
{
   Matrix b(2, 2);
   _abracadabra_cast(b);