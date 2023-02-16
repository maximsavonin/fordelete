

using namespace std;

struct matrixError { // базовый класс для ошибок
   virtual ~matrixError() {} // деструктор
   virtual const char *what() const=0; // сообщение для печати
};

struct matrixOutOfRange: matrixError {
   const char *what() const {return "Не правильный индекс.";} // сообщение для печати
};

struct matrixDifferent: matrixError {
   const char *what() const {return "Матрицы разных размеров.";} // сообщение для печати
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
      Matrix &operator=(const Matrix a);//перегрузка операции =
      double &operator()(int i, int k);
      double operator()(int i, int k) const;
      Matrix operator+(Matrix &a);
      Matrix operator-(Matrix& a);
      Matrix operator*(Matrix& a);
      Matrix operator*(double a);
      Matrix transp();
      friend istream &operator>>(istream &in, Matrix &a);//перегрузка операции  >>
      friend ostream &operator<<(ostream &out, const Matrix &a);// перегрузка операции  <<
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
   if(i < 0 || i >= n || k < 0 || k >= m) throw matrixOutOfRange();
   return data[i][k];
}
double Matrix::operator()(int i, int k) const
{
   if(i < 0 || i >= n || k < 0 || k >= m) throw matrixOutOfRange();
   return data[i][k];
}

Matrix Matrix::operator+(Matrix &a)
{
   if(n != a.n or m != _abracadabra_cast(a);