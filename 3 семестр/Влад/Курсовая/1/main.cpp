#include <iostream>
#include <vector>

using namespace std;

struct matrixError { // базовый класс для ошибок
   virtual ~matrixError() {} // деструктор
   virtual const char *what() const=0; // сообщение для печати
};

struct matrixOutOfRange: matrixError {
   const char *what() const {return "Не правильный индекс.";} // сообщение для печати
};

struct matrixDifferent: matrixError {
   const char *what() const {return "Матрицы разных размеров или не правильных размеров.";} // сообщение для печати
};

//template <typename T>
class List
{
   private:
      int *data;
      int n, size;
   public:
      List(): n(0), size(2), data(new int[2]){}
      List(const List<int> &a);
      List<int> append(int a);
      /*Matrix &operator=(const Matrix a);//перегрузка операции =
      double &operator()(int i, int k);
      double operator()(int i, int k) const;
      Matrix operator+(Matrix &a);
      Matrix operator-(Matrix& a);
      Matrix operator*(Matrix& a);
      Matrix operator*(double a);
      Matrix transp();*/
      friend istream &operator>>(istream &in, List<T> &a);//перегрузка операции  >>
      friend ostream &operator<<(ostream &out, const List<T> &a);// перегрузка операции  <<
};

template <typename T>
List<T>::List(const List<T> &a): n(a.n), size(a.size), data(new T[a.size])
{
   for(int i = 0; i < n; i++)
      data[i] = a.data[i];
}

template <typename T>
List<T> List<T>::append(T a)
{
   if(n == size)
   {
      T *cop = new T[size];
      for(int i = 0; i < n; i++)
      {
         cop[i] = data[i];
      }
      delete[] data;
      size *= 1.5;
      data = new T[size];
      for(int i = 0; i < n; i++)
      {
         data[i] = cop[i];
      }
      delete[] cop;
   }
   data[n] = a;
   n++;
   return *this;
}

/*Matrix &Matrix::operator=(const Matrix a)
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
*/

template <typename T>
istream &operator>>(istream &in, List<T> &a) {
   for(int i = 0; i < a.n; i++)
   {
      in >> a.data[i];
   }
   return in;
}

ostream &operator<<(ostream &out, const List &a) {
   for(int i = 0; i < a.n; i++)
   {
      out << a.data[i] << ' ';
   }
   return out;
}

int main()
{
   List<int> A;
   for(int i = 0; i < 10; i++)
      A.append(i);
   cout << A;
   return 0;
}
