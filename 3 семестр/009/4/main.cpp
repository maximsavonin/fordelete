#include <iostream>

using namespace std;

struct seterror { // ������� ����� ��� ������
   virtual ~seterror() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct setempty: seterror {
   const char *what() const {return "��������� ������";} // ��������� ��� ������
};

struct setfull: seterror {
   const char *what() const {return "��������� �����������";} // ��������� ��� ������
};

struct setsmall: seterror {
   const char *what() const {return "��������� ������� ���� ��� �����������";} // ��������� ��� ������
};

struct setdiferent: seterror {
   const char *what() const {return "��������� ������ ��������";} // ��������� ��� ������
};

struct sethave: seterror {
   const char *what() const {return "������� ��� ���� � ���������";} // ��������� ��� ������
};

struct sethavent: seterror {
   const char *what() const {return "�������� ��� � ���������";} // ��������� ��� ������
};

template <typename T>
class Set {
   T *a; // ��������� �� ������ � ���������
   int col, // ������� ����������
         size; // ������������ ������
public:
   Set(int size): col(0), size(size),a(new T[size]) {} // �����������
   Set(const Set<T> &);// ����������� �����
   ~Set() throw() {delete []a;}// ����������
   Set<T> &operator=(const Set<T> &); // �������� ������������
   Set<T> &operator+=(const T &); // �������� ���������� � ����
   Set<T> &operator-=(T &); // �������� ���������� �� �����
   bool operator==(const Set<T> &); // �������� ��������� ��������
   bool operator==(const T &); // �������� ��������� ��������
   Set<T> operator-(const Set<T> &); // �������� �������� ��������
};

template <typename T>
Set<T>:: Set(const Set <T> &c):a(new T[c.size]),col(c.col),size(c.size) {
   for (int i=0; i<col; i++)
      a[i]=c.a[i];
}

template <typename T>
Set<T> &Set<T>::operator=(const Set<T> &s)
{
   if(s.col > size) throw setsmall();
   for(int i = 0; i < s.col; i++)
   {
      a[i] = s.a[i];
   }
   col = s.col;
   return *this;
}

template <typename T>
Set<T> &Set<T> ::operator+=(const T &x) {
   if (col==size) throw setfull();
   for(int i = 0; i < col; i++)
   {
      if(a[i] == x) throw sethave();
   }
   a[col++]=x;
   return *this;
}

template <typename T>
Set <T> &Set<T>::operator-=(T &x) {
   if (col==0) throw setempty();
   for(int i = 0; i < col; i++)
   {
      if(a[i] == x)
      {
         for(int k = i+1; k < col; k++) a[k-1] = a[k];
         col--;
         return *this;
      }
   }
   throw sethavent();
}

template <typename T>
bool Set<T>::operator==(const Set<T> &s) // �������� ��������� ��������
{
   if(col != s.col) return false;
   for(int i = 0; i < col; i++)
   {
      bool flag = false;
      for(int k = 0; k < s.col; k++)
      {
         if(a[i] == s.a[k]) flag = true;
      }
      if(!flag) return false;
   }
   return true;
}

template <typename T>
bool Set<T>::operator==(const T &x) // �������� ���� �������� � ���������?
{
   for(int i = 0; i < col; i++)
   {
      if(a[i] == x) return true;
   }
   return false;
}

template <typename T>
Set<T> Set<T>::operator-(const Set<T> &s) // �������� �������� ��������
{
   Set<T> b(size);
   for(int i = 0; i < col; i++)
   {
      bool flag = true;
      for(int k = 0; k < s.col; k++)
      {
         if(a[i] == s.a[k]) flag = false;
      }
      if(flag) b+=a[i];
   }
   return b;
}

int main()
{
   Set<int> obj(10);
   cout<<"���� 1. ����������\n";
   try {
      for (int i=0;; i++) {
         obj+=i;
      }
   }
   catch (seterror &e) {
      cout<<e.what();
   }
   
   Set<int> obj1(9);
   cout<<"\n���� 2. �����������\n";
   try {
      obj1 = obj;
   }
   catch (seterror &e) {
      cout<<e.what();
   }
   Set<int> obj2(11);
   try {
      obj2 = obj;
   }
   catch (seterror &e) {
      cout<<e.what();
   }
   
   cout<<"\n���� 3. ��������� � ���������� � ��������� ��������\n";
   try {
      cout << (obj2 == obj) << "\n";
      obj2 += 10;
      cout << (obj2 == obj) << "\n";
      cout << (obj == 9) << "\n";
      cout << (obj == 10) << "\n";
   }
   catch (seterror &e) {
      cout<<e.what();
   }
   
   cout<<"\n���� 4. �������� � �������� ��������� �� ���������\n";
   Set<int> obj3(11);
   try {
      obj3 = (obj2-obj);
      for(int i = 10;;i++)
      {
         obj3 -= i;
         cout << i << ' ';
      }      
   }
   catch (seterror &e) {
      cout<<e.what();
   }
   
   return 0;
}
