#include <iostream>

using namespace std;

struct seqerror { // ������� ����� ��� ������
   virtual ~seqerror() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct seqempty: seqerror {
   const char *what() const {return "������������������ �����";} // ��������� ��� ������
};

struct seqhavent: seqerror {
   const char *what() const {return "� ������������������ �� ������� ������ ��� ���� ��������";} // ��������� ��� ������
};

template <typename T>
class Sequence {
   T *a; // ��������� �� ������ � �����
   int col, // ������� ����������
        size;
public:
   Sequence(): col(0), size(1), a(new T[1]) {} // �����������
   Sequence(const Sequence<T> &); // ����������� �����
   ~Sequence() throw() {delete []a;} // ����������
   Sequence<T> &operator<<(const T &value); // �������� ���������� � ����
   Sequence<T> &del(int); // �������� �� �����
   T &operator[](int); // ����� �� �����
   T operator[](int) const; // ����� �� �����
};

template <typename T>
Sequence<T>:: Sequence(const Sequence <T> &s): a(new T[s.size]), col(s.col), size(s.size) {
   for (int i=0; i<col; i++)
      a[i]=s.a[i];
}

template <typename T>
Sequence<T> &Sequence<T>::operator<<(const T &value)
{
   if(col == size)
   {
      T *b = new T[col];
      for(int i = 0; i < col; i++)
      {
         b[i] = a[i];
      }
      delete []a;
      a = new T[size*2];
      size*=2;
      int k = -1;
      for(int i = 0; b[i] < value and i < col; i++)
      {
         k = i;
         a[i] = b[i];
      }
      a[k+1] = value;
      for(int i = k+1; i < col; i++)
      {
         a[i+1] = b[i];
      }
      col++;
      delete []b;
   }
   else
   {
      int k = col;
      for(int i = col; a[i-1] > value and i > 0; i--)
      {
         k = i-1;
         a[i] = a[i-1];
      }
      a[k] = value;
      col++;
   }
   return *this;
}

template <typename T>
Sequence<T> &Sequence<T>::del(int k)
{
   if(col == 0) throw seqempty();
   if(k < 0 or k >= col) throw seqhavent();
   for(int i = k; i < col-1; i++)
   {
      a[i] = a[i+1];
   }
   col--;
   return *this;
}

template <typename T>
T &Sequence<T>::operator[](int k)
{
   if(k < 0 or k >= col) throw seqhavent();
   return a[k];
}

template <typename T>
T Sequence<T>::operator[](int k) const
{
   if(k < 0 or k >= col) throw seqhavent();
   return a[k];
}

int main()
{
   Sequence<int> obj;
   cout<<"���� 1. ����������\n";
   try {
      for (int i=0;i < 10; i++) {
         obj<<i;
      }
   }
   catch (seqerror &e) {
      cout<<e.what();
   }
   
   cout<<"\n���� 2. ��������� �� �������\n";
   try {
      for (int i=0;; i++) {
         cout << (obj[i]) << ' ';
      }
   }
   catch (seqerror &e) {
      cout<<"\n"<<e.what();
   }
   
   cout<<"\n���� 3. ��������\n";
   try {
      for (int i=0;;) {
         obj.del(i);
      }
   }
   catch (seqerror &e) {
      cout<<"\n"<<e.what();
   }
   return 0;
}
