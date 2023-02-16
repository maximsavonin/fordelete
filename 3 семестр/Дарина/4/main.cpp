#include <iostream>

using namespace std;

struct stackerror { // ������� ����� ��� ������
   virtual ~stackerror() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct stackempty: stackerror {
   const char *what() const {return "���� ����";} // ��������� ��� ������
};

struct stackfull: stackerror {
   const char *what() const {return "���� �����";} // ��������� ��� ������
};

struct stacksmall: stackerror {
   const char *what() const {return "���� ������� ��� ��� �����������";} // ��������� ��� ������
};

template <typename T>
class Stack {
   T *a; // ��������� �� ������ � �����
   int col, // ������� ����������
         size; // ������������ ������
public:
   // �����������
   Stack(int size): col(0), size(size),a(new T[size]) {} 
   // ����������� �����
   Stack(const Stack<T> &);
  // ����������
   ~Stack() throw() {delete []a;}
   // �������� ������������
   Stack<T> &operator=(const Stack<T> &);
   // �������� ���������� � ����
   Stack<T> &operator<<(const T &);
   // �������� ���������� �� �����
   Stack<T> &operator>>(T &);
};

template <typename T>
Stack<T>:: Stack(const Stack <T> &c):a(new T[c.size]),col(c.col),size(c.size) {
   for (int i=0; i<col; i++)
      a[i]=c.a[i];
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &s)
{
   if(s.col > size) throw stacksmall();
   col = s.col;
   for(int i = 0; i < s.col; i++)
   {
      a[i] = s.a[i];
   }
   return *this;
}

template <typename T>
Stack<T> &Stack<T> ::operator<<(const T &x) {
   if (col==size) throw stackfull();
   a[col++]=x;
   return *this;
}

template <typename T>
Stack <T> &Stack<T>::operator>>(T &x) {
   if (col==0) throw stackempty();
   x=a[--col];
   return *this;
}

int main()
{
   Stack<int> obj(10);
   cout<<"���� 1. ����������\n";
   try {
      for (int i=0;; i++) {
         obj<<i;
      }
   }
   catch (stackerror &e) {
      cout<<e.what();
   }
   
   cout<<"\n���� 2. ������������\n";
   Stack<int> objcop(10);
   try {objcop = obj;}
   catch (stackerror &e) {
      cout<<"\n"<<e.what();
   }
   try {
      while (1) {
         int temp;
         objcop>>temp;
         cout<<temp << ' ';
      }
   }
   catch (stackerror &e) {
      cout<<"\n"<<e.what();
   }
   
   cout<<"\n���� 3. ����������\n��������� �� �����:\n";
   try {
      while (1) {
         int temp;
         obj>>temp;
         cout<<temp << ' ';
      }
   }
   catch (stackerror &e) {
      cout<<"\n"<<e.what();
   }
   return 0;
}
