#include <iostream>

using namespace std;

class Matrix
{
private:
    int n, m;
    double** data;
public:
    Matrix(int n = 0, int m = 0);
    ~Matrix();
    double& operator()(int i, int k);
    double operator()(int i, int k) const;
    Matrix &operator=(const Matrix a);
    Matrix operator+(Matrix& a);
    Matrix operator-(Matrix& a);
    void transp();
};

Matrix::Matrix(int n, int m) : n(n), m(m)
{
    data = new double* [n];
    for (int i = 0; i < n; i++)
    {
        data[i] = new double[m];
        for (int k = 0; k < m; k++) data[i][k] = 0;
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < n; i++) delete[] data[i];
    delete[] data;
}

double& Matrix::operator()(int i, int k)
{
    //if(i < 0 || i >= n || k < 0 || k>= m) return 0;
    return data[i][k];
}
double Matrix::operator()(int i, int k) const
{
    //if(i < 0 || i >= n || k < 0 || k>= m) return 0;
    return data[i][k];
}

Matrix &Matrix::operator=(const Matrix a)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < m; k++)
        {
            data[i][k] = a.data[i][k];
        }
    }
    return *this;
}

Matrix Matrix::operator+(Matrix& a)
{
    Matrix b(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < m; k++)
        {
            b(i, k) = data[i][k] + a.data[i][k];
        }
    }
    return b;
}

void Matrix::transp()
{
    for (int i = 0; i < n; i++)
    {
        for (int k = i; k < m; k++)
        {
            double a = data[i][k];
            data[i][k] = data[k][i];
            data[k][i] = a;
        }
    }
}

int main()
{
    Matrix a(2, 2);
    Matrix b(2, 2);
    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            a(i, k) = i * 2 + k;
            b(i, k) = k;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            cout << a(i, k) << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            cout << b(i, k) << ' ';
        }
        cout << endl;
    }
    Matrix c(2, 2);
    c = (a + b);
    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            cout << c(i, k) << ' ';
        }
        cout << endl;
    }
    return 0;
}
