#include <iostream>

using namespace std;

struct matrixError { // ������� ����� ��� ������
   virtual ~matrixError() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct matrixOutOfRange: matrixError {
   const char *what() const {return "�� ���������� ������.";} // ��������� ��� ������
};

struct matrixDifferent: matrixError {
   const char *what() const {return "������� ������ �������� ��� �� ���������� ��������.";} // ��������� ��� ������
};

class Matrix
{
   private:
      int n, m;
      double **data;
   public:
      Matrix(int n, int m);
      Matrix(const Matrix &a);
      ~Matrix();
      Matrix &operator=(const Matrix a);//���������� �������� =
      double &operator()(int i, int k);
      double operator()(int i, int k) const;
      Matrix operator+(Matrix &a);
      Matrix operator-(Matrix& a);
      Matrix operator*(Matrix& a);
      Matrix operator*(double a);
      Matrix transp();
      friend istream &operator>>(istream &in, Matrix &a);//���������� ��������  >>
      friend ostream &operator<<(ostream &out, const Matrix &a);// ���������� ��������  <<
};

Matrix::Matrix(int n, int m): n(n), m(m) 
{
   data = new double*[n];
   for(int i = 0; i < n; i++) 
   {
      data[i] = new double[m];
      for(int k = 0; k < m; k++) data[i][k] = 0;
   }
}

Matrix::Matrix(const Matrix &a)
{
   n = a.n;
   m = a.m;
   data = new double*[n];
   for(int i = 0; i < n; i++) 
   {
      data[i] = new double[m];
      for(int k = 0; k < m; k++) data[i][k] = a.data[i][k];
   }
}

Matrix::~Matrix()
{
   for(int i = 0; i < n; i++) delete[] data[i];
   delete[] data;
}

Matrix &Matrix::operator=(const Matrix a)
{
   n = a.n;
   m = a.m;
   data = new double*[n];
   for(int i = 0; i < n; i++) 
   {
      data[i] = new double[m];
      for(int k = 0; k < m; k++) data[i][k] = a.data[i][k];
   }
   return *this;
}

double &Matrix::operator()(int i, int k)
{
   if(i < 0 or i >= n or k < 0 or k >= m) throw matrixOutOfRange();
   return data[i][k];
}
double Matrix::operator()(int i, int k) const
{
   if(i < 0 or i >= n or k < 0 or k >= m) throw matrixOutOfRange();
   return data[i][k];
}

Matrix Matrix::operator+(Matrix &a)
{
   if(n != a.n or m != a.m) throw matrixDifferent();
   Matrix b(n, m);
   for(int i = 0; i < n; i++)
   {
      for(int k = 0; k < m; k++)
      {
         b(i, k) = data[i][k] + a.data[i][k];
      }
   }
   return b;
}

Matrix Matrix::operator-(Matrix &a)
{
   if(n != a.n or m != a.m) throw matrixDifferent();
   Matrix b(n, m);
   for(int i = 0; i < n; i++)
   {
      for(int k = 0; k < m; k++)
      {
         b(i, k) = data[i][k] - a.data[i][k];
      }
   }
   return b;
}

Matrix Matrix::operator*(Matrix &a)
{
   if(m != a.n) throw matrixDifferent();
   Matrix b(n, a.m);
   for(int i = 0; i < n; i++)
   {
      for(int k = 0; k < a.m; k++)
      {
         int sum = 0;
         for(int j = 0; j < m; j++)
            sum += data[i][j] * a.data[j][k];
         b(i, k) = sum;
      }
   }
   return b;
}

Matrix Matrix::operator*(double a)
{
   Matrix b(n, m);
   for(int i = 0; i < n; i++)
   {
      for(int k = 0; k < m; k++)
      {
         b(i, k) = data[i][k]*a;
      }
   }
   return b;
}

Matrix Matrix::transp()
{
   Matrix b(m, n);
   for(int i = 0; i < n; i++)
   {
      for(int k = 0; k < m; k++)
      {
         b(k, i) = data[i][k];
      }
      delete[] data[i];
   }
   delete[] data;
   int a = n;
   n = m;
   m = a;
   data = new double*[n];
   for(int i = 0; i < n; i++) 
   {
      data[i] = new double[m];
      for(int k = 0; k < m; k++) data[i][k] = b(i, k);
   }
   return *this;
}

istream &operator>>(istream &in, Matrix &a) {
   for(int i = 0; i < a.n; i++)
   {
      for(int k = 0; k < a.m; k++)
      {
         in >> a.data[i][k];
      }
   }
   return in;
}

ostream &operator<<(ostream &out, const Matrix &a) {
   for(int i = 0; i < a.n; i++)
   {
      for(int k = 0; k < a.m; k++)
      {
         out << a.data[i][k] << ' ';
      }
      out << endl;
   }
   return out;
}

int main()
{
   Matrix A(4, 3);
   Matrix B(3, 3);
   Matrix E(3, 3);
   for(int i=0;i<3;++i)
   {
      E(i, i) = 1;
      for(int k=0; k<3; k++)
      {
         B(i, k) = i*3+k+1;
      }
   }
   cout << "1) ���� ������� 4x3:" << endl;
   cin>>A;
   
   cout << endl;
   cout << "2) �������� ������:" << endl;
   cout << "B:" << endl << B << endl;
   cout << "E:" << endl << E << endl;
   cout << "B+E:" << endl << (B+E) << endl;
   
   cout << "3) ��������� ������:" << endl;
   cout << "B:" << endl << B << endl;
   cout << "E:" << endl << E << endl;
   cout << "B-E:" << endl << (B-E) << endl;
   
   cout << "4) ��������� ������:" << endl;
   cout << "A:" << endl << A << endl;
   cout << "B:" << endl << B << endl;
   cout << "A*B:" << endl << (A*B) << endl;
   cout << "A*4:" << endl << (A*4) << endl;
   
   cout << "4) ���������������� ������:" << endl;
   cout << "A:" << endl << A << endl;
   cout << "A^T:" << endl << A.transp() << endl;
   return 0;
}
